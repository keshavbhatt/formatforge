#include "conversionprocess.h"

#include <Core/utils.h>

#include <QStringLiteral>

const QRegularExpression ConversionProcess::DUR_REGEX(
    R"(Duration: (?P<hour>\d{2}):(?P<min>\d{2}):(?P<sec>\d{2})\.(?P<ms>\d{2}))");
const QRegularExpression ConversionProcess::TIME_REGEX(
    R"(out_time=(?P<hour>\d{2}):(?P<min>\d{2}):(?P<sec>\d{2})\.(?P<ms>\d{2}))");

ConversionProcess::ConversionProcess(QObject *parent,
                                     const ConversionItem &conversionItem)
    : QObject{parent}, m_conversionItem(conversionItem) {}

ConversionProcess::~ConversionProcess() {
  this->stop();
  if (m_conversionProcess) {
    m_conversionProcess->deleteLater();
  }
}

void ConversionProcess::stop() {
  if (m_conversionProcess &&
      (m_conversionProcess->state() == QProcess::Running ||
       QProcess::Starting)) {
    m_conversionProcess->disconnect();
    m_conversionProcess->kill();
    m_conversionProcess = nullptr;
  }
}

void ConversionProcess::start() {
  Utils::ensureDirectoryPath(m_conversionItem.getOutputDirectory());

  this->stop();

  m_conversionProcess = new QProcess(this);

  connect(m_conversionProcess, &QProcess::readyReadStandardOutput, this, [=]() {
    handleProgress(m_conversionItem.getId(),
                   m_conversionProcess->readAllStandardOutput());
  });

  connect(m_conversionProcess, &QProcess::readyReadStandardError, this, [=]() {
    handleProgress(m_conversionItem.getId(),
                   m_conversionProcess->readAllStandardError());
  });

  connect(m_conversionProcess,
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
          [=](int exitCode, QProcess::ExitStatus exitStatus) {
            emit finished(m_conversionItem.getId(), exitCode, exitStatus);
            if (m_conversionProcess) {
              m_conversionProcess->deleteLater();
              m_conversionProcess = nullptr;
            }
          });

  auto outputFilePath =
      Utils::getFileNameFor(m_conversionItem.getOutputDirectory() +
                                m_conversionItem.getFileBaseName(),
                            m_conversionItem.getOutputExetension());
  auto inputFilePath = m_conversionItem.getFilePath();
  auto ffmpegArgs = m_conversionItem.getFfmpegArguments().split(" ");

  QStringList args;
  args << "-hide_banner"
       << "-loglevel"
       << "info"
       << "-progress"
       << "-"
       << "-nostats"
       << "-y";
  args << "-i" << inputFilePath;
  args << ffmpegArgs;
  args << outputFilePath;

  qDebug() << "Starting process" << outputFilePath;

  m_conversionProcess->start("ffmpeg", args);
}

void ConversionProcess::handleProgress(const QString &processId,
                                       const QString &progressData) {

  auto calculatedProgress = calculateProgress(progressData);
  if (calculatedProgress >= 0) {
    m_progress = QJsonObject();
    m_progress.insert("pid", processId);
    m_progress.insert("progress_calculated", calculatedProgress);
    QStringList lines = progressData.trimmed().split("\n");
    foreach (QString line, lines) {
      QStringList kv = line.split("=");
      if (kv.count() > 1)
        m_progress.insert(kv.first(), kv.last());
    }
  }

  emit progressChanged(m_progress);
}

double ConversionProcess::calculateProgress(const QString &progressData) {
  // Parse total duration (if not available yet)
  if (!m_totalDuration) {
    QRegularExpressionMatch durationMatch = DUR_REGEX.match(progressData);
    if (durationMatch.hasMatch()) {
      int hour = durationMatch.captured("hour").toInt();
      int min = durationMatch.captured("min").toInt();
      int sec = durationMatch.captured("sec").toInt();
      int ms = durationMatch.captured("ms").toInt();
      m_totalDuration = 3600000 * hour + 60000 * min + 1000 * sec + ms;
    }
  }

  if (m_totalDuration <= 0) {
    return -1.0;
  }

  // Parse progress time
  QRegularExpressionMatch progressMatch = TIME_REGEX.match(progressData);
  if (progressMatch.hasMatch()) {
    int hour = progressMatch.captured("hour").toInt();
    int min = progressMatch.captured("min").toInt();
    int sec = progressMatch.captured("sec").toInt();
    int ms = progressMatch.captured("ms").toInt();
    int elapsedTime = 3600000 * hour + 60000 * min + 1000 * sec + ms;
    return (double)elapsedTime / m_totalDuration * 100;
  }

  return -1.0;
}

#include "conversionprocess.h"

#include <Core/utils.h>

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

  connect(m_conversionProcess, &QProcess::readyRead, this, [=]() {
    qDebug() << m_conversionItem.getId() << "emited 'ReadyRead signal'"
             << m_conversionProcess->readAll();
  });

  connect(m_conversionProcess,
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
          [=](int exitCode, QProcess::ExitStatus exitStatus) {
            Q_UNUSED(exitStatus);
            qDebug() << m_conversionItem.getId() << "emited 'Finished signal'"
                     << "Process exited with code " << exitCode;
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
  args << "-i" << inputFilePath;
  args << ffmpegArgs;
  args << outputFilePath;

  qDebug() << "Starting process" << outputFilePath;

  m_conversionProcess->start("ffmpeg", args);
}

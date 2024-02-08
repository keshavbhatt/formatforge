#include "conversionprocess.h"

ConversionProcess::ConversionProcess(QObject *parent,
                                     const ConversionItem &conversionItem)
    : QObject{parent}, m_conversionItem(conversionItem) {}

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

  m_conversionProcess->setProgram("ffmpeg");
  QStringList args;
  args << "-i" << m_conversionItem.getFilePath();
  args << m_conversionItem.getFfmpegArguments().split(" ");
  args << "/tmp/" + m_conversionItem.getId() + "." +
              m_conversionItem.getOutputExetension();
  m_conversionProcess->setArguments(args);

  qDebug() << "Starting process" << m_conversionItem.getId();
  m_conversionProcess->start();
}

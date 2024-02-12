#include "ffprobemetadataextractor.h"

FFProbeMetaDataExtractor::FFProbeMetaDataExtractor(QObject *parent)
    : MetadataExtractor(parent), processedFilesCounter(0) {}

FFProbeMetaDataExtractor::~FFProbeMetaDataExtractor() {}

void FFProbeMetaDataExtractor::processMediaFiles(const QStringList &filePaths) {
  processedFilesCounter = 0;
  int totalFilesToProcess = filePaths.size();

  QEventLoop *eventLoop = new QEventLoop();

  for (int i = 0; i < totalFilesToProcess; ++i) {
    const QString &filePath = filePaths.at(i);

    QProcess *ffprobeProcess = new QProcess(this);

    connect(ffprobeProcess,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
              Q_UNUSED(exitStatus);

              processedFilesCounter++;
              emit mediaProcessingProgress(processedFilesCounter,
                                           totalFilesToProcess);
              QByteArray output = ffprobeProcess->readAllStandardOutput();

              if (exitCode != 0) {
                emit mediaProcessed(
                    filePath, QString("%1 Processing error. Exit code: %2")
                                  .arg(extractorId(), exitCode)
                                  .toUtf8());
              } else {
                emit mediaProcessed(filePath, output);
              }

              ffprobeProcess->deleteLater();

              eventLoop->quit();
            });

    ffprobeProcess->start("ffprobe", QStringList()
                                         << "-v"
                                         << "quiet"
                                         << "-print_format"
                                         << "json"
                                         << "-show_format"
                                         << "-show_streams" << filePath);
    eventLoop->exec();
  }

  emit mediaProcessingFinished();
  eventLoop->deleteLater();
}

QString FFProbeMetaDataExtractor::extractorId() const {
  return metaObject()->className();
}

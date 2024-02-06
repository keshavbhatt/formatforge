#include "ffprobemetadataextractor.h"

FFProbeMetaDataExtractor::FFProbeMetaDataExtractor(QObject *parent)
    : QObject(parent), processedFilesCounter(0) {}

FFProbeMetaDataExtractor::~FFProbeMetaDataExtractor() {}

void FFProbeMetaDataExtractor::processMediaFiles(const QStringList &filePaths) {
  processedFilesCounter = 0;
  int totalFilesToProcess = filePaths.size();

  QEventLoop *eventLoop = new QEventLoop();

  for (int i = 0; i < totalFilesToProcess; ++i) {
    const QString &fileName = filePaths.at(i);

    QProcess *ffprobeProcess = new QProcess(this);

    connect(ffprobeProcess,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
              Q_UNUSED(exitStatus);

              processedFilesCounter++;
              emit mediaProcessingProgress(processedFilesCounter,
                                           totalFilesToProcess);
              QByteArray output = ffprobeProcess->readAllStandardOutput();
              QString result = QString::fromUtf8(output);

              if (exitCode != 0) {
                emit mediaProcessed(fileName, "processing_error");
              } else {
                emit mediaProcessed(fileName, result);
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
                                         << "-show_streams" << fileName);
    eventLoop->exec();
  }

  emit mediaProcessingFinished();
  eventLoop->deleteLater();
}

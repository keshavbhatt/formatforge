#include "ffprobemetadataextractor.h"

FFProbeMetaDataExtractor::FFProbeMetaDataExtractor(QObject *parent)
    : QObject(parent), processedFilesCounter(0) {}

FFProbeMetaDataExtractor::~FFProbeMetaDataExtractor() {}

void FFProbeMetaDataExtractor::processMediaFiles(const QStringList &fileNames) {
  processedFilesCounter = 0;
  int totalFilesToProcess = fileNames.size();

  for (int i = 0; i < totalFilesToProcess; ++i) {
    const QString &fileName = fileNames.at(i);

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

              QCoreApplication::processEvents();

              // all files processed emit finish
              if (processedFilesCounter == totalFilesToProcess) {
                emit mediaProcessingFinished();
              }

              ffprobeProcess->deleteLater();
            });

    ffprobeProcess->start("ffprobe", QStringList()
                                         << "-v"
                                         << "quiet"
                                         << "-print_format"
                                         << "json"
                                         << "-show_format"
                                         << "-show_streams" << fileName);
  }
}

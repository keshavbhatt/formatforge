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

    auto cacheKey = Utils::computeFileHash(filePath);
    if (CacheStore::instance().exists(cacheKey, this->extractorId())) {
      auto dataFromCache =
          CacheStore::instance().load(cacheKey, this->extractorId());
      emit mediaProcessed(filePath, dataFromCache);
      qDebug().noquote()  << dataFromCache;
      processedFilesCounter++;
      emit mediaProcessingProgress(processedFilesCounter, totalFilesToProcess);
    } else {
      QProcess *ffprobeProcess = new QProcess(this);
      connect(ffprobeProcess,
              QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
              this, [=](int exitCode, QProcess::ExitStatus exitStatus) {
                Q_UNUSED(exitStatus);

                QByteArray output = ffprobeProcess->readAllStandardOutput();
                if (exitCode != 0) {
                  emit mediaProcessed(
                      filePath, QString("%1 Processing error. Exit code: %2")
                                    .arg(extractorId(), exitCode)
                                    .toUtf8());
                } else {
                  CacheStore::instance().save(cacheKey, output,
                                              this->extractorId());
                  emit mediaProcessed(filePath, output);
                }

                processedFilesCounter++;
                emit mediaProcessingProgress(processedFilesCounter,
                                             totalFilesToProcess);

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
  }

  emit mediaProcessingFinished();
  eventLoop->deleteLater();
}

QString FFProbeMetaDataExtractor::extractorId() const {
  return metaObject()->className();
}

#include "ffmpegthumbnailextractor.h"

/**
 * @brief FFMpegThumbnailExtractor::FFMpegThumbnailExtractor
 * @param parent
 */
FFMpegThumbnailExtractor::FFMpegThumbnailExtractor(QObject *parent)
    : MetadataExtractor(parent), m_processedFilesCounter(0) {}

FFMpegThumbnailExtractor::~FFMpegThumbnailExtractor() {}

void FFMpegThumbnailExtractor::processMediaFiles(const QStringList &fileNames) {
  m_processedFilesCounter = 0;
  m_totalFilesToProcess = fileNames.size();

  QCoreApplication::processEvents();
  this->processNextMediaFile(fileNames);
}

void FFMpegThumbnailExtractor::processNextMediaFile(
    const QStringList &fileNames) {
  if (m_processedFilesCounter < m_totalFilesToProcess) {
    const QString &filePath = fileNames.at(m_processedFilesCounter);

    auto cacheKey = Utils::computeFileHash(filePath);
    if (CacheStore::instance().exists(cacheKey, this->extractorId())) {
      auto dataFromCache =
          CacheStore::instance().load(cacheKey, this->extractorId());
      emit mediaProcessed(filePath, dataFromCache);
      m_processedFilesCounter++;
      emit mediaProcessingProgress(m_processedFilesCounter,
                                   m_totalFilesToProcess);
    } else {
      QProcess *ffmpegProcess = new QProcess(this);
      connect(ffmpegProcess,
              QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
              this, [=](int exitCode, QProcess::ExitStatus exitStatus) {
                Q_UNUSED(exitStatus);

                QByteArray output = ffmpegProcess->readAllStandardOutput();
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

                m_processedFilesCounter++;
                emit mediaProcessingProgress(m_processedFilesCounter,
                                             m_totalFilesToProcess);

                processNextMediaFile(fileNames);
                ffmpegProcess->deleteLater();
              });

      ffmpegProcess->start("ffmpeg", QStringList() << "-v"
                                                   << "quiet"
                                                   << "-i" << filePath << "-vf"
                                                   << "select=gte(n\\,100)"
                                                   << "-vframes"
                                                   << "1"
                                                   << "-f"
                                                   << "image2pipe"
                                                   << "-");
    }
  } else {
    emit mediaProcessingFinished();
  }
}

QString FFMpegThumbnailExtractor::extractorId() const {
  return metaObject()->className();
}

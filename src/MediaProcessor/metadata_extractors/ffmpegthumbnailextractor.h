#ifndef FFMPEGTHUMBNAILEXTRACTOR_H
#define FFMPEGTHUMBNAILEXTRACTOR_H

#include "Core/utils.h"
#include "MediaProcessor/cache/cachestore.h"
#include "metadata_extractor.h"

#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QProcess>

class FFMpegThumbnailExtractor : public MetadataExtractor {
  Q_OBJECT

public:
  explicit FFMpegThumbnailExtractor(QObject *parent = nullptr);
  ~FFMpegThumbnailExtractor() override;

public slots:
  void processMediaFiles(const QStringList &fileNames) override;

private:
  void processNextMediaFile(const QStringList &fileNames);

  int m_processedFilesCounter;
  int m_totalFilesToProcess;

public:
  QString extractorId() const override;
};

#endif // FFMPEGTHUMBNAILEXTRACTOR_H

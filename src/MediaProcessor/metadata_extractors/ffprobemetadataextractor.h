#ifndef FFPROBEMETADATAEXTRACTOR_H
#define FFPROBEMETADATAEXTRACTOR_H

#include "Core/utils.h"
#include "MediaProcessor/cache/cachestore.h"
#include "metadata_extractor.h"

#include <QCoreApplication>
#include <QObject>
#include <QProcess>

class FFProbeMetaDataExtractor : public MetadataExtractor {
  Q_OBJECT

public:
  explicit FFProbeMetaDataExtractor(QObject *parent = nullptr);
  ~FFProbeMetaDataExtractor() override;

public slots:
  void processMediaFiles(const QStringList &filePaths) override;

private:
  int processedFilesCounter;

public:
  QString extractorId() const override;
};

#endif // FFPROBEMETADATAEXTRACTOR_H

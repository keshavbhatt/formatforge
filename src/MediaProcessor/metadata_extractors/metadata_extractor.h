#ifndef METADATA_EXTRACTOR_H
#define METADATA_EXTRACTOR_H

#include <QObject>
#include <QStringList>

class MetadataExtractor : public QObject {
  Q_OBJECT

public:
  explicit MetadataExtractor(QObject *parent = nullptr) : QObject(parent) {}
  virtual ~MetadataExtractor() {}

  virtual QString extractorId() const = 0;

public slots:
  virtual void processMediaFiles(const QStringList &filePaths) = 0;

signals:
  void mediaProcessingProgress(int currentFileIndex, int totalFiles);
  void mediaProcessed(const QString &fileName, const QByteArray &result);
  void mediaProcessingFinished();
};

#endif // METADATA_EXTRACTOR_H

#ifndef FFPROBEMETADATAEXTRACTOR_H
#define FFPROBEMETADATAEXTRACTOR_H

#include <QObject>
#include <QCoreApplication>
#include <QProcess>

class FFProbeMetaDataExtractor : public QObject {
  Q_OBJECT

public:
  explicit FFProbeMetaDataExtractor(QObject *parent = nullptr);
  ~FFProbeMetaDataExtractor();

public slots:
  void processMediaFiles(const QStringList &filePaths);

signals:
  void mediaProcessingProgress(int currentFileIndex, int totalFiles);
  void mediaProcessed(const QString &fileName, const QString &result);
  void mediaProcessingFinished();

private:
  int processedFilesCounter;
};

#endif // FFPROBEMETADATAEXTRACTOR_H

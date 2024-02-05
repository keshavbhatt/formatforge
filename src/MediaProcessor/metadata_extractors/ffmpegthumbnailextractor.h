#ifndef FFMPEGTHUMBNAILEXTRACTOR_H
#define FFMPEGTHUMBNAILEXTRACTOR_H

#include <QCoreApplication>
#include <QObject>
#include <QProcess>

class FFMpegThumbnailExtractor : public QObject {
  Q_OBJECT

public:
  explicit FFMpegThumbnailExtractor(QObject *parent = nullptr);
  ~FFMpegThumbnailExtractor();

public slots:
  void processMediaFiles(const QStringList &fileNames);

signals:
  void mediaProcessingProgress(int currentFileIndex, int totalFiles);
  void mediaProcessed(const QString &fileName, const QByteArray &result);
  void mediaProcessingFinished();

private:
  void processNextMediaFile(const QStringList &fileNames);

  int processedFilesCounter;
  int totalFilesToProcess;
};

#endif // FFMPEGTHUMBNAILEXTRACTOR_H

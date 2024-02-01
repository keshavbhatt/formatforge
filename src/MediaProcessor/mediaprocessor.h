// mediaprocessor.h
#ifndef MEDIAPROCESSOR_H
#define MEDIAPROCESSOR_H

#include <QObject>
#include <QThread>

class MediaProcessor : public QObject {
    Q_OBJECT

public:
    explicit MediaProcessor(QObject *parent = nullptr);
    ~MediaProcessor();

public slots:
    void processMediaFiles(const QStringList &fileNames);

signals:
    void mediaProcessingProgress(int currentFileIndex, int totalFiles);
    void mediaProcessed(const QString &fileName, const QString &result);
    void mediaProcessingFinished();

private:
    int processedFilesCounter;

};

#endif // MEDIAPROCESSOR_H

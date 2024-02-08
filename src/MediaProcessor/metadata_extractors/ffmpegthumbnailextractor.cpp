#include "ffmpegthumbnailextractor.h"
#include <QDebug>

FFMpegThumbnailExtractor::FFMpegThumbnailExtractor(QObject *parent)
    : QObject(parent), processedFilesCounter(0) {}

FFMpegThumbnailExtractor::~FFMpegThumbnailExtractor() {}

void FFMpegThumbnailExtractor::processMediaFiles(const QStringList &fileNames) {
  processedFilesCounter = 0;
  totalFilesToProcess = fileNames.size();
  QCoreApplication::processEvents(); // do no block gui thread
  processNextMediaFile(fileNames);
}

void FFMpegThumbnailExtractor::processNextMediaFile(
    const QStringList &fileNames) {
  if (processedFilesCounter < totalFilesToProcess) {
    const QString &fileName = fileNames.at(processedFilesCounter);

    QProcess *ffmpegProcess = new QProcess(this);

    connect(ffmpegProcess,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
              Q_UNUSED(exitStatus);

              QByteArray output = ffmpegProcess->readAllStandardOutput();

              if (exitCode != 0) {
                emit mediaProcessed(fileName,
                                    QString("Processing error. Exit code: %1")
                                        .arg(exitCode)
                                        .toUtf8());
              } else {
                emit mediaProcessed(fileName, output);
              }

              processedFilesCounter++;
              emit mediaProcessingProgress(processedFilesCounter,
                                           totalFilesToProcess);

              processNextMediaFile(fileNames);

              ffmpegProcess->deleteLater();
            });


    // TIME BASED
    // ffmpegProcess->start("ffmpeg", QStringList() << "-v"
    //                                              << "quiet"
    //                                              << "-i" << fileName << "-ss"
    //                                              << "0"
    //                                              << "-vframes"
    //                                              << "1"
    //                                              << "-f"
    //                                              << "image2pipe"
    //                                              << "-");

    //ffmpeg  -i l.webm -vf "thumbnail,select=gt(scene\,0.015)" -vsync vfr "outd.jpg"

    // THUMBNAIL PLUGIN BASED(probably broken here) see notes.md
    // ffmpegProcess->start("ffmpeg", QStringList() << "-v"
    //                                              << "quiet"
    //                                              << "-i" << fileName << "-vf"
    //                                              << "thumbnail,select=gt(scene\,0.015)"
    //                                              << "-vsync"
    //                                              << "vfr"
    //                                              << "-f"
    //                                              << "image2pipe"
    //                                              << "-");

    // ffmpeg -i l.webm -vf "select=gte(n\,100)" -vframes 1 out_img.png

    ffmpegProcess->start("ffmpeg", QStringList() << "-v"
                                                 << "quiet"
                                                 << "-i" << fileName << "-vf"
                                                 << "select=gte(n\\,100)"
                                                 << "-vframes"
                                                 << "1"
                                                 << "-f"
                                                 << "image2pipe"
                                                 << "-");

  } else {
    emit mediaProcessingFinished();
  }
}

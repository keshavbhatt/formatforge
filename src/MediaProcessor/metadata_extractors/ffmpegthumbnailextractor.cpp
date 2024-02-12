#include "ffmpegthumbnailextractor.h"

FFMpegThumbnailExtractor::FFMpegThumbnailExtractor(QObject *parent)
    : MetadataExtractor(parent), processedFilesCounter(0) {}

FFMpegThumbnailExtractor::~FFMpegThumbnailExtractor() {}

void FFMpegThumbnailExtractor::processMediaFiles(const QStringList &fileNames) {
  processedFilesCounter = 0;
  totalFilesToProcess = fileNames.size();

  QCoreApplication::processEvents();
  processNextMediaFile(fileNames);
}

void FFMpegThumbnailExtractor::processNextMediaFile(
    const QStringList &fileNames) {
  if (processedFilesCounter < totalFilesToProcess) {
    const QString &filePath = fileNames.at(processedFilesCounter);

    QProcess *ffmpegProcess = new QProcess(this);

    connect(ffmpegProcess,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [=](int exitCode, QProcess::ExitStatus exitStatus) {
              Q_UNUSED(exitStatus);

              QByteArray output = ffmpegProcess->readAllStandardOutput();

              if (exitCode != 0) {
                emit mediaProcessed(
                    filePath, QString("%1 Processing error. Exit code: %2")
                                  .arg(extractorId(), exitCode)
                                  .toUtf8());
              } else {
                emit mediaProcessed(filePath, output);
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

    // ffmpeg  -i l.webm -vf "thumbnail,select=gt(scene\,0.015)" -vsync vfr
    // "outd.jpg"

    // THUMBNAIL PLUGIN BASED(probably broken here) see notes.md
    // ffmpegProcess->start("ffmpeg", QStringList() << "-v"
    //                                              << "quiet"
    //                                              << "-i" << fileName << "-vf"
    //                                              <<
    //                                              "thumbnail,select=gt(scene\,0.015)"
    //                                              << "-vsync"
    //                                              << "vfr"
    //                                              << "-f"
    //                                              << "image2pipe"
    //                                              << "-");

    // ffmpeg -i l.webm -vf "select=gte(n\,100)" -vframes 1 out_img.png
    ffmpegProcess->start("ffmpeg", QStringList() << "-v"
                                                 << "quiet"
                                                 << "-i" << filePath << "-vf"
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

QString FFMpegThumbnailExtractor::extractorId() const {
  return metaObject()->className();
}

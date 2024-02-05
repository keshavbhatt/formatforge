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

    ffmpegProcess->start("ffmpeg", QStringList() << "-v"
                                                 << "quiet"
                                                 << "-i" << fileName << "-ss"
                                                 << "0"
                                                 << "-vframes"
                                                 << "1"
                                                 << "-f"
                                                 << "image2pipe"
                                                 << "-");
  } else {
    emit mediaProcessingFinished();
  }
}

// void FFMpegThumbnailExtractor::processMediaFiles(const QStringList
// &fileNames) {
//   processedFilesCounter = 0;

//   int totalFilesToProcess = fileNames.size();

//   for (int i = 0; i < totalFilesToProcess; ++i) {
//     const QString &fileName = fileNames.at(i);

//     QProcess *ffmpegProcess = new QProcess(this);
//     connect(ffmpegProcess,
//             QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
//             this,
//             [=](int exitCode, QProcess::ExitStatus exitStatus) {
//               Q_UNUSED(exitStatus);

//               processedFilesCounter++;
//               emit mediaProcessingProgress(processedFilesCounter,
//                                            totalFilesToProcess);
//               QByteArray output = ffmpegProcess->readAllStandardOutput();

//               if (exitCode != 0) {
//                 emit mediaProcessed(fileName, "processing_error");
//               } else {
//                 emit mediaProcessed(fileName, output);
//               }

//               QCoreApplication::processEvents();

//               // all files processed emit finish
//               if (processedFilesCounter == totalFilesToProcess) {
//                 emit mediaProcessingFinished();
//               }

//               ffmpegProcess->deleteLater();
//             });

//     ffmpegProcess->start("ffmpeg", QStringList() << "-v"
//                                                  << "quiet"
//                                                  << "-i" << fileName << "-ss"
//                                                  << "0"
//                                                  << "-vframes"
//                                                  << "1"
//                                                  << "-f"
//                                                  << "image2pipe"
//                                                  << "-");
//   }
// }

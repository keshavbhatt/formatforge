#include "Core/utils.h"

#include <QDir>
#include <QStringList>
#include <QTime>

Utils::Utils() {}

QString Utils::toCamelCase(const QString &s) {
  QStringList parts = s.split(' ', Qt::SkipEmptyParts);
  for (int i = 0, total = parts.size(); i < total; ++i)
    parts[i].replace(0, 1, parts[i][0].toUpper());

  return parts.join(" ");
}

QStringList Utils::getSupportedMultimediaMimeTypes() {
  return QStringList{
      "video",     "audio", "image", "x-shockwave-flash", "vnd.rn-realmedia",
      "vnd.ms-asf"};
}

QString Utils::durationStringToHumanReadable(const QString &duration) {
  double durationInSeconds = duration.toDouble();

  QTime durationTime = QTime(0, 0).addSecs(qRound(durationInSeconds));
  QString formattedDuration = durationTime.toString("hh:mm:ss");

  return formattedDuration;
}

QString Utils::getMediaTypeFromFFProbeStreamArray(const QJsonArray &streams) {
  for (const QJsonValue &streamValue : streams) {
    if (streamValue.isObject()) {
      QJsonObject streamObject = streamValue.toObject();

      if (streamObject.contains("codec_type")) {
        QString codecType = streamObject["codec_type"].toString();

        if (codecType == "video" || codecType == "audio") {
          return codecType;
        } else {
          // todo: add more cases ex subtitles, data, attachments
        }
      }
    }
  }
  return "Unknown";
}

QString Utils::getTabIconPath(const QString &name) {
  auto lower = name.toLower();
  if (lower.contains("video")) {
    return ":/primo/video.png";
  } else if (lower.contains("audio")) {
    return ":/primo/music.png";
  } else {
    return ":/primo/help_blue.png";
  }
}

QString Utils::computeFileHash(const QString &filePath) {
  QFileInfo fileInfo(filePath);

  if (!fileInfo.exists() || !fileInfo.isFile()) {
    qWarning() << "File does not exist or is not a regular file:" << filePath;
    return QString();
  }

  QString fileProperties =
      QString::number(fileInfo.size()) +
      QString::number(fileInfo.lastModified().toMSecsSinceEpoch()) +
      QString::number(fileInfo.metadataChangeTime().toMSecsSinceEpoch());

  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Unable to open file:" << filePath;
    return QString();
  }

  // read first 4096 bytes(4Kb) or entire file if smaller
  const qint64 bytesToRead = qMin(qint64(4096), fileInfo.size());
  QByteArray fileContent = file.read(bytesToRead);

  file.close();

  QCryptographicHash contentHash(QCryptographicHash::Sha256);
  contentHash.addData(fileContent);
  fileProperties += QString::fromLatin1(contentHash.result().toHex());

  QCryptographicHash hash(QCryptographicHash::Sha256);
  hash.addData(fileProperties.toUtf8());

  return QString(hash.result().toHex());
}

bool Utils::ensureDirectoryPath(const QString &path) {
  QDir dir(path);
  return dir.mkpath(".");
}

QString Utils::getFileNameFor(const QString &baseFileNae,
                              const QString &fileExetension) {
  return baseFileNae + "." + fileExetension;
}

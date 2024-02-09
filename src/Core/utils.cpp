#include "Core/utils.h"

#include <QStringList>
#include <QTime>

Utils::Utils() {}

QString Utils::toCamelCase(const QString &s) {
  QStringList parts = s.split(' ', Qt::SkipEmptyParts);
  for (int i = 0; i < parts.size(); ++i)
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

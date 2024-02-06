#include "videometadata.h"
#include <QDebug>

VideoMetaData::VideoMetaData() { m_mediaType = "Video"; }

void VideoMetaData::parse(const QJsonObject &jsonObject) {
  m_formatObject = jsonObject["format"].toObject();
  m_streamsArray = jsonObject["streams"].toArray();

  foreach (QJsonValue stream, m_streamsArray) {
      auto streamObject = stream.toObject();
    if (streamObject["codec_type"].toString().contains(m_mediaType,
                                                 Qt::CaseInsensitive)) {
      videoStreams.append(streamObject);
    }
  }
  // index = jsonObject["index"].toInt();
  // codecName = jsonObject["codec_name"].toString();
  // codecType = jsonObject["codec_type"].toString();
}

void VideoMetaData::printInfo() const {
  // qDebug() << "Stream" << index << "Type:" << codecType
  //          << "Codec:" << codecName;
}

QList<QJsonObject> VideoMetaData::getVideoStreams() const {
  return videoStreams;
}

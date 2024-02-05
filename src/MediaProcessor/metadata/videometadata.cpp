#include "videometadata.h"
#include <QDebug>

VideoMetaData::VideoMetaData() { m_mediaType = "Video"; }

void VideoMetaData::parse(const QJsonObject &jsonObject) {
  m_formatObject = jsonObject["format"].toObject();

  index = jsonObject["index"].toInt();
  codecName = jsonObject["codec_name"].toString();
  codecType = jsonObject["codec_type"].toString();
}

void VideoMetaData::printInfo() const {
  qDebug() << "Stream" << index << "Type:" << codecType
           << "Codec:" << codecName;
}

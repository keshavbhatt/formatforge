#include "audiometadata.h"
#include <QDebug>

AudioMetaData::AudioMetaData() { m_mediaType = "Audio"; }

void AudioMetaData::parse(const QJsonObject &jsonObject) {
  m_formatObject = jsonObject["format"].toObject();
  m_streamsArray = jsonObject["streams"].toArray();

  // index = jsonObject["index"].toInt();
  // codecName = jsonObject["codec_name"].toString();
  // codecType = jsonObject["codec_type"].toString();
}

void AudioMetaData::printInfo() const {
  // qDebug() << "Stream" << index << "Type:" << codecType
  //          << "Codec:" << codecName;
}

#include "audiometadata.h"
#include <QDebug>

AudioMetaData::AudioMetaData() { m_mediaType = "Audio"; }

void AudioMetaData::parse(const QJsonObject &jsonObject) {
  m_formatObject = jsonObject["format"].toObject();
  m_streamsArray = jsonObject["streams"].toArray();

  foreach (QJsonValue stream, m_streamsArray) {
    auto streamObject = stream.toObject();
    if (streamObject["codec_type"].toString().contains(m_mediaType,
                                                       Qt::CaseInsensitive)) {
      audioStreams.append(streamObject);
    }
  }
}

void AudioMetaData::printInfo() const {
  // qDebug() << "Stream" << index << "Type:" << codecType
  //          << "Codec:" << codecName;
}

QList<QJsonObject> AudioMetaData::getAudioStreams() const {
  return audioStreams;
}

#ifndef MEDIAMETADATA_H
#define MEDIAMETADATA_H

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class MediaMetaData {
public:
  virtual void parse(const QJsonObject &jsonObject) = 0;
  virtual void printInfo() const = 0;
  virtual ~MediaMetaData() {}

  QString mediaType() const;
  QJsonObject formatObject() const;
  QJsonArray streamsArray() const;
  int getStreamsCount() const;

  QString getStreamInfo() const;

protected:
  QString m_mediaType = "Unknown";
  QJsonObject m_formatObject;
  QJsonArray m_streamsArray;
};

inline QString MediaMetaData::mediaType() const { return m_mediaType; }

inline QJsonObject MediaMetaData::formatObject() const {
  return m_formatObject;
}

inline int MediaMetaData::getStreamsCount() const {
  return streamsArray().count();
}

inline QString MediaMetaData::getStreamInfo() const {
  QString streamInfo;

  int videoCount = 0;
  int audioCount = 0;
  int subtitleCount = 0;

  foreach (QJsonValue value, this->streamsArray()) {
    if (value.isObject()) {
      QJsonObject stream = value.toObject();

      if (stream["codec_type"].toString() == "video") {
        videoCount++;
      } else if (stream["codec_type"].toString() == "audio") {
        audioCount++;
      } else if (stream["codec_type"].toString() == "subtitle") {
        subtitleCount++;
      }
    }
  }

  if (videoCount > 0) {
    streamInfo += QString("%1 video track%2, ")
                      .arg(videoCount)
                      .arg(videoCount > 1 ? "s" : "");
  }
  if (audioCount > 0) {
    streamInfo += QString("%1 audio track%2, ")
                      .arg(audioCount)
                      .arg(audioCount > 1 ? "s" : "");
  }
  if (subtitleCount > 0) {
    streamInfo += QString("%1 subtitle track%2")
                      .arg(subtitleCount)
                      .arg(subtitleCount > 1 ? "s" : "");
  }

  return streamInfo.trimmed().chopped(1);
}

inline QJsonArray MediaMetaData::streamsArray() const { return m_streamsArray; }

#endif // MEDIAMETADATA_H

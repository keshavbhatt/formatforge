#ifndef MEDIAMETADATA_H
#define MEDIAMETADATA_H

#include <QJsonObject>
#include <QString>

class MediaMetaData {
public:
  virtual void parse(const QJsonObject &jsonObject) = 0;
  virtual void printInfo() const = 0;
  virtual ~MediaMetaData() {}

  QString mediaType() const;
  QJsonObject formatObject() const;

protected:
  QString m_mediaType = "Unknown";
  QJsonObject m_formatObject;
};

inline QString MediaMetaData::mediaType() const { return m_mediaType; }

inline QJsonObject MediaMetaData::formatObject() const {
  return m_formatObject;
}

#endif // MEDIAMETADATA_H

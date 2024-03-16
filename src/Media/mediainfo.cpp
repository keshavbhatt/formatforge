#include "mediainfo.h"
#include <QLocale>

MediaInfo::MediaInfo() : m_mediaMetaData(nullptr) {
  // TODO: hold file path and make generation of media info reproducible
  // the idea is to have ability to refresh this object based on the file
  m_generalFileInfo.clear();
  m_mediaInfo.clear();
}

MediaInfo::~MediaInfo() {}

MediaInfo::MediaInfo(const QFileInfo &fileInfo, MediaMetaData *mediaMetaData)
    : m_fileInfo(fileInfo), m_mediaMetaData(mediaMetaData) {

  populateFileInfo();
  populateMediaInfo();
}

void MediaInfo::populateFileInfo() {
  const QString keyName = "FileInfo::";

  QString sizeString = QLocale().formattedDataSize(m_fileInfo.size());

  QString creationDate = QLocale().toString(
      m_fileInfo.birthTime().toLocalTime(), QLocale::LongFormat);
  QString lastModifiedDate = QLocale().toString(
      m_fileInfo.lastModified().toLocalTime(), QLocale::LongFormat);
  QString lastAccessDate = QLocale().toString(
      m_fileInfo.lastRead().toLocalTime(), QLocale::LongFormat);

  m_generalFileInfo.append(
      qMakePair(QString(keyName + "name"), m_fileInfo.fileName()));
  m_generalFileInfo.append(qMakePair(QString(keyName + "size"), sizeString));
  m_generalFileInfo.append(
      qMakePair(QString(keyName + "creation_date"), creationDate));
  m_generalFileInfo.append(
      qMakePair(QString(keyName + "last_modified"), lastModifiedDate));
  m_generalFileInfo.append(
      qMakePair(QString(keyName + "last_accessed"), lastAccessDate));
}

void MediaInfo::populateMediaInfo() {
  if (m_mediaMetaData) {
    const QJsonObject &formatObject = m_mediaMetaData->formatObject();
    populateMediaInfoRecursive(formatObject);
    for (auto &pair : m_mediaInfo) {
      const QString keyName = "Format::" + pair.first;
      pair.first = keyName;
    }

    auto lastFormatItemIndex = m_mediaInfo.size();

    const QJsonArray &streamsArray = m_mediaMetaData->streamsArray();
    populateMediaInfoRecursive(streamsArray);
    for (int i = lastFormatItemIndex; i < m_mediaInfo.size(); ++i) {
      auto &pair = m_mediaInfo[i];
      const QString keyName = "Stream::" + pair.first;
      pair.first = keyName;
    }
  }
}

void MediaInfo::populateMediaInfoRecursive(const QJsonValue &value,
                                           const QString &prefix) {
  if (value.isObject()) {
    const QJsonObject object = value.toObject();
    const auto keys = object.keys();
    for (const QString &key : keys) {
      const QJsonValue &childValue = object.value(key);
      QString newPrefix = prefix.isEmpty() ? key : prefix + "." + key;
      populateMediaInfoRecursive(childValue, newPrefix);
    }
  } else if (value.isArray()) {
    const QJsonArray array = value.toArray();
    for (int i = 0; i < array.size(); ++i) {
      const QJsonValue &arrayValue = array.at(i);
      QString newPrefix = prefix + "[" + QString::number(i) + "]";
      populateMediaInfoRecursive(arrayValue, newPrefix);
    }
  } else {
    // value is not an object or array, add it to m_mediaInfo
    if (value.isDouble() &&
        qFuzzyCompare(value.toDouble(), qRound(value.toDouble()))) {
      // value is an integer, convert it to QString using QString::number
      m_mediaInfo.append(qMakePair(prefix, QString::number(value.toInt())));
    } else {
      m_mediaInfo.append(qMakePair(prefix, value.toString()));
    }
  }
}

QList<QPair<QString, QVariant>> MediaInfo::generalFileInfo() const {
  return m_generalFileInfo;
}

bool MediaInfo::isValid() {
  return !m_generalFileInfo.isEmpty() && !m_mediaInfo.isEmpty();
}

QList<QPair<QString, QVariant>> MediaInfo::mediaInfo() const {
  return m_mediaInfo;
}

QString MediaInfo::filePath() const { return m_fileInfo.filePath(); }

QString MediaInfo::fileName() const { return m_fileInfo.fileName(); }

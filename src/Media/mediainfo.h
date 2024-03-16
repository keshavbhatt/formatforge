#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QFileInfo>

#include <MediaProcessor/metadata/mediametadata.h>

class MediaInfo {
public:
  MediaInfo();

  MediaInfo(const QFileInfo &fileInfo, MediaMetaData *mediaMetaData);

  ~MediaInfo();

  bool isValid();

  QList<QPair<QString, QVariant>> generalFileInfo() const;

  QList<QPair<QString, QVariant>> mediaInfo() const;

  QString filePath() const;

  QString fileName() const;

private:
  QFileInfo m_fileInfo;
  MediaMetaData *m_mediaMetaData = nullptr;

  QList<QPair<QString, QVariant>> m_generalFileInfo;

  QList<QPair<QString, QVariant>> m_mediaInfo;

  void populateMediaInfo();
  void populateFileInfo();
  void populateMediaInfoRecursive(const QJsonValue &value,
                                  const QString &prefix = "");
};

#endif // MEDIAINFO_H

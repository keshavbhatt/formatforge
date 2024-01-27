#ifndef MIMEDATABASEMANAGER_H
#define MIMEDATABASEMANAGER_H

#include <QMimeDatabase>

class MimeDatabaseManager {
public:
  MimeDatabaseManager();

  static MimeDatabaseManager *getInstance();
  static void destroyInstance();

  QStringList getSupportedVideoMimeTypes();
  QStringList getSupportedAudioMimeTypes();

  QMimeType getMediaTypeByExtension(const QString &extension);

private:
  static MimeDatabaseManager *instance;

  QMimeDatabase mimeDb;
  QStringList getAllSupportedMediaMimeTypesBy(const QString &mimeFilterString);
};

#endif // MIMEDATABASEMANAGER_H

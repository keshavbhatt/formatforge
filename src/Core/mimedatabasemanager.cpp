#include "mimedatabasemanager.h"

MimeDatabaseManager *MimeDatabaseManager::instance = nullptr;

MimeDatabaseManager::MimeDatabaseManager() {}

MimeDatabaseManager *MimeDatabaseManager::getInstance() {
  if (!instance) {
    instance = new MimeDatabaseManager();
  }
  return instance;
}

void MimeDatabaseManager::destroyInstance() {
  if (instance) {
    delete instance;
    instance = nullptr;
  }
}

QStringList MimeDatabaseManager::getSupportedVideoMimeTypes() {
  return getAllSupportedMediaMimeTypesBy("audio/");
}

QStringList MimeDatabaseManager::getSupportedAudioMimeTypes() {
  return getAllSupportedMediaMimeTypesBy("video/");
}

QMimeType
MimeDatabaseManager::getMediaTypeByExtension(const QString &extension) {
  QMimeDatabase mimeDb;
  QMimeType mimeType = mimeDb.mimeTypeForFile("dummy." + extension);

  if (mimeType.isValid()) {
    return mimeType;
  } else {
    qWarning() << "MimeDatabaseManager::getMediaTypeByExtension"
               << "exetension" << extension << "not known.";
    return QMimeType();
  }
}

QMimeType MimeDatabaseManager::getMimeTypeForFile(const QString &filePath) {
  return mimeDb.mimeTypeForFile(filePath);
}

QStringList MimeDatabaseManager::getAllSupportedMediaMimeTypesBy(
    const QString &mimeFilterString) {
  QStringList allVideoMimeTypes;
  auto all_mime_types = mimeDb.allMimeTypes();
  for (const QMimeType &mimeType : qAsConst(all_mime_types)) {
    QString type = mimeType.name();
    if (type.startsWith(mimeFilterString)) {
      // filterout playlist types
      if (type.contains("playlist") == false) {
        allVideoMimeTypes << type;
      }
    }
  }
  return allVideoMimeTypes;
}

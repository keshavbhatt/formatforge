#include "cachestore.h"


CacheStore::CacheStore() : m_initialized(false) {
  m_cacheRootDirPath =
      QStandardPaths::writableLocation(QStandardPaths::CacheLocation) +
      "/Cache";
  this->setInitialized(ensureCacheRootDirExists(m_cacheRootDirPath));
}

void CacheStore::setInitialized(bool newInitialized) {
  m_initialized = newInitialized;
}

CacheStore &CacheStore::instance() {
  static CacheStore instance;
  return instance;
}

bool CacheStore::save(const QString &key, const QByteArray &data,
                      const QString &subdirectory) {
  if (!instance().initialized())
    return false;

  auto cacheDirPath =
      instance().cacheRootDirPath() + QDir::separator() + subdirectory;
  instance().ensureCacheSubdir(cacheDirPath);

  QString filePath = cacheDirPath + QDir::separator() + key;
  QFile file(filePath);
  if (file.open(QIODevice::WriteOnly)) {
    QDataStream stream(&file);
    stream << data;
    file.close();
    return true;
  }
  return false;
}

QByteArray CacheStore::load(const QString &key, const QString &subdirectory) {
  if (!instance().initialized())
    return QByteArray();

  QString filePath = instance().cacheRootDirPath() + QDir::separator() +
                     subdirectory + QDir::separator() + key;
  QFile file(filePath);
  if (file.open(QIODevice::ReadOnly)) {
    QDataStream stream(&file);
    QByteArray data;
    stream >> data;
    file.close();
    return data;
  }
  return QByteArray();
}

bool CacheStore::exists(const QString &key, const QString &subdirectory) {

  if (!instance().initialized())
    return false;

  QString filePath =
      instance().cacheRootDirPath() + "/" + subdirectory + "/" + key;
  return QFile::exists(filePath);
}

bool CacheStore::remove(const QString &key, const QString &subdirectory) {

  if (!instance().initialized())
    return false;

  QString filePath =
      instance().cacheRootDirPath() + "/" + subdirectory + "/" + key;
  return QFile::remove(filePath);
}

bool CacheStore::initialized() {
  if (m_initialized == false) {
    qWarning() << "CacheStore is not initialized! Caching will not work.";
  }
  return m_initialized;
}

QString CacheStore::cacheRootDirPath() const { return m_cacheRootDirPath; }

bool CacheStore::ensureCacheSubdir(const QString &path) {
  QDir dir(path);
  if (!dir.exists()) {
    return dir.mkpath(".");
  }
  return true;
}

bool CacheStore::ensureCacheRootDirExists(const QString &cacheRoot) {
  QDir dir(cacheRoot);
  if (!dir.exists()) {
    return dir.mkpath(".");
  }
  return true;
}

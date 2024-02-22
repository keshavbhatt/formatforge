#ifndef CACHESTORE_H
#define CACHESTORE_H

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QString>

class CacheStore {
public:
  static CacheStore &instance();

  static bool save(const QString &key, const QByteArray &data,
                   const QString &subdirectory = "");
  static QByteArray load(const QString &key, const QString &subdirectory = "");
  static bool exists(const QString &key, const QString &subdirectory = "");
  static bool remove(const QString &key, const QString &subdirectory = "");

  QString cacheRootDirPath() const;

private:
  CacheStore();

  static const QChar dir_path_separator;

  bool m_initialized;
  QString m_cacheRootDirPath;

  // delete copy constructor and assignment operator to prevent copying
  CacheStore(const CacheStore &) = delete;
  CacheStore &operator=(const CacheStore &) = delete;

  bool ensureCacheRootDirExists(const QString &cacheRoot);
  bool initialized();
  void setInitialized(bool newInitialized);
  bool ensureCacheSubdir(const QString &path);
};

#endif // CACHESTORE_H

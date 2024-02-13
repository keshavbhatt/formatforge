#ifndef UTILS_H
#define UTILS_H

#include <QCryptographicHash>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class Utils {
public:
  Utils();
  static QString toCamelCase(const QString &s);
  static QStringList getSupportedMultimediaMimeTypes();
  static QString durationStringToHumanReadable(const QString &duration);

  static QString getMediaTypeFromFFProbeStreamArray(const QJsonArray &streams);

  static QString getTabIconPath(const QString &name);

  static QString computeFileHash(const QString &filePath);

  static bool ensureDirectoryPath(const QString &path);
  static QString getFileNameFor(const QString &baseFileNae,
                                const QString &fileExetension);
};

#endif // UTILS_H

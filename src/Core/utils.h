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
};

#endif // UTILS_H

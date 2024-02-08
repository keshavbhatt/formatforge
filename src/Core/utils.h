#ifndef UTILS_H
#define UTILS_H

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
};

#endif // UTILS_H

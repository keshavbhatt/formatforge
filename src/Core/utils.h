#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils {
public:
  Utils();
  static QString toCamelCase(const QString &s);
  static QStringList getSupportedMultimediaMimeTypes();
  static QString durationStringToHumanReadable(const QString &duration);
};

#endif // UTILS_H

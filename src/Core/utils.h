#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils {
public:
  Utils();
    static QString toCamelCase(const QString &s);
    static QStringList getSupportedMultimediaMimeTypes();
};

#endif // UTILS_H

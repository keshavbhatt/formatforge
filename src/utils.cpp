#include "utils.h"

#include <QStringList>

Utils::Utils() {}

QString Utils::toCamelCase(const QString &s) {
  QStringList parts = s.split(' ', Qt::SkipEmptyParts);
  for (int i = 0; i < parts.size(); ++i)
    parts[i].replace(0, 1, parts[i][0].toUpper());

  return parts.join(" ");
}

QStringList Utils::getSupportedMultimediaMimeTypes() {
  return QStringList{"video", "audio", "image", "x-shockwave-flash"};
}

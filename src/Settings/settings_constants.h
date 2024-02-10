#ifndef SETTINGS_CONSTANTS_H
#define SETTINGS_CONSTANTS_H

#include <QStandardPaths>
#include <QtCore>

namespace SettingsConstants {

inline const QString OUTPUT_DIRECTORY_PATH =
    QStringLiteral("OUTPUT_DIRECTORY_PATH");

inline const QString FILE_SELECTOR_LAST_USED_PATH =
    QStringLiteral("FILE_SELECTOR_LAST_USED_PATH");

inline const QString DO_NOT_USE_NATIVE_FILE_SELECTOR =
    QStringLiteral("DO_NOT_USE_NATIVE_FILE_SELECTOR");

} // namespace SettingsConstants

#endif // SETTINGS_CONSTANTS_H

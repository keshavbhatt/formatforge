#ifndef SETTINGS_CONSTANTS_H
#define SETTINGS_CONSTANTS_H

#include <QStandardPaths>
#include <QtCore>
#include <qmetaobject.h>

namespace SettingsConstants {

Q_NAMESPACE

enum SettingKeys {
  OUTPUT_DIRECTORY_PATH,
  FILE_SELECTOR_LAST_USED_PATH,
  DO_NOT_USE_NATIVE_FILE_SELECTOR,
  PRESERVE_HIERARCHY_IN_OUTPUT_DIR
};
Q_ENUM_NS(SettingKeys)

inline QString SettingsConstantsGetNameFor(SettingKeys key) {
  QMetaEnum metaEnum = QMetaEnum::fromType<SettingsConstants::SettingKeys>();
  const char *valueToKey = metaEnum.valueToKey(key);

  if (valueToKey) {
    return QString(valueToKey);
  } else {
    qWarning() << "SettingKey not found for value:" << key;
    return QString();
  }
}

inline QVariant SettingsConstantsGetDefaultFor(SettingKeys key) {
  switch (key) {
  case SettingKeys::OUTPUT_DIRECTORY_PATH:
    return QVariant(
        QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
  case SettingKeys::FILE_SELECTOR_LAST_USED_PATH:
    return QVariant(QDir::homePath());
  case SettingKeys::DO_NOT_USE_NATIVE_FILE_SELECTOR:
    return QVariant(false);
  case SettingKeys::PRESERVE_HIERARCHY_IN_OUTPUT_DIR:
    return QVariant(true);
  default:
    return QVariant();
  }
}

} // namespace SettingsConstants

// Q_DECLARE_METATYPE(SettingsConstants::SettingKeys)

#endif // SETTINGS_CONSTANTS_H

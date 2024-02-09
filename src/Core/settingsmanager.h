#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "settings_constants.h"
#include <QSettings>

using namespace SettingsConstants;

class SettingsManager {

public:

  static QSettings &settings();

private:
  static SettingsManager &instance();

  SettingsManager();

  QSettings m_settings;
};

#endif // SETTINGSMANAGER_H

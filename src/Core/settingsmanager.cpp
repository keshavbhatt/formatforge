#include "settingsmanager.h"

SettingsManager &SettingsManager::instance() {
  static SettingsManager instance;
  return instance;
}

QSettings &SettingsManager::settings() { return instance().m_settings; }

SettingsManager::SettingsManager() {}

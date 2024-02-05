#include "defaultpresetreader.h"
#include "Core/mimedatabasemanager.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMimeType>

DefaultPresetReader *DefaultPresetReader::instance = nullptr;

DefaultPresetReader::DefaultPresetReader(QObject *parent) : QObject{parent} {

  QFile file(":/defaultPresets.json");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qWarning() << "Failed to open " << file.fileName()
               << " from resource bundle.";
    return;
  }

  QByteArray jsonData = file.readAll();
  file.close();

  QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

  if (jsonDoc.isNull()) {
    qWarning() << "Failed to parse preset data from " << file.fileName();
    return;
  }

  QJsonObject presetsObject = jsonDoc.object()["presets"].toObject();

  auto allKeys = presetsObject.keys();
  for (const QString &presetKey : allKeys) {
    QJsonObject presetObject = presetsObject[presetKey].toObject();

    bool presetExists = false;
    for (const Preset &existingPreset : qAsConst(loadedPresets)) {
      if (existingPreset.getLabel() == presetKey) {
        presetExists = true;
        break;
      }
    }

    if (!presetExists) {
      loadedPresets.append(Preset(presetObject, presetKey));
    }
  }
}

QList<Preset> DefaultPresetReader::getPresetsByExetension(
    const QString &exetensionName) const {
  QList<Preset> presetsByExetension;
  for (const Preset &preset : qAsConst(loadedPresets)) {
    if (preset.getExtension() == exetensionName) {
      presetsByExetension.append(preset);
    }
  }
  return presetsByExetension;
}

Preset DefaultPresetReader::getPresetByKey(const QString &key) const {
  foreach (auto preset, loadedPresets) {
    if (preset.getKey() == key) {
      return preset;
    }
  }
  return Preset("Null", "Null", "Null", "Null", "Null");
}

QSet<QString> DefaultPresetReader::getLoadedOutputExetensions() {
  QStringList k;
  foreach (auto preset, loadedPresets) {
    k.append(preset.getExtension());
  }
  return QSet<QString>(k.begin(), k.end());
}

QList<Preset> DefaultPresetReader::getLoadedPresets() const {
  return loadedPresets;
}

DefaultPresetReader *DefaultPresetReader::getInstance() {
  if (!instance) {
    instance = new DefaultPresetReader();
  }
  return instance;
}

void DefaultPresetReader::destroyInstance() {
  if (instance) {
    delete instance;
    instance = nullptr;
  }
}

void DefaultPresetReader::printAllPresets() {
  qDebug() << "Loaded Presets:";
  for (const Preset &preset : qAsConst(loadedPresets)) {
    qDebug() << "Label:" << preset.getLabel();
    qDebug() << "Params:" << preset.getParams();
    qDebug() << "Extension:" << preset.getExtension();
    qDebug() << "Category:" << preset.getCategory();
    qDebug() << "-----------------------";
  }
}

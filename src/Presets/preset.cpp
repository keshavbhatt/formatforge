#include "preset.h"

Preset::Preset(const QJsonObject &jsonObject, const QString &presetKey) {
  fromJson(jsonObject);
  setPresetKey(presetKey);
}

Preset::Preset(const QString &label, const QString &params,
               const QString &extension, const QString &category,
               const QString &presetKey)
    : label(label), params(params), extension(extension), category(category),
      key(presetKey) {}

QString Preset::getLabel() const { return label; }

QString Preset::getParams() const { return params; }

QString Preset::getExtension() const { return extension; }

QString Preset::getCategory() const { return category; }

void Preset::fromJson(const QJsonObject &jsonObject) {
  label = jsonObject["label"].toString();
  params = jsonObject["params"].toString();
  extension = jsonObject["extension"].toString();
  category = jsonObject["category"].toString();
}

QString Preset::getKey() const { return key; }

void Preset::setPresetKey(const QString &newPresetKey) {
  key = newPresetKey;
}

QJsonObject Preset::toJson() const {
  QJsonObject jsonObject;
  jsonObject["key"] = key;
  jsonObject["label"] = label;
  jsonObject["params"] = params;
  jsonObject["extension"] = extension;
  jsonObject["category"] = category;
  return jsonObject;
}

void Preset::print() const {
  qDebug() << "------------------";
  qDebug() << "Key:" << getKey();
  qDebug() << "Label:" << getLabel();
  qDebug() << "Params:" << getParams();
  qDebug() << "Extension:" << getExtension();
  qDebug() << "Category:" << getCategory();
  qDebug() << "------------------";
}

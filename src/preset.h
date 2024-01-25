#ifndef PRESET_H
#define PRESET_H

#include <QJsonObject>
#include <QString>

class Preset {
public:
  Preset(const QString &label, const QString &params, const QString &extension,
         const QString &category, const QString &presetKey);

  Preset(const QJsonObject &jsonObject, const QString &presetKey);

  QString getLabel() const;

  QString getParams() const;

  QString getExtension() const;

  QString getCategory() const;

  QJsonObject toJson() const;

  void print() const;

  void setPresetKey(const QString &newPresetKey);

  QString getKey() const;

private:
  void fromJson(const QJsonObject &jsonObject);

  QString label;
  QString params;
  QString extension;
  QString category;
  QString key;
};

#endif // PRESET_H

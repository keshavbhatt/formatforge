#ifndef DEFAULTPRESETREADER_H
#define DEFAULTPRESETREADER_H

#include "preset.h"

#include <QObject>

class DefaultPresetReader : public QObject {
  Q_OBJECT

public:
  static DefaultPresetReader *getInstance();
  static void destroyInstance();

  void printAllPresets();

  QList<Preset> getLoadedPresets() const;

  QList<Preset> getPresetsByExetension(const QString &exetensionName) const;

  Preset getPresetByKey(const QString &key) const;

private:
  explicit DefaultPresetReader(QObject *parent = nullptr);

  static DefaultPresetReader *instance;

  QList<Preset> loadedPresets;
};

#endif // DEFAULTPRESETREADER_H

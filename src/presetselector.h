#ifndef PRESETSELECTOR_H
#define PRESETSELECTOR_H

#include "defaultpresetreader.h"
#include "presettabwidget.h"
#include <QTabWidget>
#include <QWidget>

namespace Ui {
class PresetSelector;
}

class PresetSelector : public QWidget {
  Q_OBJECT

public:
  explicit PresetSelector(QWidget *parent = nullptr);
  ~PresetSelector();

  void setLayoutContentsMargins(int margin);

private:
  Ui::PresetSelector *ui;
  QStringList presetTypes;

  void loadPresets();
  void createCategoryTab(const QString &name = "");
  QStringList getCurrentTabNames();
  PresetTabWidget *getTabByName(QTabWidget *tabWidget = nullptr,
                                const QString &tabName = "");
};

#endif // PRESETSELECTOR_H

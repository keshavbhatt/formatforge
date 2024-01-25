#ifndef OUTPUTSETTINGPAGE_H
#define OUTPUTSETTINGPAGE_H

#include <QWidget>
#include <presetselector.h>

namespace Ui {
class OutputSettingPage;
}

class OutputSettingPage : public QWidget {
  Q_OBJECT

public:
  explicit OutputSettingPage(QWidget *parent = nullptr);
  ~OutputSettingPage();

  void showPresetSelector();
signals:
  void nextPage();

private:
  Ui::OutputSettingPage *ui;

  PresetSelector *presetSelector = nullptr;
};

#endif // OUTPUTSETTINGPAGE_H

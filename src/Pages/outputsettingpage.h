#ifndef OUTPUTSETTINGPAGE_H
#define OUTPUTSETTINGPAGE_H

#include "Presets/widgets/presetselector.h"
#include "mediapage.h"
#include "page.h"
#include <QWidget>

namespace Ui {
class OutputSettingPage;
}

class OutputSettingPage : public Page {
  Q_OBJECT

public:
  explicit OutputSettingPage(QWidget *parent = nullptr);
  ~OutputSettingPage();

  void showPresetSelector();

private:
  Ui::OutputSettingPage *ui;

  PresetSelector *presetSelector = nullptr;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  void updatePage();
  MediaPage *getMediaPage();

  void updatePageStatusMessage();
  signals:
  void presetSelectionChanged(const Preset &preset);

public slots:
  void activate();

public:
  bool isEnabled();
  void setNextPage(Page *nextPage);
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setPreviousPage(Page *prevPage);
  bool hasValidSelectedPreset();
  void clearPresetSelection();

private slots:
  void editSelectedPreset();
};

#endif // OUTPUTSETTINGPAGE_H

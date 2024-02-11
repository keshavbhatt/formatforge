#ifndef OUTPUTSETTINGPAGE_H
#define OUTPUTSETTINGPAGE_H

#include "Presets/widgets/presetselector.h"
#include "Settings/settingsmanager.h"
#include "mediapage.h"
#include "page.h"

#include <QFileDialog>
#include <QWidget>

namespace Ui {
class OutputSettingPage;
}

class OutputSettingPage : public Page {
  Q_OBJECT

public:
  explicit OutputSettingPage(QWidget *parent = nullptr);
  ~OutputSettingPage();

  bool isEnabled();
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setNextPage(Page *nextPage);
  void setPreviousPage(Page *prevPage);

  void showPresetSelector();
  bool hasValidSelectedPreset();
  void clearPresetSelection();

  Preset getSelectedPreset() const;
  QString getOutputDirectoryPath() const;
  bool getPreserveHierarchy();
public slots:
  void activate();
  void selectOutputDirectory();

signals:
  void presetSelectionChanged(const Preset &preset);

private:
  Ui::OutputSettingPage *ui;

  PresetSelector *presetSelector = nullptr;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  QString m_outputDirectoryPath;

  void updatePage();
  MediaPage *getMediaPage();
  void updatePageStatusMessage();

private slots:
  void editSelectedPreset();
};

#endif // OUTPUTSETTINGPAGE_H

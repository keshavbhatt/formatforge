#include "outputsettingpage.h"
#include "mediapage.h"
#include "ui_outputsettingpage.h"

OutputSettingPage::OutputSettingPage(QWidget *parent)
    : Page(parent), ui(new Ui::OutputSettingPage) {
  ui->setupUi(this);
  showPresetSelector();
}

void OutputSettingPage::showPresetSelector() {
  if (presetSelector) {
    presetSelector->disconnect();
    presetSelector->deleteLater();
    presetSelector = nullptr;
  }

  presetSelector = new PresetSelector(this);
  presetSelector->setLayoutContentsMargins(0);
  connect(presetSelector, &PresetSelector::presetSelectionChanged, this,
          [=](const Preset &selectedPreset) { this->updatePage(); });
  ui->presetSelectorLayout->addWidget(presetSelector);
}

void OutputSettingPage::updatePage() {
  if (presetSelector) {
    bool presetSelected = presetSelector->hasValidSelectedPreset();
    ui->nextPushButton->setEnabled(presetSelected);
  } else {
    ui->nextPushButton->setEnabled(false);
  }
}

bool OutputSettingPage::isEnabled() {
  Page *mediaPage = qobject_cast<MediaPage *>(getPreviousPage());
  if (mediaPage) {
    return mediaPage->isEnabled();
  } else {
    qWarning() << Q_FUNC_INFO
               << "Casting failed, is previousPage for OutputSettingPage set "
                  "correctly?";
    return false;
  }
}

void OutputSettingPage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

Page *OutputSettingPage::getNextPage() const { return m_nextPage; }

Page *OutputSettingPage::getPreviousPage() const { return m_prevPage; }

void OutputSettingPage::setPreviousPage(Page *prevPage) {
  m_prevPage = prevPage;
}

void OutputSettingPage::activate() {
  if (presetSelector) {
    presetSelector->clearSelection();
  }
  this->updatePage();
}

OutputSettingPage::~OutputSettingPage() { delete ui; }

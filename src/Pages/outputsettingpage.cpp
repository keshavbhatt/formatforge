#include "outputsettingpage.h"
#include "ui_outputsettingpage.h"

OutputSettingPage::OutputSettingPage(QWidget *parent)
    : Page(parent), ui(new Ui::OutputSettingPage) {
  ui->setupUi(this);
  showPresetSelector();

  connect(ui->nextPushButton, &QPushButton::clicked, this,
          [=]() { emit goToNextPage(); });

  connect(ui->editSelectedPresetPushButton, &QPushButton::clicked, this,
          &OutputSettingPage::editSelectedPreset);
}

void OutputSettingPage::editSelectedPreset() {}

void OutputSettingPage::showPresetSelector() {
  if (presetSelector) {
    presetSelector->disconnect();
    presetSelector->deleteLater();
    presetSelector = nullptr;
  }

  presetSelector = new PresetSelector(this);
  presetSelector->setLayoutContentsMargins(0);
  connect(presetSelector, &PresetSelector::presetSelectionChanged, this, [=]() {
    this->updatePage();
    emit presetSelectionChanged(presetSelector->getSelectedPreset());
  });
  ui->presetSelectorLayout->addWidget(presetSelector);
}

bool OutputSettingPage::hasValidSelectedPreset() {
  if (presetSelector) {
    return presetSelector->hasValidSelectedPreset();
  }
  return false;
}

void OutputSettingPage::clearPresetSelection() {
  if (presetSelector) {
    return presetSelector->clearSelection();
  }
}

void OutputSettingPage::updatePage() {
  if (presetSelector) {
    bool presetSelected = presetSelector->hasValidSelectedPreset();
    ui->nextPushButton->setEnabled(presetSelected);
    ui->editSelectedPresetPushButton->setEnabled(presetSelected);
  } else {
    ui->nextPushButton->setEnabled(false);
    ui->editSelectedPresetPushButton->setEnabled(false);
  }
}

MediaPage *OutputSettingPage::getMediaPage() {
  MediaPage *mediaPage = qobject_cast<MediaPage *>(getPreviousPage());

  return mediaPage;
}

bool OutputSettingPage::isEnabled() {
  MediaPage *mediaPage = getMediaPage();
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

void OutputSettingPage::activate() { this->updatePage(); }

OutputSettingPage::~OutputSettingPage() { delete ui; }

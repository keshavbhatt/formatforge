#include "outputsettingpage.h"
#include "ui_outputsettingpage.h"

OutputSettingPage::OutputSettingPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::OutputSettingPage) {
  ui->setupUi(this);
  showPresetSelector();
}

void OutputSettingPage::showPresetSelector() {
  if (presetSelector) {
    presetSelector->deleteLater();
    presetSelector = nullptr;
  }

  presetSelector = new PresetSelector(this);
  presetSelector->setLayoutContentsMargins(0);
  ui->presetSelectorLayout->addWidget(presetSelector);
}

OutputSettingPage::~OutputSettingPage() { delete ui; }

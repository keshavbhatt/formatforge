#include "outputsettingpage.h"
#include "ui_outputsettingpage.h"

OutputSettingPage::OutputSettingPage(QWidget *parent)
    : Page(parent), ui(new Ui::OutputSettingPage) {
  ui->setupUi(this);
  showPresetSelector();

  ui->changeOutputDirPushButton->setIcon(QIcon(":/primo/folder_open.png"));
  ui->nextPushButton->setIcon(QIcon(":/primo/next.png"));
  connect(ui->nextPushButton, &QPushButton::clicked, this,
          [=]() { emit goToNextPage(); });

  ui->editSelectedPresetPushButton->setIcon(QIcon(":/primo/pencil.png"));
  connect(ui->editSelectedPresetPushButton, &QPushButton::clicked, this,
          &OutputSettingPage::editSelectedPreset);

  // OUTPUT PRESERVE HIERARCHY
  auto preserveHierarchy =
      SettingsManager::settings()
          .value(SettingsConstantsGetNameFor(
                     SettingKeys::PRESERVE_HIERARCHY_IN_OUTPUT_DIR),
                 true)
          .toBool();
  ui->preserveHierarchyCheckBox->setChecked(preserveHierarchy);
  connect(ui->preserveHierarchyCheckBox, &QCheckBox::toggled,
          [=](bool checked) {
            SettingsManager::settings().setValue(
                SettingsConstantsGetNameFor(
                    SettingKeys::PRESERVE_HIERARCHY_IN_OUTPUT_DIR),
                checked);
          });

  // OUTPUT DIRECTORY
  ui->outputDirectoryLineEdit->setFocusPolicy(Qt::NoFocus);
  ui->outputDirectoryLineEdit->setReadOnly(true);

  m_outputDirectoryPath =
      SettingsManager::settings()
          .value(
              SettingsConstantsGetNameFor(SettingKeys::OUTPUT_DIRECTORY_PATH),
              SettingsConstantsGetDefaultFor(SettingKeys::OUTPUT_DIRECTORY_PATH)
                  .toString())
          .toString();
  ui->outputDirectoryLineEdit->setText(m_outputDirectoryPath);
  connect(ui->changeOutputDirPushButton, &QPushButton::clicked, this,
          &OutputSettingPage::selectOutputDirectory);
}

void OutputSettingPage::selectOutputDirectory() {

  auto doNotUseNativeFileSelector =
      SettingsManager::settings()
          .value(SettingsConstantsGetNameFor(
                     SettingKeys::DO_NOT_USE_NATIVE_FILE_SELECTOR),
                 SettingsConstantsGetDefaultFor(
                     SettingKeys::DO_NOT_USE_NATIVE_FILE_SELECTOR))
          .toBool();

  QString newOutputDirectory;

  if (doNotUseNativeFileSelector) {
    newOutputDirectory = QFileDialog::getExistingDirectory(
        this, tr("Select Output Directory"), m_outputDirectoryPath,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks |
            QFileDialog::DontUseNativeDialog);
  } else {
    newOutputDirectory = QFileDialog::getExistingDirectory(
        this, tr("Select Output Directory"), m_outputDirectoryPath,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  }

  if (!newOutputDirectory.isEmpty()) {
    m_outputDirectoryPath = newOutputDirectory;
    ui->outputDirectoryLineEdit->setText(m_outputDirectoryPath);
    SettingsManager::settings().setValue(
        SettingsConstantsGetNameFor(SettingKeys::OUTPUT_DIRECTORY_PATH),
        m_outputDirectoryPath);
  }
}

QString OutputSettingPage::getOutputDirectoryPath() const {
  return m_outputDirectoryPath;
}

bool OutputSettingPage::getPreserveHierarchy() {
  return ui->preserveHierarchyCheckBox->isChecked();
}

void OutputSettingPage::editSelectedPreset() { Q_UNIMPLEMENTED(); }

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
    this->updatePageStatusMessage();
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

Preset OutputSettingPage::getSelectedPreset() const {
  return presetSelector->getSelectedPreset();
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

void OutputSettingPage::activate() {
  this->updatePage();
  this->updatePageStatusMessage();
}

void OutputSettingPage::updatePageStatusMessage() {
  QString message = "Select a Preset";
  if (presetSelector && presetSelector->hasValidSelectedPreset()) {
    auto selectedPreset = presetSelector->getSelectedPreset();
    message = "Selected preset: " + selectedPreset.getLabel();
  }
  emit updateStatusMessage(message);
}

OutputSettingPage::~OutputSettingPage() { delete ui; }

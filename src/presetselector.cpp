#include "presetselector.h"
#include "mimedatabasemanager.h"
#include "presettabwidget.h"
#include "ui_presetselector.h"
#include "utils.h"

PresetSelector::PresetSelector(QWidget *parent)
    : QWidget(parent), ui(new Ui::PresetSelector) {
  ui->setupUi(this);

  loadPresets();
}

QStringList PresetSelector::getCurrentTabNames() {

  QStringList tabNames;
  for (int i = 0; i < ui->tabWidget->count(); ++i) {
    PresetTabWidget *presetTabWidget =
        qobject_cast<PresetTabWidget *>(ui->tabWidget->widget(i));

    if (presetTabWidget) {
      tabNames.append(presetTabWidget->getTabName());
    }
  }
  return tabNames;
}

PresetTabWidget *PresetSelector::getTabByName(QTabWidget *tabWidget,
                                              const QString &tabName) {
  auto currentTabNames = this->getCurrentTabNames();
  for (int i = 0; i < currentTabNames.count(); ++i) {
    PresetTabWidget *presetTabWidget =
        qobject_cast<PresetTabWidget *>(tabWidget->widget(i));

    if (currentTabNames.at(i) == tabName) {
      return presetTabWidget;
    }
  }
  return nullptr;
}

void PresetSelector::createCategoryTab(const QString &name) {
  QString _name = name.trimmed();
  auto targetIndex = ui->tabWidget->count();
  if (_name.isEmpty()) {
    _name = "Tab " + QString::number(targetIndex);
  }
  ui->tabWidget->insertTab(
      targetIndex, new PresetTabWidget(ui->tabWidget, name.toLower()), _name);
}

void PresetSelector::loadPresets() {

  QList<Preset> defaultPresets =
      DefaultPresetReader::getInstance()->getLoadedPresets();

  // create tab for supported multimedia mime types
  auto multimediaMimeTypes = Utils::getSupportedMultimediaMimeTypes();
  foreach (const Preset &preset, defaultPresets) {
    QMimeType mediaTypeByExtension =
        MimeDatabaseManager::getInstance()->getMediaTypeByExtension(
            preset.getExtension());
    QString type = mediaTypeByExtension.name().split("/").first();
    if (presetTypes.contains(type) == false &&
        multimediaMimeTypes.contains(type)) {
      presetTypes.append(type);
      createCategoryTab(Utils::toCamelCase(type));
    }
  }

  // load them in view
  foreach (const Preset &preset, defaultPresets) {
    auto currentTabNames = this->getCurrentTabNames();
    for (int i = 0; i < currentTabNames.count(); ++i) {
      auto currentTabName = currentTabNames.at(i);
      PresetTabWidget *presetTabWidget =
          this->getTabByName(ui->tabWidget, currentTabNames.at(i));
      if (presetTabWidget) {
        QMimeType mediaTypeByExtension =
            MimeDatabaseManager::getInstance()->getMediaTypeByExtension(
                preset.getExtension());
        if (mediaTypeByExtension.name().contains(currentTabName,
                                                 Qt::CaseInsensitive)) {
          presetTabWidget->addExetension(preset.getExtension().toUpper());
        }
      }
    }
  }
}

void PresetSelector::setLayoutContentsMargins(int margin) {
  ui->verticalLayout->setContentsMargins(margin, margin, margin, margin);
}

PresetSelector::~PresetSelector() { delete ui; }

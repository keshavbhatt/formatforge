#include "presetselector.h"
#include "Core/mimedatabasemanager.h"
#include "Core/utils.h"
#include "presettabwidget.h"
#include "ui_presetselector.h"

PresetSelector::PresetSelector(QWidget *parent)
    : QWidget(parent), ui(new Ui::PresetSelector) {
  ui->setupUi(this);

  connect(ui->tabWidget, &QTabWidget::currentChanged, this,
          &PresetSelector::clearSelection);

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

  ui->tabWidget->insertTab(targetIndex,
                           new PresetTabWidget(ui->tabWidget, name.toLower()),
                           QIcon(getTabIconPath(_name)), _name);
}

QString PresetSelector::getTabIconPath(const QString &name) {
  auto lower = name.toLower();
  if (lower.contains("video")) {
    return ":/primo/video.png";
  } else if (lower.contains("audio")) {
    return ":/primo/music.png";
  } else {
    return ":/primo/help_blue.png";
  }
}

void PresetSelector::loadPresets() {

  QList<Preset> defaultPresets =
      DefaultPresetReader::getInstance()->getLoadedPresets();

  // DefaultPresetReader::getInstance()->printAllPresets();

  // create tab for supported multimedia mime types
  auto multimediaMimeTypes = Utils::getSupportedMultimediaMimeTypes();
  foreach (const Preset &preset, defaultPresets) {
    QMimeType mediaTypeByExtension =
        MimeDatabaseManager::getInstance()->getMediaTypeByExtension(
            preset.getExtension());
    QString type = mediaTypeByExtension.name().split("/").first();
    QString type2 = mediaTypeByExtension.name().split("/").last();
    QString tabTitle = "other";
    tabTitle = type.contains("application") ? tabTitle : type;

    if (presetTypes.contains(tabTitle) == false &&
        (multimediaMimeTypes.contains(type) ||
         multimediaMimeTypes.contains(type2))) {
      presetTypes.append(tabTitle);
      createCategoryTab(Utils::toCamelCase(tabTitle));
    }

    // if (presetTypes.contains(type) == false &&
    //     !multimediaMimeTypes.contains(type)) {
    //   qDebug() << "skipping preset for mime type:"
    //            << mediaTypeByExtension.name();
    // }
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
                                                 Qt::CaseInsensitive) ||
            mediaTypeByExtension.name().contains("application",
                                                 Qt::CaseInsensitive)) {
          presetTabWidget->addExetension(preset.getExtension().toUpper());
        }
      }
    }
  }

  auto currentTabNames = this->getCurrentTabNames();
  for (int i = 0; i < currentTabNames.count(); ++i) {
    PresetTabWidget *presetTabWidget =
        this->getTabByName(ui->tabWidget, currentTabNames.at(i));
    connect(presetTabWidget, &PresetTabWidget::presetSelectionChanged, this,
            [=](const Preset &selectedPreset) {
              this->selectedPreset = selectedPreset;
              emit presetSelectionChanged();
            });
  }
}

void PresetSelector::setLayoutContentsMargins(int margin) {
  ui->verticalLayout->setContentsMargins(margin, margin, margin, margin);
}

void PresetSelector::clearSelection() {
  auto currentTabNames = this->getCurrentTabNames();
  for (int i = 0; i < currentTabNames.count(); ++i) {
    PresetTabWidget *presetTabWidget =
        this->getTabByName(ui->tabWidget, currentTabNames.at(i));
    if (presetTabWidget) {
      presetTabWidget->clearSelection();
    }
  }
  this->removeSelectedPreset();
}

void PresetSelector::removeSelectedPreset() {
  this->selectedPreset = Preset();
  emit presetSelectionChanged();
}

bool PresetSelector::hasValidSelectedPreset() {
  return selectedPreset.isValid();
}

Preset PresetSelector::getSelectedPreset() const { return selectedPreset; }

PresetSelector::~PresetSelector() { delete ui; }

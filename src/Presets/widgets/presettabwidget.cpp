#include "presettabwidget.h"
#include "Presets/defaultpresetreader.h"
#include "ui_presettabwidget.h"

PresetTabWidget::PresetTabWidget(QWidget *parent, QString name)
    : QWidget(parent), ui(new Ui::PresetTabWidget) {
  ui->setupUi(this);

  this->tabName = name;

  connect(ui->exetensionListWidget, &QListWidget::itemClicked, this,
          &PresetTabWidget::exetensionListWidgetItemClicked);

  connect(ui->optionsListWidget, &QListWidget::itemClicked, this,
          &PresetTabWidget::optionsListWidgeItemClicked);
}

PresetTabWidget::~PresetTabWidget() { delete ui; }

QString PresetTabWidget::getTabName() const { return tabName; }

void PresetTabWidget::addExetension(const QString &exetensionName) {

  if (addedExtensions.contains(exetensionName) == false) {
    addedExtensions.append(exetensionName);
    ui->exetensionListWidget->addItem(exetensionName);
  }
}

void PresetTabWidget::clearSelection() {
  ui->exetensionListWidget->clearSelection();

  // force re-selection of preset
  ui->optionsListWidget->clear();
}

void PresetTabWidget::exetensionListWidgetItemClicked(QListWidgetItem *item) {
  // load related presets in the optionsListWidget
  ui->optionsListWidget->blockSignals(true);
  QList<Preset> presetsByExetension =
      DefaultPresetReader::getInstance()->getPresetsByExetension(
          item->text().toLower());

  ui->optionsListWidget->clear();

  for (int i = 0; i < presetsByExetension.count(); ++i) {
    QListWidgetItem *item =
        new QListWidgetItem(presetsByExetension.at(i).getLabel());
    item->setData(Qt::UserRole, presetsByExetension.at(i).getKey());
    ui->optionsListWidget->addItem(item);
  }
  ui->optionsListWidget->blockSignals(false);
}

void PresetTabWidget::optionsListWidgeItemClicked(QListWidgetItem *item) {
  if (item) {
    // load preset's in the editPresetWidget
    Preset presetByKey = DefaultPresetReader::getInstance()->getPresetByKey(
        item->data(Qt::UserRole).toString());

    emit presetSelectionChanged(presetByKey);

    qDebug() << "------------------";
    qDebug() << "Key:" << presetByKey.getKey();
    qDebug() << "Label:" << presetByKey.getLabel();
    qDebug() << "Params:" << presetByKey.getParams();
    qDebug() << "Extension:" << presetByKey.getExtension();
    qDebug() << "Category:" << presetByKey.getCategory();
    qDebug() << "------------------";
  }
}

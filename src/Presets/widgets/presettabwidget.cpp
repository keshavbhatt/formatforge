#include "presettabwidget.h"
#include "Presets/defaultpresetreader.h"
#include "ui_presettabwidget.h"

#include <Core/utils.h>

PresetTabWidget::PresetTabWidget(QWidget *parent, QString name)
    : QWidget(parent), ui(new Ui::PresetTabWidget) {
  ui->setupUi(this);

  this->tabName = name;

  ui->exetensionListWidget->setEmptyText(tr("No exetensions found"));
  ui->optionsListWidget->setEmptyText(
      tr("Select an exetension to see available presets"));

  connect(ui->exetensionListWidget, &QListWidget::itemSelectionChanged, this,
          &PresetTabWidget::exetensionListWidgetItemSelectionChanged);

  connect(ui->optionsListWidget, &QListWidget::itemSelectionChanged, this,
          &PresetTabWidget::optionsListWidgetItemSelectionChanged);
}

PresetTabWidget::~PresetTabWidget() { delete ui; }

QString PresetTabWidget::getTabName() const { return tabName; }

void PresetTabWidget::addExetension(const QString &exetensionName,
                                    const QString &type) {

  if (addedExtensions.contains(exetensionName) == false) {
    addedExtensions.append(exetensionName);
    QListWidgetItem *item =
        new QListWidgetItem(QIcon(Utils::getTabIconPath(type)), exetensionName,
                            ui->exetensionListWidget);
    ui->exetensionListWidget->addItem(item);
  }
}

void PresetTabWidget::clearSelection() {
  ui->exetensionListWidget->clearSelection();

  // force re-selection of preset
  ui->optionsListWidget->clear();
}

void PresetTabWidget::exetensionListWidgetItemSelectionChanged() {
  auto item = ui->exetensionListWidget->currentItem();

  // load related presets in the optionsListWidget
  ui->optionsListWidget->blockSignals(true);
  QList<Preset> presetsByExetension =
      DefaultPresetReader::getInstance()->getPresetsByExetension(
          item->text().toLower());

  ui->optionsListWidget->clear();

  // add presetsByExetension to optionsListWidget
  for (int i = 0, total = presetsByExetension.count(); i < total; ++i) {
    QListWidgetItem *item = new QListWidgetItem(
        QIcon(":/primo/receipt.png"), presetsByExetension.at(i).getLabel(),
        ui->optionsListWidget);
    item->setData(Qt::UserRole, presetsByExetension.at(i).getKey());
    ui->optionsListWidget->addItem(item);
  }
  ui->optionsListWidget->blockSignals(false);

  // select first item if there is only one item ;)
  if (presetsByExetension.count() == 1) {
    ui->optionsListWidget->setCurrentRow(0);
    ui->optionsListWidget->setFocus();
  }
}

void PresetTabWidget::optionsListWidgetItemSelectionChanged() {
  auto item = ui->optionsListWidget->currentItem();

  // load preset's in the editPresetWidget
  Preset presetByKey = DefaultPresetReader::getInstance()->getPresetByKey(
      item->data(Qt::UserRole).toString());

  presetByKey.print();
  emit presetSelectionChanged(presetByKey);
}

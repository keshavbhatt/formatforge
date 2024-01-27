#include "presettabwidget.h"
#include "Presets/defaultpresetreader.h"
#include "ui_presettabwidget.h"

PresetTabWidget::PresetTabWidget(QWidget *parent, QString name)
    : QWidget(parent), ui(new Ui::PresetTabWidget) {
  ui->setupUi(this);

  this->tabName = name;

  connect(ui->exetensionListWidget, &QListWidget::currentRowChanged, this,
          &PresetTabWidget::exetensionListWidgetCurrentRowChanged);

  connect(ui->optionsListWidget, &QListWidget::currentRowChanged, this,
          &PresetTabWidget::optionsListWidgeCurrentRowChanged);
}

PresetTabWidget::~PresetTabWidget() { delete ui; }

QString PresetTabWidget::getTabName() const { return tabName; }

void PresetTabWidget::addExetension(const QString &exetensionName) {

  if (addedExtensions.contains(exetensionName) == false) {
    addedExtensions.append(exetensionName);
    ui->exetensionListWidget->addItem(exetensionName);
  }
}

void PresetTabWidget::exetensionListWidgetCurrentRowChanged(int row) {
  // load related presets in the optionsListWidget
  ui->optionsListWidget->blockSignals(true);
  auto current = ui->exetensionListWidget->item(row);
  QList<Preset> presetsByExetension =
      DefaultPresetReader::getInstance()->getPresetsByExetension(
          current->text().toLower());

  ui->optionsListWidget->clear();

  for (int i = 0; i < presetsByExetension.count(); ++i) {
    QListWidgetItem *item =
        new QListWidgetItem(presetsByExetension.at(i).getLabel());
    item->setData(Qt::UserRole, presetsByExetension.at(i).getKey());
    ui->optionsListWidget->addItem(item);
  }
  ui->optionsListWidget->blockSignals(false);
}

void PresetTabWidget::optionsListWidgeCurrentRowChanged(int row) {
  auto current = ui->optionsListWidget->item(row);
  // load preset's in the editPresetWidget
  Preset presetByKey = DefaultPresetReader::getInstance()->getPresetByKey(
      current->data(Qt::UserRole).toString());

  qDebug() << "------------------";
  qDebug() << "Key:" << presetByKey.getKey();
  qDebug() << "Label:" << presetByKey.getLabel();
  qDebug() << "Params:" << presetByKey.getParams();
  qDebug() << "Extension:" << presetByKey.getExtension();
  qDebug() << "Category:" << presetByKey.getCategory();
  qDebug() << "------------------";
}

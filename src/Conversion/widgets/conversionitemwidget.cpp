#include "conversionitemwidget.h"
#include "ui_conversionitemwidget.h"

ConversionItemWidget::ConversionItemWidget(QWidget *parent,
                                           ConversionItem conversionItem)
    : QWidget(parent), ui(new Ui::ConversionItemWidget),
      m_conversionItem(conversionItem) {
  ui->setupUi(this);

  this->layout()->setContentsMargins(0, 0, 0, 0);

  // styling
  QPalette palette = ui->innerWidget->palette();
  QColor innerWidgetBackgroundColor = palette.color(QPalette::Highlight);
  innerWidgetBackgroundColor.setAlpha(30);
  ui->innerWidget->setStyleSheet(
      QString("QWidget#innerWidget{background-color: rgba(%1, %2, %3, %4); "
              "background-image:url(:/other/texture.png)}")
          .arg(innerWidgetBackgroundColor.red())
          .arg(innerWidgetBackgroundColor.green())
          .arg(innerWidgetBackgroundColor.blue())
          .arg(innerWidgetBackgroundColor.alpha()));

  // we can use pure black here as well
  QColor thumbnailLabelBackgrounColor = palette.color(QPalette::Highlight);
  thumbnailLabelBackgrounColor = thumbnailLabelBackgrounColor.darker(160);
  thumbnailLabelBackgrounColor.setAlpha(60);
  ui->fileThumbnailLabel->setStyleSheet(
      QString("background-color: rgba(%1, %2, %3, %4);")
          .arg(thumbnailLabelBackgrounColor.red())
          .arg(thumbnailLabelBackgrounColor.green())
          .arg(thumbnailLabelBackgrounColor.blue())
          .arg(thumbnailLabelBackgrounColor.alpha()));

  ui->formatInfoPushButton->setText("More info");
  ui->formatInfoPushButton->setIcon(QIcon(":/primo/info_blue.png"));
  ui->formatInfoPushButton->setFlat(true);
  ui->formatInfoPushButton->setToolTip("Show more information");

  // thumbnail size
  int width = height() * 1.78;
  ui->fileThumbnailLabel->setMinimumSize(width, height());

  setValuesFromConversionItem();
}

ConversionItemWidget::~ConversionItemWidget() { delete ui; }

ConversionItem ConversionItemWidget::getConversionItem() const {
  return m_conversionItem;
}

void ConversionItemWidget::setValuesFromConversionItem() { Q_UNIMPLEMENTED(); }

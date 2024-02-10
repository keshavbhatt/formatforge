#include "conversionitemwidget.h"
#include "ui_conversionitemwidget.h"

ConversionItemWidget::ConversionItemWidget(QWidget *parent,
                                           ConversionItem conversionItem)
    : QWidget(parent), ui(new Ui::ConversionItemWidget),
      m_conversionItem(conversionItem) {
  ui->setupUi(this);
}

ConversionItemWidget::~ConversionItemWidget() { delete ui; }

ConversionItem ConversionItemWidget::getConversionItem() const {
  return m_conversionItem;
}

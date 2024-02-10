#ifndef CONVERSIONITEMWIDGET_H
#define CONVERSIONITEMWIDGET_H

#include <QWidget>

#include <Conversion/conversionitem.h>

namespace Ui {
class ConversionItemWidget;
}

class ConversionItemWidget : public QWidget {
  Q_OBJECT

public:
  explicit ConversionItemWidget(
      QWidget *parent = nullptr,
      ConversionItem conversionItem = ConversionItem());
  ~ConversionItemWidget();

  ConversionItem getConversionItem() const;

private:
  Ui::ConversionItemWidget *ui;
  ConversionItem m_conversionItem;
};

#endif // CONVERSIONITEMWIDGET_H

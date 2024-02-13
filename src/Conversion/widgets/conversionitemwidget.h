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

private slots:
  void updateAfterConversion();
  void openOutputSettings();

private:
  Ui::ConversionItemWidget *ui;
  ConversionItem m_conversionItem;

  void setValuesFromConversionItem();
  QPixmap getIconThumbnailPixmapFor(const QString &mediaType, int width = 32,
                                    int height = 32);
  QString getFileNameFrom(const ConversionItem &conversionItem);
};

#endif // CONVERSIONITEMWIDGET_H

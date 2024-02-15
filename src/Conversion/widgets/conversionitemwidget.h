#ifndef CONVERSIONITEMWIDGET_H
#define CONVERSIONITEMWIDGET_H

#include <QProcess>
#include <QWidget>

#include <Conversion/conversionitem.h>

#include <MediaProcessor/metadata_extractors/ffmpegthumbnailextractor.h>
#include <MediaProcessor/metadata_extractors/ffprobemetadataextractor.h>

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

  void conversionProcessProgressChanged(double progress);

  void conversionProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private slots:
  void openOutputSettings();
  void setMediaItemThumbnail(const QString &fileName, const QByteArray &result);
  void updateMediaItemMetaData(const QString &filePath, const QString &result);

private:
  Ui::ConversionItemWidget *ui;
  ConversionItem m_conversionItem;

  //todo turn this to regular member not pointer
  FFMpegThumbnailExtractor *m_mediaThumbnailProcessor = nullptr;
  FFProbeMetaDataExtractor m_mediaMetadataProcessor;

  void setValuesFromConversionItem();
  QPixmap getIconThumbnailPixmapFor(const QString &mediaType, int width = 32,
                                    int height = 32);
  QString getFileNameFrom(const ConversionItem &conversionItem);


};

#endif // CONVERSIONITEMWIDGET_H

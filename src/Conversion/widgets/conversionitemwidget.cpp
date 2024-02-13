#include "conversionitemwidget.h"
#include "ui_conversionitemwidget.h"

#include <Core/utils.h>

ConversionItemWidget::ConversionItemWidget(QWidget *parent,
                                           ConversionItem conversionItem)
    : QWidget(parent), ui(new Ui::ConversionItemWidget),
      m_conversionItem(conversionItem) {
  ui->setupUi(this);

  ui->changeOutputSettingsPushButton->setText(tr("Change out Setting"));
  ui->changeOutputSettingsPushButton->setFlat(true);
  ui->changeOutputSettingsPushButton->setIcon(QIcon(":/primo/receipt.png"));
  ui->changeOutputSettingsPushButton->setToolTip(
      tr("Change output settings for this Item"));

  connect(ui->changeOutputSettingsPushButton, &QPushButton::clicked, this,
          &ConversionItemWidget::openOutputSettings);

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

void ConversionItemWidget::openOutputSettings() { Q_UNIMPLEMENTED(); }

ConversionItemWidget::~ConversionItemWidget() { delete ui; }

ConversionItem ConversionItemWidget::getConversionItem() const {
  return m_conversionItem;
}

void ConversionItemWidget::setValuesFromConversionItem() {
  ui->fileTitleLable->setText(getFileNameFrom(m_conversionItem));
  ui->fileSizeLabel->setText("~");
  ui->fileThumbnailLabel->setPixmap(getIconThumbnailPixmapFor("Waiting"));
  ui->mediaDurationLabel->setText("~");
  ui->fileExetensionLabel->setText("~");
  ui->mediaTypeLabel->setText("~");

  ui->videoDimensionLabel->setText("~");
  ui->bitrateLabel->setText("~");
  ui->mediaStreamsLabel->setText("~");
}

void ConversionItemWidget::updateAfterConversion() {
  ui->fileSizeLabel->setText("~");
  ui->fileThumbnailLabel->setPixmap(getIconThumbnailPixmapFor("Waiting"));
  ui->mediaDurationLabel->setText("~");
  ui->fileExetensionLabel->setText("~");
  ui->mediaTypeLabel->setText("~");
  ui->mediaStreamsLabel->setText("~");

  ui->videoDimensionLabel->setText("~");
  ui->bitrateLabel->setText("~");
}

QPixmap
ConversionItemWidget::getIconThumbnailPixmapFor(const QString &mediaType,
                                                int width, int height) {
  QMap<QString, QString> pixmapMap = {{"Video", ":/primo/video.png"},
                                      {"Audio", ":/primo/music.png"},
                                      {"Image", ":/primo/photo.png"},
                                      {"Waiting", ":/primo/clock.png"},
                                      {"Unknown", ":/primo/help_blue.png"}};

  QPixmap originalPixmap =
      QPixmap(pixmapMap.value(mediaType, ":/primo/help_blue.png"));

  if (!originalPixmap.isNull()) {
    return originalPixmap.scaled(width, height, Qt::KeepAspectRatio,
                                 Qt::SmoothTransformation);
  } else {
    return QPixmap(":/primo/help_blue.png")
        .scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  }
}

QString
ConversionItemWidget::getFileNameFrom(const ConversionItem &conversionItem) {
  return conversionItem.getFileBaseName() + "." +
         conversionItem.getOutputExetension();
}

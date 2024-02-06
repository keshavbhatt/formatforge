#include "mediaitemwidget.h"
#include "ui_mediaitemwidget.h"
#include <Core/utils.h>
#include <MediaProcessor/metadata/audiometadata.h>
#include <MediaProcessor/metadata/videometadata.h>
#include <QDebug>
#include <QFileInfo>

MediaItemWidget::MediaItemWidget(QWidget *parent, QString filePath,
                                 MediaMetaData *mediaMetaData)
    : QWidget(parent), ui(new Ui::MediaItemWidget), m_filePath(filePath),
      m_fileInfo(QFileInfo(filePath)), m_mediaMetaData(mediaMetaData) {
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

  // start FFMpegThumbnailExtractor connections
  mediaThumbnailProcessor = new FFMpegThumbnailExtractor(this);
  connect(mediaThumbnailProcessor,
          &FFMpegThumbnailExtractor::mediaProcessingFinished, this, [=]() {
            disconnect(mediaThumbnailProcessor, nullptr, nullptr, nullptr);
            mediaThumbnailProcessor->deleteLater();
            mediaThumbnailProcessor = nullptr;
          });

  connect(mediaThumbnailProcessor,
          &FFMpegThumbnailExtractor::mediaProcessingProgress, this,
          [=](int currentFileIndex, int totalFiles) {
            qDebug() << "FFMpegThumbnailExtractor processing file " << currentFileIndex << " of "
                     << totalFiles;
          });

  connect(mediaThumbnailProcessor, &FFMpegThumbnailExtractor::mediaProcessed,
          this, &MediaItemWidget::setMediaItemThumbnail);
  // end FFMpegThumbnailExtractor connections

  int width = height() * 1.78;
  ui->fileThumbnailLabel->setMinimumSize(width, height());

  setValuesFromMetadata();
}

void MediaItemWidget::setMediaItemThumbnail(const QString &fileName,
                                            const QByteArray &result) {
  Q_UNUSED(fileName);
  QPixmap thumbnailPixmapFromData;
  if (thumbnailPixmapFromData.loadFromData(result)) {

    ui->fileThumbnailLabel->setPixmap(thumbnailPixmapFromData.scaled(
        QSize(ui->fileThumbnailLabel->size()), Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
  } else {
    qDebug() << "Error loading thumbnail from data.";
  }
}

void MediaItemWidget::setValuesFromMetadata() {

  ui->fileTitleLable->setText(m_fileInfo.fileName());
  ui->fileSizeLabel->setText(
      this->locale().formattedDataSize(m_fileInfo.size()));

  ui->fileThumbnailLabel->setPixmap(
      getIconThumbnailPixmapFor(m_mediaMetaData->mediaType()));
  ui->mediaDurationLabel->setText(Utils::durationStringToHumanReadable(
      m_mediaMetaData->formatObject().value("duration").toString()));
  ui->fileExetensionLabel->setText(
      m_mediaMetaData->formatObject().value("format_long_name").toString());
  ui->mediaTypeLabel->setText(mediaMetaData()->mediaType().toUpper());

  auto streamsCount = m_mediaMetaData->getStreamsCount();
  if (streamsCount == 1) {
    ui->mediaStreamsLabel->setText(m_mediaMetaData->getStreamInfo());
  } else {
    ui->mediaStreamsLabel->setText(QString::number(streamsCount) + " tracks (" +
                                   m_mediaMetaData->getStreamInfo() + ")");
  }

  ui->videoDimensionLabel->setText("");

  if (VideoMetaData *videoMetaData =
          dynamic_cast<VideoMetaData *>(m_mediaMetaData)) {
    if (mediaThumbnailProcessor) {
      mediaThumbnailProcessor->processMediaFiles(QStringList{m_filePath});
    }

    if (videoMetaData->getVideoStreams().isEmpty() == false) {
      auto firstVideoStream = videoMetaData->getVideoStreams().constFirst();
      ui->videoDimensionLabel->setText(
          QString::number(firstVideoStream.value("width").toDouble()) + "x" +
          QString::number(firstVideoStream.value("height").toDouble()));
    }
  } else if (AudioMetaData *audioMetaData =
                 dynamic_cast<AudioMetaData *>(m_mediaMetaData)) {

  } else {
    ui->mediaDurationLabel->setText("Unknown");
  }
}

QPixmap MediaItemWidget::getIconThumbnailPixmapFor(const QString &mediaType,
                                                   int width, int height) {
  QMap<QString, QString> pixmapMap = {{"Video", ":/primo/video.png"},
                                      {"Audio", ":/primo/music.png"},
                                      {"Image", ":/primo/photo.png"}};

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

MediaItemWidget::~MediaItemWidget() {
  delete ui;
  if (m_mediaMetaData) {
    delete m_mediaMetaData;
  }
}

QString MediaItemWidget::filePath() const { return m_filePath; }

MediaMetaData *MediaItemWidget::mediaMetaData() const {
  return m_mediaMetaData;
}

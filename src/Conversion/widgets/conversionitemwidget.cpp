#include "conversionitemwidget.h"
#include "ui_conversionitemwidget.h"

#include <Core/utils.h>

#include <Settings/settingsmanager.h>

#include <MediaProcessor/metadata/audiometadata.h>
#include <MediaProcessor/metadata/mediametadata.h>
#include <MediaProcessor/metadata/videometadata.h>

#include <MediaProcessor/metadata_parsers/ffprobeparser.h>

ConversionItemWidget::ConversionItemWidget(QWidget *parent,
                                           ConversionItem conversionItem)
    : QWidget(parent), ui(new Ui::ConversionItemWidget),
      m_conversionItem(conversionItem) {
  ui->setupUi(this);
  this->layout()->setContentsMargins(0, 0, 0, 0);

  ui->formatInfoPushButton->hide();
  ui->progressLabel->show();
  ui->progressLabel->setText("~");
  ui->metaDataWidget->hide();

  ui->changeOutputSettingsPushButton->setText(tr("Change out Setting"));
  ui->changeOutputSettingsPushButton->setFlat(true);
  ui->changeOutputSettingsPushButton->setIcon(QIcon(":/primo/receipt.png"));
  ui->changeOutputSettingsPushButton->setToolTip(
      tr("Change output settings for this Item"));

  connect(ui->changeOutputSettingsPushButton, &QPushButton::clicked, this,
          &ConversionItemWidget::openOutputSettings);

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
  ui->fileThumbnailProgressLabel->setStyleSheet(
      QString("background-color: rgba(%1, %2, %3, %4);")
          .arg(thumbnailLabelBackgrounColor.red())
          .arg(thumbnailLabelBackgrounColor.green())
          .arg(thumbnailLabelBackgrounColor.blue())
          .arg(thumbnailLabelBackgrounColor.alpha()));

  ui->fileThumbnailProgressLabel->setProgress(0);
  QColor c(palette.color(QPalette::Highlight));
  c.setAlpha(120);
  ui->fileThumbnailProgressLabel->setProgressColor(c.lighter(140));
  ui->fileThumbnailProgressLabel->setAlignment(Qt::AlignCenter);
  connect(ui->fileThumbnailProgressLabel, &ProgressLabel::progressChanged, this,
          [=](int progress) {
            ui->fileThumbnailProgressLabel->setText(QString::number(progress) +
                                                    "%");
          });

  ui->formatInfoPushButton->setText("More info");
  ui->formatInfoPushButton->setIcon(QIcon(":/primo/info_blue.png"));
  ui->formatInfoPushButton->setFlat(true);
  ui->formatInfoPushButton->setToolTip("Show more information");

  // start FFMpegThumbnailExtractor connections
  m_mediaThumbnailProcessor = new FFMpegThumbnailExtractor(this);
  connect(m_mediaThumbnailProcessor,
          &FFMpegThumbnailExtractor::mediaProcessingFinished, this, [=]() {
            disconnect(m_mediaThumbnailProcessor, nullptr, nullptr, nullptr);
            m_mediaThumbnailProcessor->deleteLater();
            m_mediaThumbnailProcessor = nullptr;
          });
  connect(m_mediaThumbnailProcessor, &FFMpegThumbnailExtractor::mediaProcessed,
          this, &ConversionItemWidget::setMediaItemThumbnail);
  // end FFMpegThumbnailExtractor connections

  // start FFProbeMetaDataExtractor connections
  connect(&m_mediaMetadataProcessor,
          &FFProbeMetaDataExtractor::mediaProcessingFinished, this,
          [=]() { this->setEnabled(true); });

  connect(&m_mediaMetadataProcessor, &FFProbeMetaDataExtractor::mediaProcessed,
          this, &ConversionItemWidget::updateMediaItemMetaData);
  // end FFProbeMetaDataExtractor connections

  // thumbnail size
  auto thumbnailAspectRatio =
      SettingsManager::settings()
          .value(SettingsConstantsGetNameFor(THUMBNAIL_ASPECT_RATIO),
                 SettingsConstantsGetDefaultFor(THUMBNAIL_ASPECT_RATIO))
          .toDouble();
  int width = height() * thumbnailAspectRatio;
  ui->fileThumbnailProgressLabel->setMinimumSize(width, height());
  // end thumbnail size

  setValuesFromConversionItem();
}

void ConversionItemWidget::openOutputSettings() { Q_UNIMPLEMENTED(); }

ConversionItemWidget::~ConversionItemWidget() { delete ui; }

ConversionItem ConversionItemWidget::getConversionItem() const {
  return m_conversionItem;
}

void ConversionItemWidget::conversionProcessProgressChanged(
    const QJsonObject &progressData) {
  if (!progressData.isEmpty()) {
    double progress = progressData.value("progress_calculated").toDouble();
    ui->fileThumbnailProgressLabel->setProgress(qRound(progress));

    QString progressLabelText;
    QStringList excludeKeys{"_", "pid", "progress"};

    for (auto it = progressData.constBegin(); it != progressData.constEnd();
         ++it) {
      bool excludeKey = false;
      for (const QString &excluded : excludeKeys) {
        if (it.key().contains(excluded)) {
          excludeKey = true;
          break;
        }
      }

      if (!excludeKey) {
        progressLabelText.append(it.key())
            .append(": ")
            .append(it.value().toString())
            .append("   ");
      }
    }

    ui->progressLabel->setText(progressLabelText.trimmed());
  }
}

void ConversionItemWidget::setValuesFromConversionItem() {

  ui->fileTitleLable->setText(
      Utils::getFileNameFor(m_conversionItem.getFileBaseName(),
                            m_conversionItem.getOutputExetension()));
  ui->filePathLable->setText(m_conversionItem.getOutputDirectory());
  ui->fileSizeLabel->setText("~");
  ui->fileThumbnailProgressLabel->setPixmap(
      this->getIconThumbnailPixmapFor("Waiting"));
  ui->mediaDurationLabel->setText("~");
  ui->fileExetensionLabel->setText("~");
  ui->mediaTypeLabel->setText("~");

  ui->videoDimensionLabel->setText("");
  ui->bitrateLabel->setText("");
  ui->mediaStreamsLabel->setText("");
}

void ConversionItemWidget::conversionProcessFinished(
    int exitCode, QProcess::ExitStatus exitStatus) {
  Q_UNUSED(exitStatus);
  auto outputFilePath =
      Utils::getFileNameFor(m_conversionItem.getOutputDirectory() +
                                m_conversionItem.getFileBaseName(),
                            m_conversionItem.getOutputExetension());
  if (exitCode == 0) {
    ui->fileThumbnailProgressLabel->setProgress(100);
    m_mediaMetadataProcessor.processMediaFiles(QStringList{outputFilePath});

    ui->formatInfoPushButton->show();
    ui->changeOutputSettingsPushButton->hide();
  } else {
    ui->fileThumbnailProgressLabel->setPixmap(
        getIconThumbnailPixmapFor("Unknown"));
  }

  ui->progressLabel->setText("~");
  ui->progressLabel->hide();
  ui->metaDataWidget->show();
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

void ConversionItemWidget::setMediaItemThumbnail(const QString &fileName,
                                                 const QByteArray &result) {

  QPixmap thumbnailPixmapFromData;
  if (thumbnailPixmapFromData.loadFromData(result)) {

    ui->fileThumbnailProgressLabel->setPixmap(thumbnailPixmapFromData.scaled(
        QSize(ui->fileThumbnailProgressLabel->size()), Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
  } else {
    qDebug() << "Error loading thumbnail from data for file" << fileName;
  }
}

void ConversionItemWidget::updateMediaItemMetaData(const QString &filePath,
                                                   const QString &result) {

  MediaMetaData *mediaMetaData =
      FFProbeParser::getMediaMetaDataFor(filePath, result);
  if (mediaMetaData) {

    QFileInfo fileInfo(filePath);

    ui->fileTitleLable->setText(fileInfo.fileName());
    ui->filePathLable->setText(fileInfo.dir().absolutePath());
    ui->fileSizeLabel->setText(
        this->locale().formattedDataSize(fileInfo.size()));

    ui->fileThumbnailProgressLabel->setPixmap(
        getIconThumbnailPixmapFor(mediaMetaData->mediaType()));
    ui->mediaDurationLabel->setText(Utils::durationStringToHumanReadable(
        mediaMetaData->formatObject().value("duration").toString()));
    ui->fileExetensionLabel->setText(
        mediaMetaData->formatObject().value("format_long_name").toString());
    ui->mediaTypeLabel->setText(mediaMetaData->mediaType().toUpper());

    auto streamsCount = mediaMetaData->getStreamsCount();
    if (streamsCount == 1) {
      ui->mediaStreamsLabel->setText(mediaMetaData->getStreamInfo());
    } else {
      ui->mediaStreamsLabel->setText(QString::number(streamsCount) +
                                     " tracks (" +
                                     mediaMetaData->getStreamInfo() + ")");
    }

    ui->videoDimensionLabel->setText("");

    if (VideoMetaData *videoMetaData =
            dynamic_cast<VideoMetaData *>(mediaMetaData)) {
      if (m_mediaThumbnailProcessor) {
        m_mediaThumbnailProcessor->processMediaFiles(QStringList{filePath});
      }

      const auto &videoStreams = videoMetaData->getVideoStreams();
      if (videoStreams.isEmpty() == false) {
        const auto &firstVideoStream = videoStreams.constFirst();
        // video dimension
        QString dimensionText =
            QString("%1x%2")
                .arg(firstVideoStream.value("width").toDouble())
                .arg(firstVideoStream.value("height").toDouble());

        int additionalVideoStreams =
            videoMetaData->getVideoStreams().count() - 1;
        if (additionalVideoStreams > 0) {
          dimensionText += QString(" (%1 more)").arg(additionalVideoStreams);
        }
        ui->videoDimensionLabel->setText(dimensionText);

        // video bitrate(uses bit_rate from format object if first stream
        // misses)
        auto bitrateFromFirstVideoStream =
            firstVideoStream.value("bit_rate").toString().toDouble();
        auto bitrateFromVideoFormat = videoMetaData->formatObject()
                                          .value("bit_rate")
                                          .toString()
                                          .toDouble();
        QString bitrateText =
            QString("%1/Sec").arg(this->locale().formattedDataSize(
                bitrateFromFirstVideoStream == 0.0
                    ? bitrateFromVideoFormat
                    : bitrateFromFirstVideoStream));

        int additionalAudioStreams =
            videoMetaData->getVideoStreams().count() - 1;
        if (additionalAudioStreams > 0) {
          bitrateText += QString(" (%1 more)").arg(additionalAudioStreams);
        }
        ui->bitrateLabel->setText(bitrateText);
      }
    } else if (AudioMetaData *audioMetaData =
                   dynamic_cast<AudioMetaData *>(mediaMetaData)) {
      // hide n/a elements
      ui->videoDimensionLabel->hide();

      const auto &audioStreams = audioMetaData->getAudioStreams();
      if (audioStreams.isEmpty() == false) {
        const auto &firstAudioStream = audioStreams.constFirst();

        // audio bitrate(uses bit_rate from format object if first stream
        // misses)
        auto bitrateFromFirstAudioStream =
            firstAudioStream.value("bit_rate").toString().toDouble();
        auto bitrateFromAudioFormat = audioMetaData->formatObject()
                                          .value("bit_rate")
                                          .toString()
                                          .toDouble();
        QString bitrateText =
            QString("%1/Sec").arg(this->locale().formattedDataSize(
                bitrateFromFirstAudioStream == 0.0
                    ? bitrateFromAudioFormat
                    : bitrateFromFirstAudioStream));

        int additionalAudioStreams =
            audioMetaData->getAudioStreams().count() - 1;
        if (additionalAudioStreams > 0) {
          bitrateText += QString(" (%1 more)").arg(additionalAudioStreams);
        }
        ui->bitrateLabel->setText(bitrateText);
      }
    } else {
      ui->mediaDurationLabel->setText("Unknown");
      // TODO: other ui items
    }
  }
}

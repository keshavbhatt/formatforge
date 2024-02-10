#ifndef MEDIAITEMWIDGET_H
#define MEDIAITEMWIDGET_H

#include <QFileInfo>
#include <QWidget>

#include <MediaProcessor/metadata/mediametadata.h>

#include <MediaProcessor/metadata_extractors/ffmpegthumbnailextractor.h>

namespace Ui {
class MediaItemWidget;
}

class MediaItemWidget : public QWidget {
  Q_OBJECT

public:
  explicit MediaItemWidget(QWidget *parent = nullptr, QString filePath = "",
                           MediaMetaData *mediaMetaData = nullptr);
  ~MediaItemWidget();

  QString getFilePath() const;
  MediaMetaData *mediaMetaData() const;

  QString getId() const;

private:
  Ui::MediaItemWidget *ui;

  QString m_id;
  QString m_filePath;
  QFileInfo m_fileInfo;
  FFMpegThumbnailExtractor *mediaThumbnailProcessor = nullptr;
  MediaMetaData *m_mediaMetaData = nullptr;

  void setValuesFromMetadata();
  QPixmap getIconThumbnailPixmapFor(const QString &mediaType, int width = 32,
                                    int height = 32);
  void setMediaItemThumbnail(const QString &fileName, const QByteArray &result);
};

#endif // MEDIAITEMWIDGET_H

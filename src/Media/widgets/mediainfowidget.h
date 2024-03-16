#ifndef MEDIAINFOWIDGET_H
#define MEDIAINFOWIDGET_H

#include <QMessageBox>
#include <QTableWidget>
#include <QWidget>

#include <Media/mediainfo.h>

namespace Ui {
class MediaInfoWidget;
}

class MediaInfoWidget : public QWidget {
  Q_OBJECT

public:
  explicit MediaInfoWidget(QWidget *parent = nullptr,
                           MediaInfo mediaInfo = MediaInfo());
  ~MediaInfoWidget();

private:
  Ui::MediaInfoWidget *ui;
  void populateTableWidget(QTableWidget *tableWidget,
                           const MediaInfo &mediaInfo);

  MediaInfo m_mediaInfo;
  void applyFilter(const QString &filterText);
};

#endif // MEDIAINFOWIDGET_H

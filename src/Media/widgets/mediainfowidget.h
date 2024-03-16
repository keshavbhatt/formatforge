#ifndef MEDIAINFOWIDGET_H
#define MEDIAINFOWIDGET_H

#include <QClipboard>
#include <QKeyEvent>
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

protected:
  void keyPressEvent(QKeyEvent *event) override;

private slots:
  void updateFilterRadioButton(const QString &filterText);
  void updateFilterText();
  void copyRowActionTriggered();

private:
  Ui::MediaInfoWidget *ui;
  void populateTableWidget(QTableWidget *tableWidget,
                           const MediaInfo &mediaInfo);

  MediaInfo m_mediaInfo;
  void applyFilter(const QString &filterText);
  void setupContextMenuForMediaInfoTable();
};

#endif // MEDIAINFOWIDGET_H

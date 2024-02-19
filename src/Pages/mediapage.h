#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include "page.h"

#include <QDebug>
#include <QScrollBar>
#include <QWidget>

#include "Conversion/conversionitem.h"
#include "Core/filescanner.h"
#include "Media/widgets/mediaitemwidget.h"
#include "MediaProcessor/metadata/audiometadata.h"
#include "MediaProcessor/metadata/videometadata.h"
#include "MediaProcessor/metadata_extractors/ffprobemetadataextractor.h"
#include "MediaProcessor/metadata_parsers/ffprobeparser.h"
#include "Widgets/spinner.h"
#include "outputsettingpage.h"

namespace Ui {
class MediaPage;
}

class MediaPage : public Page {
  Q_OBJECT

public:
  explicit MediaPage(QWidget *parent = nullptr);
  ~MediaPage();

  void loadMediaFiles(const QStringList &filePathList);
  QList<ConversionItem> getSelectedMediaItems() const;
  bool isEnabled();
  void setNextPage(Page *nextPage);
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setPreviousPage(Page *prevPage);

private:
  Ui::MediaPage *ui;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  FFProbeMetaDataExtractor m_mediaMetadataProcessor;
  Spinner *spinner = nullptr;

  void updatePage();
  void addMediaItemToView(const QString &filePath, const QString &result);
  void processMedia(const QStringList &fileNameList);
  void removeSelectedMediaListWidgetItems();
  void updatePageStatusMessage();

public slots:
  void activate();
  QStringList getLoadedMediaFilesPath();

signals:
  void playMediaRequested(const QString &filePath);
  void addMoreFiles();

private slots:
  void mediaItemDoubleClicked(QListWidgetItem *item);
  void updateBottomToolbarButtons();
};

#endif // MEDIAPAGE_H

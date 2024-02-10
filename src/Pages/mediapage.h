#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include "page.h"

#include <QWidget>

#include "Conversion/conversionitem.h"
#include "MediaProcessor/metadata_extractors/ffprobemetadataextractor.h"
#include "Widgets/spinner.h"

namespace Ui {
class MediaPage;
}

class MediaPage : public Page {
  Q_OBJECT

public:
  explicit MediaPage(QWidget *parent = nullptr);
  ~MediaPage();

  void loadMediaFiles(const QStringList &filePathList);

private:
  Ui::MediaPage *ui;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  FFProbeMetaDataExtractor mediaMetadataProcessor;

  Spinner *spinner = nullptr;

  void updatePage();
  void addMediaItem(const QString &filePath, const QString &result);
  void processMedia(const QStringList &fileNameList);
  void removeSelectedMediaListWidgetItems();
  void updatePageStatusMessage();

public slots:
  void activate();
  QStringList getLoadedMediaFilesPath();

signals:
  void addMoreFiles();

public:
  QList<ConversionItem> getSelectedMediaItems() const;
  bool isEnabled();
  void setNextPage(Page *nextPage);
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setPreviousPage(Page *prevPage);

private slots:
  void updateBottomToolbarButtons();
};

#endif // MEDIAPAGE_H

#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include "MediaProcessor/mediaprocessor.h"
#include "page.h"

#include <QWidget>

#include <Widgets/spinner.h>

namespace Ui {
class MediaPage;
}

class MediaPage : public Page {
  Q_OBJECT

public:
  explicit MediaPage(QWidget *parent = nullptr);
  ~MediaPage();

  void loadMediaFiles(const QStringList &fileNameList);

private:
  Ui::MediaPage *ui;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  MediaProcessor mediaProcessor;
  Spinner *spinner = nullptr;

  void updatePage();
  void addMediaItem(const QString &fileName, const QString &result);
  void processMedia(const QStringList &fileNameList);

public slots:
  void activate();

public:
  bool isEnabled();
  void setNextPage(Page *nextPage);
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setPreviousPage(Page *prevPage);
};

#endif // MEDIAPAGE_H

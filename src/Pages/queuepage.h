#ifndef QUEUEPAGE_H
#define QUEUEPAGE_H

#include "outputsettingpage.h"
#include "page.h"

#include <QWidget>

#include <Conversion/conversionmanager.h>

namespace Ui {
class QueuePage;
}

class QueuePage : public Page {
  Q_OBJECT

public:
  explicit QueuePage(QWidget *parent = nullptr);
  ~QueuePage();

  bool isEnabled();
  void setNextPage(Page *nextPage);
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setPreviousPage(Page *prevPage);
  void convert();

public slots:
  void activate();

private:
  Ui::QueuePage *ui;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  OutputSettingPage *getOutputSettingPage();
  void updatePageStatusMessage();
  void updatePage();
  void prepare();

  ConversionManager *m_conversionManager = nullptr;

  void addConversionItem(const ConversionItem &conversionItem);
  void loadConversionItemsToView(MediaPage *mediaPage,
                                 const Preset &selectedPreset);

  QList<ConversionItem> getAllConversionItems() const;
};

#endif // QUEUEPAGE_H

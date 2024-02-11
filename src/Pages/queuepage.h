#ifndef QUEUEPAGE_H
#define QUEUEPAGE_H

#include "Conversion/conversionmanager.h"
#include "Conversion/widgets/conversionitemwidget.h"
#include "outputsettingpage.h"
#include "page.h"
#include <QScrollBar>
#include <QWidget>

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

  void addConversionItemToView(const ConversionItem &conversionItem);
  void addConversionItems(MediaPage *mediaPage, const Preset &selectedPreset,
                          const QString &outputDirectoryPath,
                          bool preserveHierarchy);

  QList<ConversionItem> getAllConversionItems() const;
};

#endif // QUEUEPAGE_H

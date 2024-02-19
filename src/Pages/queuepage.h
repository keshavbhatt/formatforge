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

signals:
  void playMediaRequested(const QString &filePath);

private slots:
  void mediaItemDoubleClicked(QListWidgetItem *item);

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
  QString getOutputDirectoryPathFrom(const ConversionItem &conversionItem);
  void updateItemProgress(const QJsonObject &progressData);
  void updateItemStatus(QString pid, int exitCode,
                        QProcess::ExitStatus exitStatus);
  ConversionItemWidget *findConversionItemWidget(const QString &itemId) const;
};

#endif // QUEUEPAGE_H

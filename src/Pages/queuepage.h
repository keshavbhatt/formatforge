#ifndef QUEUEPAGE_H
#define QUEUEPAGE_H

#include "page.h"

#include <QWidget>

namespace Ui {
class QueuePage;
}

class QueuePage : public Page {
  Q_OBJECT

public:
  explicit QueuePage(QWidget *parent = nullptr);
  ~QueuePage();

private:
  Ui::QueuePage *ui;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  // Page interface
public slots:
  void activate();

  // Page interface
public:
  bool isEnabled();
  void setNextPage(Page *nextPage);
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setPreviousPage(Page *prevPage);
};

#endif // QUEUEPAGE_H

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "page.h"

#include <QWidget>

namespace Ui {
class HomePage;
}

class HomePage : public Page {
  Q_OBJECT

public:
  explicit HomePage(QWidget *parent = nullptr);
  ~HomePage();

signals:
  void mediaFileLoaded(const QStringList &fileNames);

private slots:
  void addMedia();

private:
  Ui::HomePage *ui;

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

#endif // HOMEPAGE_H

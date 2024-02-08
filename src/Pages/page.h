#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class Page : public QWidget {
  Q_OBJECT
public:
  explicit Page(QWidget *parent = nullptr) : QWidget{parent} {}

  virtual bool isEnabled() = 0;
  virtual void setNextPage(Page *nextPage = nullptr) = 0;
  virtual void setPreviousPage(Page *prevPage = nullptr) = 0;
  virtual Page *getNextPage() const = 0;
  virtual Page *getPreviousPage() const = 0;

public slots:
  virtual void activate() = 0;

signals:
  void goToNextPage();
  void goToPreviousPage();
  void updateStatusMessage(const QString &message);
  void updateMainToolbarAction();
};

#endif // PAGE_H

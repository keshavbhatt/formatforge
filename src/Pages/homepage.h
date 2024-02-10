#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "page.h"

#include <QFileDialog>
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
  void filesSelected(const QStringList &fileNames);

public slots:
  void addMediaFromFolder();
  void addMediaFromExistingFiles();

private:
  void
  openFileSelector(QFileDialog::FileMode fileMode = QFileDialog::ExistingFiles);
  Ui::HomePage *ui;

  Page *m_nextPage = nullptr;
  Page *m_prevPage = nullptr;

  void recursiveAddFiles(const QDir &dir, const QStringList &nameFilters,
                         QStringList &filePaths);

  QString getFileSelectorLastUsedPath();

public slots:
  void activate();

public:
  bool isEnabled();
  void setNextPage(Page *nextPage);
  Page *getNextPage() const;
  Page *getPreviousPage() const;
  void setPreviousPage(Page *prevPage);
};

#endif // HOMEPAGE_H

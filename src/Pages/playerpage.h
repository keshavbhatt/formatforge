#ifndef PLAYERPAGE_H
#define PLAYERPAGE_H

#include "page.h"

#include <QWidget>

#include <Player/mpvobject.h>

namespace Ui {
class PlayerPage;
}

class PlayerPage : public Page {
  Q_OBJECT

public:
  explicit PlayerPage(QWidget *parent = nullptr);
  ~PlayerPage();

  bool isEnabled() override;
  void setNextPage(Page *nextPage) override;
  void setPreviousPage(Page *prevPage) override;
  Page *getNextPage() const override;
  Page *getPreviousPage() const override;

  void play(const QString &filePath);

public slots:
  void activate() override;

private:
  Ui::PlayerPage *ui;
  MpvObject *m_mpvObject = nullptr;

protected:
  void keyPressEvent(QKeyEvent *event) override;
};

#endif // PLAYERPAGE_H

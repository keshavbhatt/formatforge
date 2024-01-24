#ifndef OUTPUTSETTINGPAGE_H
#define OUTPUTSETTINGPAGE_H

#include <QWidget>

namespace Ui {
class OutputSettingPage;
}

class OutputSettingPage : public QWidget {
  Q_OBJECT

public:
  explicit OutputSettingPage(QWidget *parent = nullptr);
  ~OutputSettingPage();

signals:
  void nextPage();

private:
  Ui::OutputSettingPage *ui;
};

#endif // OUTPUTSETTINGPAGE_H

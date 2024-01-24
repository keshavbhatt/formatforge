#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include <QWidget>

namespace Ui {
class MediaPage;
}

class MediaPage : public QWidget {
  Q_OBJECT

signals:
  void nextPage();

public:
  explicit MediaPage(QWidget *parent = nullptr);
  ~MediaPage();

  void loadMediaFiles(const QStringList &fileNameList);

private slots:
  void goToOutputSettingsPage();

private:
  Ui::MediaPage *ui;
};

#endif // MEDIAPAGE_H

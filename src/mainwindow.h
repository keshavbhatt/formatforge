#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Pages/homepage.h"
#include "slidingstackedwidget.h"
#include "spinner.h"
#include <Pages/mediapage.h>
#include <Pages/outputsettingpage.h>
#include <Pages/queuepage.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void startSpinner();
  void stopSpinner();

  void switchStackWidget(QWidget *widget, bool addToStackVector = false);

private:
  Ui::MainWindow *ui;

  QVector<QWidget *> stackVector;

  Spinner *spinner;
  SlidingStackedWidget *stackedWidget;

  // pages
  HomePage *homePage;
  MediaPage *mediaPage;
  OutputSettingPage *outputSettingPage;
  QueuePage *queuePage;

  // actions

  QAction *homeAction, *mediaAction, *outputSettingAction, *convertAction,
      *queueAction;

  void initToolbar();
  void createActions();
  void initPages();
  void initSpinner();
};
#endif // MAINWINDOW_H

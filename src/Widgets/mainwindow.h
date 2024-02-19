#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Pages/homepage.h"
#include "Widgets/spinner.h"
#include "slidingstackedwidget.h"
#include <Pages/mediapage.h>
#include <Pages/outputsettingpage.h>
#include <Pages/queuepage.h>

#include <Pages/playerpage.h>

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

private slots:
  void updateMainToolbarActions(int activeActionIndex = 0);

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
  PlayerPage *playerPage;

  // actions
  QAction *homeAction, *mediaAction, *outputSettingAction, *convertAction,
      *queueAction, *playerAction;

  QList<QPair<QAction *, Page *>> mainToolbarActionsWidgetPair;

  void initToolbar();
  void createActions();
  void initPages();
  void initSpinner();
  void preparePages();
  void playMediaRequested(const QString &filePath);
};
#endif // MAINWINDOW_H

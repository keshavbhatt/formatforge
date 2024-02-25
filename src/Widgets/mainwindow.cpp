#include "mainwindow.h"
#include "Presets/widgets/presetselector.h"
#include "ui_mainwindow.h"

#include <Conversion/conversionmanager.h>

#include <QMessageBox>
#include <QQuickView>
#include <QQuickWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowIcon(QIcon(":/app/icon-64.png"));

  stackedWidget = new SlidingStackedWidget(this);
  ui->centralwidget->layout()->addWidget(stackedWidget);

  initPages();

  initToolbar();

  // init stackWidget
  stackedWidget->setAnimation(QEasingCurve::Type::OutQuart);
  stackedWidget->setSpeed(200);
  connect(stackedWidget, &QStackedWidget::currentChanged, this,
          [=](int index) { updateMainToolbarActions(index); });
  this->switchStackWidget(homePage);
}

void MainWindow::initSpinner() {
  spinner = new Spinner;
  QWidget *hSpacer = new QWidget(ui->toolBar);
  hSpacer->setStyleSheet("background-color:transparent");
  hSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  ui->toolBar->addWidget(hSpacer);
  spinner->setSpinnerSize(QSize(ui->toolBar->sizeHint().height(),
                                ui->toolBar->sizeHint().height()));
  spinner->setFixedSize(spinner->minimumSizeHint());
}

void MainWindow::preparePages() {
  // register main toolbar Action to coresponding widget
  mainToolbarActionsWidgetPair
      << qMakePair(homeAction, homePage) << qMakePair(mediaAction, mediaPage)
      << qMakePair(outputSettingAction, outputSettingPage)
      << qMakePair(queueAction, queuePage)
      << qMakePair(playerAction, playerPage);
  // netPage
  homePage->setNextPage(mediaPage);
  mediaPage->setNextPage(outputSettingPage);
  outputSettingPage->setNextPage(queuePage);
  queuePage->setNextPage(nullptr);

  // previousPage
  homePage->setPreviousPage(nullptr);
  mediaPage->setPreviousPage(homePage);
  outputSettingPage->setPreviousPage(mediaPage);
  queuePage->setPreviousPage(outputSettingPage);

  // connect main toolbar action and add action to toolbar
  for (int i = 0, total = mainToolbarActionsWidgetPair.size(); i < total; ++i) {
    QPair<QAction *, Page *> p = mainToolbarActionsWidgetPair.at(i);
    QAction *a = p.first;
    a->setCheckable(true);

    connect(a, &QAction::triggered, this,
            [=]() { this->switchStackWidget(p.second); });

    ui->toolBar->addAction(a);

    connect(p.second, &Page::updateMainToolbarAction, this,
            [=]() { updateMainToolbarActions(i); });
  }

  this->updateMainToolbarActions();
}

void MainWindow::createActions() {

  // create action
  homeAction = new QAction(QIcon(":/app/icon-64.png"), tr("&Home"), this);
  mediaAction = new QAction(QIcon("://primo/video.png"), tr("&Media"), this);
  outputSettingAction =
      new QAction(QIcon("://primo/tools.png"), tr("&Output Setting"), this);
  convertAction =
      new QAction(QIcon("://primo/button_play.png"), tr("&Convert"), this);
  queueAction =
      new QAction(QIcon("://primo/database_active.png"), tr("&Queue"), this);
  playerAction =
      new QAction(QIcon("://primo/button_black_play.png"), tr("&Player"), this);
  playerAction->setProperty("autoAdded", false);

  preparePages();

  // spinner widget in toolbar
  initSpinner();

  ui->toolBar->addWidget(spinner);
  ui->toolBar->addAction(convertAction);
  ui->toolBar->addAction(playerAction);

  connect(convertAction, &QAction::triggered, this, [=]() {
    if (queuePage) {
      queuePage->convert();
    }
  });

  connect(playerAction, &QAction::triggered, this, [=]() {
    if (playerPage) {
      this->switchStackWidget(playerPage);
    }
  });
}

void MainWindow::updateMainToolbarActions(int activeActionIndex) {
  for (QPair<QAction *, Page *> p : qAsConst(mainToolbarActionsWidgetPair)) {
    p.first->setChecked(false);
    p.first->setEnabled(p.second->isEnabled());
  }
  if (activeActionIndex + 1 <= mainToolbarActionsWidgetPair.count())
    mainToolbarActionsWidgetPair.at(activeActionIndex).first->setChecked(true);
}

void MainWindow::initPages() {
  // init pages
  homePage = new HomePage;
  mediaPage = new MediaPage;
  outputSettingPage = new OutputSettingPage;
  queuePage = new QueuePage;
  playerPage = new PlayerPage;

  // add pages to stackedWidget
  stackedWidget->addWidget(homePage);
  stackedWidget->addWidget(mediaPage);
  stackedWidget->addWidget(outputSettingPage);
  stackedWidget->addWidget(queuePage);
  stackedWidget->addWidget(playerPage);

  // page connections
  for (int i = 0, total = stackedWidget->count(); i < total; ++i) {

    auto page = qobject_cast<Page *>(stackedWidget->widget(i));

    if (page) {
      connect(page, &Page::goToNextPage, this, [=]() {
        if (page->getNextPage())
          this->switchStackWidget(page->getNextPage());
      });

      connect(page, &Page::goToPreviousPage, this, [=]() {
        if (page->getPreviousPage())
          this->switchStackWidget(page->getPreviousPage());
      });

      connect(
          page, &Page::updateStatusMessage, this,
          [=](const QString &message) { ui->statusbar->showMessage(message); });
    }
  }

  // other connections
  connect(homePage, &HomePage::filesSelected, mediaPage,
          &MediaPage::loadMediaFiles);

  connect(outputSettingPage, &OutputSettingPage::presetSelectionChanged, this,
          [=](const Preset &preset) {
            // qDebug() << "Preset selection changed";
            queueAction->setEnabled(preset.isValid());
          });

  connect(mediaPage, &MediaPage::addMoreFiles, homePage,
          &HomePage::addMediaFromExistingFiles);

  connect(mediaPage, &MediaPage::playMediaRequested, this,
          &MainWindow::playMediaRequested);

  connect(queuePage, &QueuePage::playMediaRequested, this,
          &MainWindow::playMediaRequested);
}

void MainWindow::initToolbar() {

  createActions();

  ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
  ui->toolBar->setIconSize(QSize(28, 28));
  auto toolbarFont = ui->toolBar->font();
  toolbarFont.setBold(true);
  auto toolbarPointSize = toolbarFont.pointSize();
  toolbarFont.setPointSize(toolbarPointSize + 2);
  ui->toolBar->setFont(toolbarFont);
  ui->toolBar->setMovable(false);
  ui->toolBar->setFloatable(false);
}

void MainWindow::startSpinner() { spinner->start(); }

void MainWindow::stopSpinner() { spinner->stop(); }

void MainWindow::switchStackWidget(QWidget *widget, bool addToStackVector) {
  if (addToStackVector) {
    // prevent adding duplicate widget in stackVector
    if (stackVector.isEmpty() == false &&
        stackedWidget->currentWidget() != widget)
      stackVector.append(stackedWidget->currentWidget());
    else if (stackVector.isEmpty()) {
      stackVector.append(stackedWidget->currentWidget());
    }
  }
  stackedWidget->slideInWgt(widget);

  // call activate slot on page
  auto page = qobject_cast<Page *>(widget);
  if (page) {
    page->activate();
  }
}

void MainWindow::playMediaRequested(const QString &filePath) {
  QFileInfo file(filePath);
  if (file.exists() && file.isFile()) {
    if (playerPage) {
      switchStackWidget(playerPage);

      auto playMediaDelayed = [this, filePath]() {
        if (playerPage) {
          playerPage->play(filePath);
        }
      };

      QTimer::singleShot(300, this, playMediaDelayed);
    }
  } else {
    QMessageBox msgBox;
    msgBox.setIconPixmap(QPixmap(":/app/icon-64.png"));
    msgBox.setText(QString("Player: Unable to play requested file.\nFile Path: %1").arg(filePath));
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setDetailedText(
        QString("File: %1 doesn't exists or not a valid file.").arg(filePath));
    msgBox.exec();
  }
}

MainWindow::~MainWindow() { delete ui; }

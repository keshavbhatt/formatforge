#include "mainwindow.h"
#include "presetselector.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setWindowIcon(QIcon("://Icons/App/icon-64.png"));

  stackedWidget = new SlidingStackedWidget(this);
  ui->centralwidget->layout()->addWidget(stackedWidget);

  initPages();

  initToolbar();

  // init stackWidget
  stackedWidget->setAnimation(QEasingCurve::Type::OutQuart);
  stackedWidget->setSpeed(200);
  connect(stackedWidget, &QStackedWidget::currentChanged, this, [=](int arg1) {
    Q_UNUSED(arg1);

    mediaAction->setEnabled(stackedWidget->currentWidget() != mediaPage);
    outputSettingAction->setEnabled(stackedWidget->currentWidget() !=
                                    outputSettingPage);
    queueAction->setEnabled(stackedWidget->currentWidget() != queuePage);
    homeAction->setEnabled(stackedWidget->currentWidget() != homePage);
  });

  homeAction->setEnabled(stackedWidget->currentWidget() != homePage);
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

void MainWindow::createActions() {

  // create action
  homeAction =
      new QAction(QIcon("://Icons/App/icon-64.png"), tr("&Home"), this);
  mediaAction = new QAction(tr("&Media"), this);
  outputSettingAction = new QAction(tr("&Output Setting"), this);
  convertAction = new QAction(tr("&Convert"), this);
  queueAction = new QAction(tr("&Queue"), this);

  connect(homeAction, &QAction::triggered, this,
          [=]() { switchStackWidget(homePage); });

  connect(mediaAction, &QAction::triggered, this,
          [=]() { switchStackWidget(mediaPage); });

  connect(outputSettingAction, &QAction::triggered, this,
          [=]() { switchStackWidget(outputSettingPage); });

  connect(queueAction, &QAction::triggered, this,
          [=]() { switchStackWidget(queuePage); });

  // add action to toolbar
  ui->toolBar->addAction(homeAction);
  ui->toolBar->addAction(mediaAction);
  ui->toolBar->addAction(outputSettingAction);
  ui->toolBar->addAction(queueAction);

  // spinner widget in toolbar
  initSpinner();
  ui->toolBar->addWidget(spinner);

  ui->toolBar->addAction(convertAction);
}

void MainWindow::initPages() {
  // init pages
  homePage = new HomePage;
  mediaPage = new MediaPage;
  outputSettingPage = new OutputSettingPage;
  queuePage = new QueuePage;

  // add pages to stackedWidget
  stackedWidget->addWidget(homePage);
  stackedWidget->addWidget(mediaPage);
  stackedWidget->addWidget(outputSettingPage);
  stackedWidget->addWidget(queuePage);

  // navigation connections
  for (int i = 0; i < stackedWidget->count(); ++i) {
    auto page = stackedWidget->widget(i);
    connect(page, SIGNAL(nextPage()), stackedWidget, SLOT(slideInNext()));
  }

  // other connections
  connect(homePage, &HomePage::mediaFileLoaded, mediaPage,
          &MediaPage::loadMediaFiles);


}

void MainWindow::initToolbar() {

  createActions();

  ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
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
}

MainWindow::~MainWindow() { delete ui; }

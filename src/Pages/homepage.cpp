#include "homepage.h"
#include "ui_homepage.h"

#include <QDir>
#include <QFileDialog>
#include <QTimer>

HomePage::HomePage(QWidget *parent) : Page(parent), ui(new Ui::HomePage) {
  ui->setupUi(this);

  ui->welcomeIconLabel->setPixmap(QPixmap("://app/icon-128.png"));
  ui->welcomeLabel->setText(
      QString("<H1 style='color:silver;'>Welcome to %1</H1>")
          .arg(QApplication::applicationName()));

  connect(ui->addMediaPushButton, &QPushButton::clicked, this,
          &HomePage::addMedia);
}

HomePage::~HomePage() { delete ui; }

void HomePage::addMedia() {
  QStringList fileNames = QFileDialog::getOpenFileNames(
      this, tr("Select Media Files"), QDir::homePath(),
      tr("Media Files (*.mp3 *.mp4 *.avi *.mkv);;All Files (*)"));

  if (fileNames.isEmpty() == false) {
    emit goToNextPage();
    emit mediaFileLoaded(fileNames);
  }
}

bool HomePage::isEnabled() { return true; }

void HomePage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

Page *HomePage::getNextPage() const { return m_nextPage; }

Page *HomePage::getPreviousPage() const { return m_prevPage; }

void HomePage::setPreviousPage(Page *prevPage) { m_prevPage = prevPage; }

void HomePage::activate() {}

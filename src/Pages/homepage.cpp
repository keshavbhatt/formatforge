#include "homepage.h"
#include "ui_homepage.h"

#include <QFileDialog>
#include <QDir>

HomePage::HomePage(QWidget *parent) : QWidget(parent), ui(new Ui::HomePage) {
  ui->setupUi(this);

  ui->welcomeIconLabel->setPixmap(QPixmap("://Icons/App/icon-128.png"));
  ui->welcomeLabel->setText(
      QString("<H1 style='color:silver;'>Welcome to %1</H1>")
          .arg(QApplication::applicationName()));
}

HomePage::~HomePage() { delete ui; }

void HomePage::on_addMediaPushButton_clicked() {
  QStringList fileNames = QFileDialog::getOpenFileNames(
      this, tr("Select Media Files"), QDir::homePath(),
      tr("Media Files (*.mp3 *.mp4 *.avi *.mkv);;All Files (*)"));

  if(fileNames.isEmpty() == false){
      emit mediaFileLoaded(fileNames);
  }
}

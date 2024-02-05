#include "homepage.h"
#include "ui_homepage.h"

#include <QDir>
#include <QFileDialog>
#include <QTimer>

#include <Presets/defaultpresetreader.h>

HomePage::HomePage(QWidget *parent) : Page(parent), ui(new Ui::HomePage) {
  ui->setupUi(this);

  ui->welcomeIconLabel->setPixmap(QPixmap("://app/icon-128.png"));
  ui->welcomeLabel->setText(
      QString("<H1 style='color:silver;'>Welcome to %1</H1>")
          .arg(QApplication::applicationName()));

  ui->addMediaPushButton->setIcon(QIcon(":/primo/add.png"));
  connect(ui->addMediaPushButton, &QPushButton::clicked, this,
          &HomePage::addMedia);

  ui->addMediaFolderPushButton->setIcon(QIcon(":/primo/folder_add.png"));
  connect(ui->addMediaFolderPushButton, &QPushButton::clicked, this,
          &HomePage::addMedia);
}

HomePage::~HomePage() { delete ui; }

void HomePage::addMedia() {
  QString extensionFilter;
  QSet<QString> loadedOutputExtensions =
      DefaultPresetReader::getInstance()->getLoadedOutputExetensions();
  foreach (const QString &extension, loadedOutputExtensions) {
    extensionFilter += "*." + extension + " ";
  }

  // QStringList fileNames = QFileDialog::getOpenFileNames(
  //     this, tr("Select Media Files"), QDir::homePath(),
  //     tr("Media Files (*.mp3 *.mp4 *.avi *.mkv);;All Files (*)"));

  QStringList fileNames = QFileDialog::getOpenFileNames(
      this, tr("Select Media Files"), QDir::homePath(),
      tr("Media Files (%1);;All Files (*)").arg(extensionFilter.trimmed()));

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

void HomePage::activate() { emit updateStatusMessage(QString("")); }

#include "homepage.h"
#include "ui_homepage.h"

#include <QDir>
#include <QFileDialog>
#include <QTimer>

#include <Presets/defaultpresetreader.h>

#include <Core/filescanner.h>

HomePage::HomePage(QWidget *parent) : Page(parent), ui(new Ui::HomePage) {
  ui->setupUi(this);

  ui->welcomeIconLabel->setPixmap(QPixmap("://app/icon-128.png"));
  ui->welcomeLabel->setText(
      QString("<H1 style='color:silver;'>Welcome to %1</H1>")
          .arg(QApplication::applicationName()));

  ui->addMediaPushButton->setIcon(QIcon(":/primo/add.png"));
  connect(ui->addMediaPushButton, &QPushButton::clicked, this,
          &HomePage::addMediaFromExistingFiles);

  ui->addMediaFolderPushButton->setIcon(QIcon(":/primo/folder_add.png"));
  connect(ui->addMediaFolderPushButton, &QPushButton::clicked, this,
          &HomePage::addMediaFromFolder);
}

HomePage::~HomePage() { delete ui; }

void HomePage::addMediaFromFolder() {
  this->openFileSelector(QFileDialog::Directory);
}

void HomePage::addMediaFromExistingFiles() {
  this->openFileSelector(QFileDialog::ExistingFiles);
}

void HomePage::openFileSelector(QFileDialog::FileMode fileMode) {
  QString extensionFilter;
  QSet<QString> loadedOutputExtensions =
      DefaultPresetReader::getInstance()->getLoadedOutputExetensions();
  foreach (const QString &extension, loadedOutputExtensions) {
    extensionFilter += "*." + extension + " ";
  }

  QFileDialog fileDialog(this);
  fileDialog.setWindowTitle(tr("Select %1")
                                .arg(fileMode == QFileDialog::Directory
                                         ? "Folder containing Media Files"
                                         : "Media Files"));
  fileDialog.setDirectory(QDir::homePath());
  fileDialog.setFileMode(fileMode);
  if (fileMode == QFileDialog::ExistingFiles) {
    fileDialog.setNameFilter(
        tr("Media Files (%1);;All Files (*)").arg(extensionFilter.trimmed()));
  }

  if (fileDialog.exec()) {
    QStringList filePaths = fileDialog.selectedFiles();
    qDebug() << "Selected files" << filePaths;
    emit goToNextPage();
    emit mediaFileLoaded(filePaths);
  }
}

bool HomePage::isEnabled() { return true; }

void HomePage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

Page *HomePage::getNextPage() const { return m_nextPage; }

Page *HomePage::getPreviousPage() const { return m_prevPage; }

void HomePage::setPreviousPage(Page *prevPage) { m_prevPage = prevPage; }

void HomePage::activate() { emit updateStatusMessage(QString("")); }

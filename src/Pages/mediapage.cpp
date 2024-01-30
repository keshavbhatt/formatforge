#include "mediapage.h"
#include "ui_mediapage.h"
#include <QDebug>

MediaPage::MediaPage(QWidget *parent) : Page(parent), ui(new Ui::MediaPage) {
  ui->setupUi(this);

  connect(ui->nextPushButton, &QPushButton::clicked, this,
          [=]() { emit goToNextPage(); });

  connect(ui->removeAllPushButton, &QPushButton::clicked, this, [=]() {
    ui->mediaListWidget->clear();
    this->updatePage();
    emit goToPreviousPage();
  });
}

void MediaPage::loadMediaFiles(const QStringList &fileNameList) {
  ui->mediaListWidget->addItems(fileNameList);
}

MediaPage::~MediaPage() { delete ui; }

Page *MediaPage::getNextPage() const { return m_nextPage; }

Page *MediaPage::getPreviousPage() const { return m_prevPage; }

void MediaPage::setPreviousPage(Page *prevPage) { m_prevPage = prevPage; }

void MediaPage::activate() { this->updatePage(); }

void MediaPage::updatePage() {

  bool listNotEmpty = ui->mediaListWidget->count() > 0;

  ui->nextPushButton->setEnabled(listNotEmpty);
  ui->removeAllPushButton->setEnabled(listNotEmpty);
  ui->removeSelectedPushButton->setEnabled(listNotEmpty);
}

bool MediaPage::isEnabled() { return ui->mediaListWidget->count() > 0; }

void MediaPage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

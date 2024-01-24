#include "mediapage.h"
#include "ui_mediapage.h"
#include <QDebug>

MediaPage::MediaPage(QWidget *parent) : QWidget(parent), ui(new Ui::MediaPage) {
  ui->setupUi(this);

  connect(ui->nextPushButton, &QPushButton::clicked, this,
          &MediaPage::goToOutputSettingsPage);
}

void MediaPage::loadMediaFiles(const QStringList &fileNameList) {
  ui->mediaListWidget->addItems(fileNameList);
}

MediaPage::~MediaPage() { delete ui; }

void MediaPage::goToOutputSettingsPage() { emit nextPage(); }

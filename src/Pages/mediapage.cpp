#include "mediapage.h"
#include "ui_mediapage.h"
#include <QDebug>

MediaPage::MediaPage(QWidget *parent) : QWidget(parent), ui(new Ui::MediaPage) {
  ui->setupUi(this);
}

void MediaPage::loadMediaFiles(const QStringList &fileNameList) {
  qDebug() << fileNameList;
}

MediaPage::~MediaPage() { delete ui; }

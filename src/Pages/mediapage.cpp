#include "mediapage.h"
#include "outputsettingpage.h"
#include "ui_mediapage.h"
#include <QDebug>

MediaPage::MediaPage(QWidget *parent) : Page(parent), ui(new Ui::MediaPage) {
  ui->setupUi(this);

  spinner = new Spinner(this);
  ui->spinnerLayout->addWidget(spinner);

  connect(ui->nextPushButton, &QPushButton::clicked, this,
          [=]() { emit goToNextPage(); });

  connect(ui->removeAllPushButton, &QPushButton::clicked, this, [=]() {
    ui->mediaListWidget->clear();
    this->updatePage();
    emit goToPreviousPage();
  });

  connect(&mediaProcessor, &MediaProcessor::mediaProcessingFinished, this,
          [=]() { this->spinner->stop(); });

  connect(&mediaProcessor, &MediaProcessor::mediaProcessingProgress, this,
          [=](int currentFileIndex, int totalFiles) {
            qDebug() << "Processing file " << currentFileIndex << " of "
                     << totalFiles;
          });

  connect(&mediaProcessor, &MediaProcessor::mediaProcessed, this,
          &MediaPage::addMediaItem);
}

void MediaPage::addMediaItem(const QString &fileName, const QString &result) {
  qDebug() << "Media Processed" << fileName << result;
  QListWidgetItem *item = new QListWidgetItem(fileName);
  ui->mediaListWidget->addItem(item);
}

void MediaPage::loadMediaFiles(const QStringList &fileNameList) {
  processMedia(fileNameList);
}

void MediaPage::processMedia(const QStringList &fileNameList) {
  spinner->start();
  mediaProcessor.processMediaFiles(fileNameList);
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

  // remove selected preset from output settings page
  if (!listNotEmpty) {
    OutputSettingPage *outputSettingPage =
        qobject_cast<OutputSettingPage *>(getNextPage());
    if (outputSettingPage) {
      outputSettingPage->clearPresetSelection();
    } else {
      qWarning() << Q_FUNC_INFO
                 << "Casting failed, is nextPage for MediaPage set "
                    "correctly?";
    }
  }
}

bool MediaPage::isEnabled() { return ui->mediaListWidget->count() > 0; }

void MediaPage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

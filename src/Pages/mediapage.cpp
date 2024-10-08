#include "mediapage.h"
#include "ui_mediapage.h"

MediaPage::MediaPage(QWidget *parent) : Page(parent), ui(new Ui::MediaPage) {
  ui->setupUi(this);

  spinner = new Spinner(this);
  ui->spinnerLayout->addWidget(spinner);

  ui->mediaListWidget->setSpacing(6);
  ui->mediaListWidget->setEmptyText(tr("No media found"));
  ui->mediaListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

  // start UI connections
  ui->nextPushButton->setIcon(QIcon(":/primo/next.png"));
  connect(ui->nextPushButton, &QPushButton::clicked, this,
          [=]() { emit goToNextPage(); });

  ui->addMorePushButton->setIcon(QIcon(":/primo/add.png"));
  connect(ui->addMorePushButton, &QPushButton::clicked, this,
          [=]() { emit addMoreFiles(); });

  ui->removeSelectedPushButton->setIcon(QIcon(":/primo/delete.png"));
  connect(ui->removeSelectedPushButton, &QPushButton::clicked, this,
          &MediaPage::removeSelectedMediaListWidgetItems);

  ui->removeAllPushButton->setIcon(QIcon(":/primo/folder_delete.png"));
  connect(ui->removeAllPushButton, &QPushButton::clicked, this, [=]() {
    ui->mediaListWidget->clear();
    this->updatePage();
    emit goToPreviousPage();
  });

  connect(ui->mediaListWidget, &QListWidget::itemSelectionChanged, this,
          [=]() { updateBottomToolbarButtons(); });

  connect(ui->mediaListWidget, &QListWidget::itemDoubleClicked, this,
          &MediaPage::mediaItemDoubleClicked);
  // end UI connections

  // start FFProbeMetaDataExtractor connections
  connect(&m_mediaMetadataProcessor,
          &FFProbeMetaDataExtractor::mediaProcessingFinished, this, [=]() {
            this->spinner->stop();
            this->updatePage();
          });

  connect(&m_mediaMetadataProcessor, &FFProbeMetaDataExtractor::mediaProcessed,
          this, &MediaPage::addMediaItemToView);
  // end FFProbeMetaDataExtractor connections
}

void MediaPage::updateBottomToolbarButtons() {
  bool listNotEmpty = ui->mediaListWidget->count() > 0;

  ui->nextPushButton->setEnabled(listNotEmpty);
  ui->removeAllPushButton->setEnabled(listNotEmpty);
  ui->removeSelectedPushButton->setEnabled(
      !ui->mediaListWidget->selectedItems().isEmpty());

  updatePageStatusMessage();
}

void MediaPage::removeSelectedMediaListWidgetItems() {
  QList<QListWidgetItem *> selectedItems = ui->mediaListWidget->selectedItems();

  foreach (QListWidgetItem *selectedItem, selectedItems) {
    QWidget *itemWidget = ui->mediaListWidget->itemWidget(selectedItem);

    ui->mediaListWidget->removeItemWidget(selectedItem);
    delete selectedItem;

    if (itemWidget) {
      delete itemWidget;
    }
  }
  updateBottomToolbarButtons();
  this->updatePage();
}

void MediaPage::addMediaItemToView(const QString &filePath,
                                   const QString &result) {

  MediaMetaData *mediaMetaData =
      FFProbeParser::getMediaMetaDataFor(filePath, result);
  if (mediaMetaData) {
    QScrollBar *vScrollBar = ui->mediaListWidget->verticalScrollBar();
    bool atBottom = vScrollBar->value() == vScrollBar->maximum();

    MediaItemWidget *mediaItemWidget =
        new MediaItemWidget(ui->mediaListWidget, filePath, mediaMetaData);
    QListWidgetItem *item = new QListWidgetItem(ui->mediaListWidget);
    item->setSizeHint(mediaItemWidget->minimumSizeHint());
    ui->mediaListWidget->setItemWidget(item, mediaItemWidget);

    if (atBottom) {
      ui->mediaListWidget->scrollToBottom();
    }
  } else {
    qWarning() << filePath << "not added, unable to get metadata!";
  }
}

void MediaPage::loadMediaFiles(const QStringList &filePathList) {

  ui->mediaListWidget->scrollToBottom();

  QSet<QString> loadedOutputExtensions =
      DefaultPresetReader::getInstance()->getLoadedOutputExetensions();
  QStringList nameFilters;
  foreach (const QString &extension, loadedOutputExtensions) {
    nameFilters << "*." + extension;
  }

  foreach (QString filePath, filePathList) {
    QFileInfo fileInfo(filePath);
    if (fileInfo.isDir()) {
      QDir selectedDir(filePath);
      FileScanner *fileScanner = new FileScanner(selectedDir, nameFilters);
      connect(fileScanner, &FileScanner::scanningFinished, this,
              [=](const QStringList &filePaths) {
                processMedia(filePaths);
                fileScanner->deleteLater();
                this->spinner->stop();
              });
      this->spinner->start();
      fileScanner->start();
    } else {
      processMedia(QStringList{filePath});
    }
  }
}

void MediaPage::processMedia(const QStringList &fileNameList) {
  spinner->start();
  m_mediaMetadataProcessor.processMediaFiles(fileNameList);
}

MediaPage::~MediaPage() { delete ui; }

Page *MediaPage::getNextPage() const { return m_nextPage; }

Page *MediaPage::getPreviousPage() const { return m_prevPage; }

void MediaPage::setPreviousPage(Page *prevPage) { m_prevPage = prevPage; }

void MediaPage::updatePage() {

  updateBottomToolbarButtons();

  // remove selected preset from output settings page
  if (!(ui->mediaListWidget->count() > 0)) {
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

  updatePageStatusMessage();
  emit updateMainToolbarAction();
}

QStringList MediaPage::getLoadedMediaFilesPath() {
  QStringList loadedMediaFilesPath;

  for (int i = 0, total = ui->mediaListWidget->count(); i < total; ++i) {
    QListWidgetItem *item = ui->mediaListWidget->item(i);
    if (item) {
      QWidget *itemWidget = ui->mediaListWidget->itemWidget(item);
      MediaItemWidget *mediaItemWidget =
          qobject_cast<MediaItemWidget *>(itemWidget);
      if (mediaItemWidget) {
        loadedMediaFilesPath.append(mediaItemWidget->getFilePath());
      }
    }
  }
  return loadedMediaFilesPath;
}

QList<ConversionItem> MediaPage::getSelectedMediaItems() const {

  QList<ConversionItem> conversionItems;
  for (int i = 0, total = ui->mediaListWidget->count(); i < total; ++i) {
    QListWidgetItem *item = ui->mediaListWidget->item(i);
    if (item) {
      QWidget *itemWidget = ui->mediaListWidget->itemWidget(item);
      MediaItemWidget *mediaItemWidget =
          qobject_cast<MediaItemWidget *>(itemWidget);
      if (mediaItemWidget) {
        conversionItems.append(ConversionItem(
            mediaItemWidget->getFilePath(), "", mediaItemWidget->getId(), ""));
      }
    }
  }
  return conversionItems;
}

void MediaPage::mediaItemDoubleClicked(QListWidgetItem *item) {
  if (item) {
    QWidget *itemWidget = ui->mediaListWidget->itemWidget(item);
    MediaItemWidget *mediaItemWidget =
        qobject_cast<MediaItemWidget *>(itemWidget);
    if (mediaItemWidget) {
      emit playMediaRequested(mediaItemWidget->getFilePath());
    }
  }
}

bool MediaPage::isEnabled() { return ui->mediaListWidget->count() > 0; }

void MediaPage::setNextPage(Page *nextPage) { m_nextPage = nextPage; }

void MediaPage::activate() { this->updatePage(); }

void MediaPage::updatePageStatusMessage() {
  QString message = "Add media file for conversion";
  if (ui->mediaListWidget->count() > 0) {
    message = QString("Loaded %1 media files, press Next")
                  .arg(ui->mediaListWidget->count());
  }
  emit updateStatusMessage(message);
}

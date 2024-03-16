#include "mediainfowidget.h"
#include "ui_mediainfowidget.h"

#include <QMenu>

MediaInfoWidget::MediaInfoWidget(QWidget *parent, MediaInfo mediaInfo)
    : QWidget(parent), ui(new Ui::MediaInfoWidget), m_mediaInfo(mediaInfo) {
  ui->setupUi(this);

  this->setWindowTitle(QApplication::applicationName() +
                       " | Media Information (" + mediaInfo.fileName() + ")");

  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Key"
                                                           << "Value");
  setupContextMenuForMediaInfoTable();

  connect(ui->filterLineEdit, &QLineEdit::textChanged, this,
          &MediaInfoWidget::applyFilter);

  if (m_mediaInfo.isValid()) {
    ui->filePathLabel->setText(m_mediaInfo.filePath());
    populateTableWidget(ui->tableWidget, m_mediaInfo);
  } else {
    QMessageBox::critical(this, "Error", "Invalid media information!");
  }

  foreach (auto rb, ui->filterRbFrame->findChildren<QRadioButton *>()) {
    connect(rb, &QRadioButton::clicked, this,
            &MediaInfoWidget::updateFilterText);
  }

  connect(ui->filterLineEdit, &QLineEdit::textChanged, this,
          &MediaInfoWidget::updateFilterRadioButton);

  ui->allRb->setChecked(true);

  ui->filterLineEdit->setFocus();
}

MediaInfoWidget::~MediaInfoWidget() { delete ui; }

void MediaInfoWidget::populateTableWidget(QTableWidget *tableWidget,
                                          const MediaInfo &mediaInfo) {
  tableWidget->clearContents();
  tableWidget->setRowCount(0);

  int totalRows =
      mediaInfo.generalFileInfo().size() + mediaInfo.mediaInfo().size();

  tableWidget->setRowCount(totalRows);

  // Populate general file info
  int row = 0;
  QList<QPair<QString, QVariant>> generalFileInfo = mediaInfo.generalFileInfo();
  for (const auto &pair : generalFileInfo) {
    tableWidget->setItem(row, 0, new QTableWidgetItem(pair.first));
    tableWidget->setItem(row, 1, new QTableWidgetItem(pair.second.toString()));
    row++;
  }

  // Populate media info
  QList<QPair<QString, QVariant>> mediaInfoList = mediaInfo.mediaInfo();
  for (const auto &pair : mediaInfoList) {
    tableWidget->setItem(row, 0, new QTableWidgetItem(pair.first));
    tableWidget->setItem(row, 1, new QTableWidgetItem(pair.second.toString()));
    row++;
  }
}

void MediaInfoWidget::applyFilter(const QString &filterText) {
  for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
    bool rowVisible = false;
    for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
      QTableWidgetItem *item = ui->tableWidget->item(row, column);
      if (item && item->text().contains(filterText, Qt::CaseInsensitive)) {
        rowVisible = true;
        break;
      }
    }
    ui->tableWidget->setRowHidden(row, !rowVisible);
  }
}

void MediaInfoWidget::updateFilterText() {
  QString filterText;
  if (ui->allRb->isChecked()) {
    filterText = "";
  } else if (ui->fileRb->isChecked()) {
    filterText = "FileInfo::";
  } else if (ui->formatRb->isChecked()) {
    filterText = "Format::";
  } else if (ui->streamRb->isChecked()) {
    filterText = "Stream::";
  }
  ui->filterLineEdit->setText(filterText);
}

void MediaInfoWidget::updateFilterRadioButton(const QString &filterText) {
  if (filterText.isEmpty()) {
    ui->allRb->setChecked(true);
  } else if (filterText == "FileInfo::") {
    ui->fileRb->setChecked(true);
  } else if (filterText == "Format::") {
    ui->formatRb->setChecked(true);
  } else if (filterText == "Stream::") {
    ui->streamRb->setChecked(true);
  }
}

void MediaInfoWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    close();
  } else if (event->matches(QKeySequence::Copy)) {
    copyRowActionTriggered();
  } else {
    QWidget::keyPressEvent(event);
  }
}

void MediaInfoWidget::setupContextMenuForMediaInfoTable() {

  QMenu *contextMenu = new QMenu(this);

  QAction *copyRowAction = new QAction("Copy Selected Row(s)", this);
  copyRowAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
  connect(copyRowAction, &QAction::triggered, this,
          &MediaInfoWidget::copyRowActionTriggered);

  contextMenu->addAction(copyRowAction);

  ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this,
          [=](const QPoint &pos) {
            contextMenu->exec(ui->tableWidget->viewport()->mapToGlobal(pos));
          });
}

void MediaInfoWidget::copyRowActionTriggered() {
  QModelIndexList selectedIndexes =
      ui->tableWidget->selectionModel()->selectedIndexes();

  if (selectedIndexes.isEmpty())
    return;

  std::sort(selectedIndexes.begin(), selectedIndexes.end());

  QString copiedText;
  int currentRow = -1;
  for (const QModelIndex &index : selectedIndexes) {
    if (index.row() != currentRow) {
      if (!copiedText.isEmpty())
        copiedText += '\n';
      currentRow = index.row();
    } else {
      copiedText += '\t';
    }
    copiedText += index.data().toString();
  }
  QApplication::clipboard()->setText(copiedText);
}

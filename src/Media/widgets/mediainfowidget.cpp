#include "mediainfowidget.h"
#include "ui_mediainfowidget.h"

MediaInfoWidget::MediaInfoWidget(QWidget *parent, MediaInfo mediaInfo)
    : QWidget(parent), ui(new Ui::MediaInfoWidget), m_mediaInfo(mediaInfo) {
  ui->setupUi(this);

  this->setWindowTitle(QApplication::applicationName() +
                       " | Media Information");

  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Key"
                                                           << "Value");

  connect(ui->filterLineEdit, &QLineEdit::textChanged, this,
          &MediaInfoWidget::applyFilter);

  if (m_mediaInfo.isValid()) {
    ui->filePathLabel->setText(m_mediaInfo.filePath());
    populateTableWidget(ui->tableWidget, m_mediaInfo);
  } else {
    QMessageBox::critical(this, "Error", "Invalid media information!");
  }
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

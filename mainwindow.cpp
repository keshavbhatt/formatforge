#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <conversionmanager.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ConversionManager *conversionManager = new ConversionManager();
    conversionManager->createTabs(ui->tabWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

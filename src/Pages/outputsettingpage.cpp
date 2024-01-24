#include "outputsettingpage.h"
#include "ui_outputsettingpage.h"

OutputSettingPage::OutputSettingPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::OutputSettingPage) {
  ui->setupUi(this);
}

OutputSettingPage::~OutputSettingPage() { delete ui; }

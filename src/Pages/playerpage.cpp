#include "playerpage.h"
#include "ui_playerpage.h"
#include <Player/mpvobject.h>
#include <QQmlApplicationEngine>
#include <QQmlContext>

PlayerPage::PlayerPage(QWidget *parent) : Page(parent), ui(new Ui::PlayerPage) {
  ui->setupUi(this);

  this->layout()->setContentsMargins(0, 0, 0, 0);

  ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:///qml/MainWindow.qml")));

  QObject *rootObject = ui->quickWidget->rootObject();
  if (rootObject) {
    // ui->quickWidget->engine()->rootContext()->setContextProperty(
    //     "playerPageObject", this);

    // ui->quickWidget->installEventFilter(this);

    m_mpvObject = rootObject->findChild<MpvObject *>("mpvObject");
    m_mpvObject->setParent(this);
  } else {
    qWarning() << Q_FUNC_INFO << "Unable to find player object in qml context";
  }

  ui->quickWidget->setFocus();
}

void PlayerPage::keyPressEvent(QKeyEvent *event) {

  // QObject *rootObject = ui->quickWidget->rootObject();
  // if (rootObject) {
  //   QCoreApplication::sendEvent(rootObject, &event);
  // } else {
  //   qWarning() << Q_FUNC_INFO << "Unable to find player object in qml
  //   context";
  // }

  // Call the base class implementation
  QWidget::keyPressEvent(event);
}

bool PlayerPage::eventFilter(QObject *obj, QEvent *event) {
  Q_UNUSED(obj);
  if (event->type() == QEvent::KeyPress) {
    QObject *rootObject = ui->quickWidget->rootObject();
    if (rootObject) {
      auto kp = static_cast<QKeyEvent *>(event);
      emit keyPressed(kp->key(), kp->modifiers());

      // QCoreApplication::sendEvent(rootObject, event);
    }
    // emit rootObject->keyPressed(static_cast<QKeyEvent *>(event));
    return true; // Consume the event to prevent further processing
  }
  return false; // Pass the event through for normal handling
}

void PlayerPage::play(const QString &filePath) {
  if (m_mpvObject) {
    m_mpvObject->loadFile(filePath);
    m_mpvObject->play();
  }
}

PlayerPage::~PlayerPage() {
  qDebug() << "PlayerPage destructor called";
  delete ui;
}

bool PlayerPage::isEnabled() { return true; }

void PlayerPage::setNextPage(Page *nextPage) { Q_UNUSED(nextPage); }

void PlayerPage::setPreviousPage(Page *prevPage) { Q_UNUSED(prevPage); }

Page *PlayerPage::getNextPage() const { return nullptr; }

Page *PlayerPage::getPreviousPage() const { return nullptr; }

void PlayerPage::activate() { ui->quickWidget->setFocus(); }

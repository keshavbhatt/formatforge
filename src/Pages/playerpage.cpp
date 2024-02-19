#include "playerpage.h"
#include "ui_playerpage.h"
#include <Player/mpvobject.h>
#include <QAction>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>

PlayerPage::PlayerPage(QWidget *parent) : Page(parent), ui(new Ui::PlayerPage) {
  ui->setupUi(this);

  this->layout()->setContentsMargins(0, 0, 0, 0);

  ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:///qml/MainWindow.qml")));

  QObject *rootObject = ui->quickWidget->rootObject();
  if (rootObject) {
    m_mpvObject = rootObject->findChild<MpvObject *>("mpvObject");
    m_mpvObject->setParent(this); // to properly delete qml mpvObject

    // reuse actions from qml
    auto actionsListQml =
        rootObject->findChild<QObject *>("playerActions")->children();
    foreach (QObject *actionObject, actionsListQml) {
      if (actionObject->inherits("QQuickAction1")) {
        QString text = QQmlProperty::read(actionObject, "text").toString();
        QString shortcut =
            QQmlProperty::read(actionObject, "shortcut").toString();
        if (shortcut.isEmpty() == false) {
          QAction *action = new QAction(text, this);
          QObject::connect(action, &QAction::triggered, [=]() {
            QMetaObject::invokeMethod(actionObject, "triggered");
          });
          action->setShortcut(QKeySequence(shortcut));
          this->addAction(action);
        }
      }
    }
  } else {
    qWarning() << Q_FUNC_INFO << "Unable to find player object in qml context";
  }
  ui->quickWidget->setFocus();
}

void PlayerPage::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_F11) {
    Q_UNIMPLEMENTED();
    if (this->isFullScreen()) {
      this->showNormal();
    } else {
      this->showFullScreen();
    }
  } else {
    QWidget::keyPressEvent(event);
  }
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

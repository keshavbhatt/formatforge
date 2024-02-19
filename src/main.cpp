#include "Widgets/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QStyleFactory>
#include <QTranslator>

#include <Player/mpvobject.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QApplication::setApplicationName(
      QString(APPLICATION_FULLNAME).replace("_", " "));
  QApplication::setDesktopFileName("com.ktechpit.formatforge");
  QApplication::setOrganizationDomain("com.ktechpit");
  QApplication::setOrganizationName("org.keshavnrj.ubuntu");
  QApplication::setApplicationVersion(VERSIONSTR);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "FormatForgeStudio_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  // qApp->setStyle(QStyleFactory::create("fusion"));

  // Qt sets the locale in the QGuiApplication constructor, but libmpv
  // requires the LC_NUMERIC category to be set to "C", so change it back.
  std::setlocale(LC_NUMERIC, "C");

  qmlRegisterType<MpvObject>("mpvz", 1, 0, "MpvObject");

  MainWindow w;
  w.setWindowTitle(QApplication::applicationName());
  w.show();
  return a.exec();
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = formatforge
TEMPLATE = app

# No debug output in release mode
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# Print if this is a debug or release build
CONFIG(debug, debug|release) {
    message("This is a debug build")
} else {
    message("This is a release build")
}

# Set program version
VERSION = 1.0
DEFINES += VERSIONSTR=\\\"$${VERSION}\\\"


APPLICATION_FULLNAME = FormatForge_Studio
DEFINES += APPLICATION_FULLNAME=\\\"$${APPLICATION_FULLNAME}\\\"

# Define git info
GIT_HASH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --short HEAD)\\\""
GIT_BRANCH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --abbrev-ref HEAD)\\\""
BUILD_TIMESTAMP="\\\"$$system(date -u +\""%Y-%m-%dT%H:%M:%SUTC\"")\\\""
DEFINES += GIT_HASH=$$GIT_HASH GIT_BRANCH=$$GIT_BRANCH BUILD_TIMESTAMP=$$BUILD_TIMESTAMP

include(Widgets/WaitingSpinnerWidget/WaitingSpinner.pri)
include(Widgets/SlidingStackedWidget/SlidingStackedWidget.pri)


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    Widgets/mainwindow.cpp \
    Core/mimedatabasemanager.cpp \
    Format/imageformat.cpp \
    Media/audiofile.cpp \
    Media/imagefile.cpp \
    Media/videofile.cpp \
    MediaConverter/audioconverter.cpp \
    MediaConverter/imageconverter.cpp \
    MediaConverter/videoconverter.cpp \
    Pages/homepage.cpp \
    Pages/mediapage.cpp \
    Pages/outputsettingpage.cpp \
    Pages/queuepage.cpp \
    Core/conversionmanager.cpp \
    Presets/defaultpresetreader.cpp \
    Presets/preset.cpp \
    Presets/widgets/presetselector.cpp \
    Presets/widgets/presettabwidget.cpp \
    Widgets/spinner.cpp \
    Core/utils.cpp

HEADERS += \
    Widgets/mainwindow.h \
    Core/conversionmanager.h \
    Format/format.h \
    Format/imageformat.h \
    Media/audiofile.h \
    Media/imagefile.h \
    Media/mediafile.h \
    Media/videofile.h \
    MediaConverter/audioconverter.h \
    MediaConverter/imageconverter.h \
    MediaConverter/mediaconverter.h \
    MediaConverter/videoconverter.h \
    Pages/homepage.h \
    Pages/mediapage.h \
    Pages/outputsettingpage.h \
    Pages/queuepage.h \
    Presets/defaultpresetreader.h \
    Core/mimedatabasemanager.h \
    Presets/preset.h \
    Presets/widgets/presetselector.h \
    Presets/widgets/presettabwidget.h \
    Widgets/spinner.h \
    Core/utils.h

FORMS += \
    Widgets/mainwindow.ui \
    Pages/homepage.ui \
    Pages/mediapage.ui \
    Pages/outputsettingpage.ui \
    Pages/queuepage.ui \
    Presets/widgets/presetselector.ui \
    Presets/widgets/presettabwidget.ui \
    Widgets/spinner.ui

TRANSLATIONS += \
    Locales/FormatForgeStudio_en_IN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons/icons.qrc \
    Presets/resources/presets.qrc

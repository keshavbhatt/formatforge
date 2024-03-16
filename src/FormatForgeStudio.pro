QT       += core gui qml quick quickwidgets x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = formatforge
TEMPLATE = app

LIBS += -lmpv -lxcb

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
    Conversion/conversionmanager.cpp \
    Conversion/conversionprocess.cpp \
    Conversion/widgets/conversionitemwidget.cpp \
    Core/filescanner.cpp \
    Media/mediainfo.cpp \
    Media/widgets/mediainfowidget.cpp \
    MediaProcessor/cache/cachestore.cpp \
    Pages/playerpage.cpp \
    Player/mpvobject.cpp \
    Settings/settingsmanager.cpp \
    Media/widgets/mediaitemwidget.cpp \
    MediaProcessor/metadata/audiometadata.cpp \
    MediaProcessor/metadata/videometadata.cpp \
    MediaProcessor/metadata_extractors/ffmpegthumbnailextractor.cpp \
    MediaProcessor/metadata_extractors/ffprobemetadataextractor.cpp \
    MediaProcessor/metadata_parsers/ffprobeparser.cpp \
    Conversion/conversionitem.cpp \
    Widgets/customlistwidget.cpp \
    Widgets/progresslabel.cpp \
    main.cpp \
    Widgets/mainwindow.cpp \
    Core/mimedatabasemanager.cpp \
    Pages/homepage.cpp \
    Pages/mediapage.cpp \
    Pages/outputsettingpage.cpp \
    Pages/queuepage.cpp \
    Presets/defaultpresetreader.cpp \
    Presets/preset.cpp \
    Presets/widgets/presetselector.cpp \
    Presets/widgets/presettabwidget.cpp \
    Widgets/spinner.cpp \
    Core/utils.cpp

HEADERS += \
    Conversion/conversionmanager.h \
    Conversion/conversionprocess.h \
    Conversion/widgets/conversionitemwidget.h \
    Core/filescanner.h \
    Media/mediainfo.h \
    Media/widgets/mediainfowidget.h \
    MediaProcessor/cache/cachestore.h \
    MediaProcessor/metadata_extractors/metadata_extractor.h \
    Pages/playerpage.h \
    Player/mpvhelpers.h \
    Player/mpvobject.h \
    Player/qthelper.hpp \
    Settings/settings_constants.h \
    Settings/settingsmanager.h \
    Media/widgets/mediaitemwidget.h \
    MediaProcessor/metadata/audiometadata.h \
    MediaProcessor/metadata/mediametadata.h \
    MediaProcessor/metadata/videometadata.h \
    MediaProcessor/metadata_extractors/ffmpegthumbnailextractor.h \
    MediaProcessor/metadata_extractors/ffprobemetadataextractor.h \
    MediaProcessor/metadata_parsers/ffprobeparser.h \
    Pages/page.h \
    Conversion/conversionitem.h \
    Widgets/customlistwidget.h \
    Widgets/mainwindow.h \
    Pages/homepage.h \
    Pages/mediapage.h \
    Pages/outputsettingpage.h \
    Pages/queuepage.h \
    Presets/defaultpresetreader.h \
    Core/mimedatabasemanager.h \
    Presets/preset.h \
    Presets/widgets/presetselector.h \
    Presets/widgets/presettabwidget.h \
    Widgets/progresslabel.h \
    Widgets/spinner.h \
    Core/utils.h

FORMS += \
    Conversion/widgets/conversionitemwidget.ui \
    Media/widgets/mediainfowidget.ui \
    Media/widgets/mediaitemwidget.ui \
    Pages/playerpage.ui \
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
    Media/resources/res.qrc \
    Player/player.qrc \
    Presets/resources/presets.qrc

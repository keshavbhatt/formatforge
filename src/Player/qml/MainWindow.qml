import QtQuick 2.0
import QtQuick.Window 2.0

import mpvz 1.0
import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.1

Item {
    id: window
    anchors.fill: parent
    objectName: "mainWindow"
    focus: true

    property bool videoLoaded: mpvPlayer.mpvObject.playlistCount >= 1
                               && videoWidth > 0 && videoHeight > 0
    property int videoWidth: mpvPlayer.mpvObject.dwidth
    property int videoHeight: mpvPlayer.mpvObject.dheight

    QtObject {
        id: config
        property bool autoplayNextFile: true
        property bool showPlaybackInfo: false
        property bool showConsole: false
        property bool do60fps: false
        property bool showTimeLeft: false
    }

    visible: true

    readonly property alias mpvObject: mpvPlayer.mpvObject
    readonly property alias sidebar: mpvPlayer.sidebar
    readonly property bool isPlaying: !mpvPlayer.mpvObject.paused

    property bool intialized: false
    property bool hideMenuBar: true
    property bool isFullscreen: false

    readonly property bool bordersVisible: !hideBorders && !pictureInPicture
    property bool hideBorders: false
    property string alwaysOnTop: 'never' // 'never', 'always', 'whilePlaying'

    property bool pictureInPicture: false
    property int pipWidth: videoLoaded ? pipHeight * videoWidth / videoHeight : 480
    property int pipHeight: 270
    property int pipMargin: 10
    property point beforePipPoint: Qt.point(0, 0)
    property int beforePipVisibility: 0


    // Connections {
    //     target: playerPageObject
    //     onKeyPressed: {
    //         appActions.handleKeyEvent(key, modifiers);
    //     }
    // }


    AppActions {
        id: appActions
    }

    AppContextMenu {
        id: contextMenu
    }

    MpvPlayer {
        id: mpvPlayer
        anchors.fill: parent
    }

}

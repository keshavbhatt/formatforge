import QtQuick 2.1
import QtQuick.Controls 1.4

QtObject {
    //--- Open
    property Action openFileAction: Action {
        text: "Open File"
        shortcut: "Ctrl+O"
        onTriggered: mpvPlayer.selectFile()
    }

    // property Action openFolderAction: Action {
    //     text: "Folder"
    //     shortcut: "Ctrl+G"
    //     onTriggered: mpvPlayer.selectFolder()
    // }

    // property Action filePropertiesAction: Action {
    //     text: "Properties"
    //     shortcut: "Shift+F10"
    //     enabled: false
    //     // onTriggered:
    // }

    // property Action exitAction: Action {
    //     text: "Exit"
    //     shortcut: "Alt+X"
    //     onTriggered: Qt.quit()
    // }

    //--- Play
    property Action playPauseAction: Action {
        text: "Play/Pause"
        shortcut: "Space"
        onTriggered: mpvObject.playPause()
    }



    property Action stopAction: Action {
        text: "Stop playback"
        shortcut: "Q"
        onTriggered: mpvObject.stop()
    }

    // property Action previousVideoAction: Action {
    //     text: "Previous"
    //     shortcut: "PgUp"
    //     onTriggered: mpvPlayer.previousVideo()
    // }

    // property Action nextVideoAction: Action {
    //     text: "Next"
    //     shortcut: "PgDown"
    //     onTriggered: mpvPlayer.nextVideo()
    // }

    //--- Play > Speed
    property Action resetSpeedAction: Action {
        text: "Reset Playback Speed"
        shortcut: "Backspace"
        onTriggered: mpvObject.resetSpeed()
    }

    property Action playFasterAction: Action {
        text: "+10% Playback Speed"
        shortcut: "+"
        onTriggered: mpvObject.speedUp()
    }

    property Action playFasterAction2: Action {
        shortcut: "="
        onTriggered: mpvObject.speedUp()
    }

    property Action playSlowerAction: Action {
        text: "-10% Playback Speed"
        shortcut: "-"
        onTriggered: mpvObject.speedDown()
    }

    property Action halfSpeedAction: Action {
        text: "/2 Playback Speed"
        shortcut: "["
        onTriggered: mpvObject.halfSpeed()
    }
    property Action doubleSpeedAction: Action {
        text: "x2 Playback Speed"
        shortcut: "]"
        onTriggered: mpvObject.doubleSpeed()
    }

    //--- Play > Seek
    property Action seekBeginningAction: Action {
        text: "Beginning"
        shortcut: "Home"
        onTriggered: mpvPlayer.seekBeginning()
    }

    property Action seekBackwardAction: Action {
        text: "-5 sec"
        shortcut: "Left"
        onTriggered: mpvPlayer.seekBackward()
    }

    property Action seekForwardAction: Action {
        text: "+5 sec"
        shortcut: "Right"
        onTriggered: mpvPlayer.seekForward()
    }

    property Action stepBackwardAction: Action {
        text: "Prev Frame"
        shortcut: ","
        onTriggered: mpvObject.stepBackward()
    }

    property Action stepForwardAction: Action {
        text: "Next Frame"
        shortcut: "."
        onTriggered: mpvObject.stepForward()
    }

    //--- Video
    property Action toggleHwdecAction: Action {
        text: "hwdec"
        shortcut: "Ctrl+H"
        checkable: true
        checked: mpvObject.isUsingHwdec
        onTriggered: mpvObject.toggleHwdec()
    }
    property Action toggle60fpsAction: Action {
        text: "60fps"
        checkable: true
        checked: config.do60fps
        onTriggered: {
            if (config.do60fps) {
                mpvObject.command(["vf", "clr", ""])
            } else {
                mpvObject.command(
                            ["vf", "set", "lavfi=\"fps=fps=60:round=down\""])
            }
            config.do60fps = !config.do60fps
        }
    }
    property Action contrastDownAction: Action {
        text: "Contrast Down"
        shortcut: "1"
        onTriggered: mpvObject.contrastDown()
    }
    property Action contrastUpAction: Action {
        text: "Contrast Up"
        shortcut: "2"
        onTriggered: mpvObject.contrastUp()
    }
    property Action brightnessDownAction: Action {
        text: "Brightness Down"
        shortcut: "3"
        onTriggered: mpvObject.brightnessDown()
    }
    property Action brightnessUpAction: Action {
        text: "Brightness Up"
        shortcut: "4"
        onTriggered: mpvObject.brightnessUp()
    }
    property Action gammaDownAction: Action {
        text: "Gamma Down"
        shortcut: "5"
        onTriggered: mpvObject.gammaDown()
    }
    property Action gammaUpAction: Action {
        text: "Gamma Up"
        shortcut: "6"
        onTriggered: mpvObject.gammaUp()
    }
    property Action saturationDownAction: Action {
        text: "Saturation Down"
        shortcut: "7"
        onTriggered: mpvObject.saturationDown()
    }
    property Action saturationUpAction: Action {
        text: "Saturation Up"
        shortcut: "8"
        onTriggered: mpvObject.saturationUp()
    }
    property Action nextVideoTrackAction: Action {
        text: "Next Video Track"
        shortcut: "Ctrl+V"
        onTriggered: mpvObject.nextVideoTrack()
    }

    //--- Audio
    property Action nextAudioTrackAction: Action {
        text: "Next Audio Track"
        shortcut: "Ctrl+A"
        onTriggered: mpvObject.nextAudioTrack()
    }

    //--- Audio > Volume
    property Action volumeMuteAction: Action {
        text: "Mute"
        shortcut: "M"
        checkable: true
        checked: mpvObject.muted
        onTriggered: mpvObject.toggleMute()
    }

    property Action volumeUpAction: Action {
        shortcut: "Up"
        onTriggered: mpvObject.volumeUp()
    }

    property Action volumeDownAction: Action {
        shortcut: "Down"
        onTriggered: mpvObject.volumeDown()
    }

    property Action volumeUpAction2: Action {
        text: "Volume Up"
        shortcut: "0"
        onTriggered: volumeUpAction.trigger()
    }

    property Action volumeDownAction2: Action {
        text: "Volume Down"
        shortcut: "9"
        onTriggered: volumeDownAction.trigger()
    }

    //--- Subtitle
    property Action nextSubTrackAction: Action {
        text: "Next Subtitle Track"
        shortcut: "C"
        onTriggered: mpvObject.nextSubTrack()
    }

    //--- Tools
    property Action toggleConsoleViewAction: Action {
        text: "Console"
        shortcut: "`"
        checkable: true
        checked: config.showConsole
        onTriggered: config.showConsole = !config.showConsole
    }

    property Action togglePlaybackInfoAction: Action {
        text: "Playback Information"
        shortcut: "Tab"
        checkable: true
        checked: config.showPlaybackInfo
        onTriggered: config.showPlaybackInfo = !config.showPlaybackInfo
    }

    property Action togglePlaybackInfoAction2: Action {
        text: "Playback Information"
        shortcut: "I"
        onTriggered: togglePlaybackInfoAction.trigger()
    }

    //--- Tools > Playlist
    // property Action togglePlaylistAction: Action {
    //     text: "Show / Hide"
    //     shortcut: "L"
    //     onTriggered: sidebar.togglePlaylist()
    // }

    //--- Window
    // property Action toggleFullscreenAction: Action {
    // 	text: "Toggle Fullscreen"
    // 	shortcut: "Alt+Enter"
    // 	checkable: true
    // 	checked: window.isFullscreen
    // 	onTriggered: window.toggleFullscreen()
    // }
    // property Action toggleFullscreenAction2: Action { shortcut: "F"; onTriggered: toggleFullscreenAction.trigger() }
}

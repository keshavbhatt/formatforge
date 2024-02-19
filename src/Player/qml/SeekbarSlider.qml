import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import mpvz 1.0

// Fork Slider so that mouseArea is exposed because using a child MouseArea conflicts.
// https://github.com/qt/qtquickcontrols/blob/dev/src/controls/Slider.qml
AppSlider {
	id: slider

	property bool ignoreValueChange: false
	property bool playingOnPressed: false

	Connections {
		target: mpvObject
        function onFileLoaded() {
			slider.ignoreValueChange = true
			slider.value = 0
			slider.ignoreValueChange = false
		}
        function onPositionChanged() {
			// console.log('onPositionChanged', mpvObject.position, slider.value)
			if (mpvObject.duration > 0 && !slider.pressed && !seekDebounce.running) {
				slider.ignoreValueChange = true
				slider.value = mpvObject.position
				slider.ignoreValueChange = false
			}
		}
        function onDurationChanged() {
			slider.maximumValue = mpvObject.duration
		}
	}
	
	minimumValue: 0

	// https://github.com/qt/qtquickcontrols/blob/dev/src/controls/Private/qquickwheelarea_p.h
	WheelArea {
		id: wheelarea
		anchors.fill: parent
		horizontalMinimumValue: slider.minimumValue
		horizontalMaximumValue: slider.maximumValue
		verticalMinimumValue: slider.minimumValue
		verticalMaximumValue: slider.maximumValue

		onVerticalWheelMoved: {
			// console.log('onVerticalWheelMoved', verticalDelta)
			if (verticalDelta > 0) { // Scroll up
				slider.decrement()
			} else if (verticalDelta < 0) { // Scroll down
				slider.increment()
			}
		}

		onHorizontalWheelMoved: {
			// console.log('onHorizontalWheelMoved', horizontalDelta)
			if (horizontalDelta > 0) { // Scroll ?
				slider.decrement()
			} else if (horizontalDelta < 0) { // Scroll ?
				slider.increment()
			}
		}
	}

	mouseArea.hoverEnabled: true

	property int visibleSliderHeight: 4
	property int topPadding: 8
	property int bottomPadding: 8
	property int handleSize: 16
	implicitHeight: topPadding + visibleSliderHeight + bottomPadding // 20

	style: AppSliderStyle {
		groove: Item {
			implicitWidth: 200
			implicitHeight: control.height

			// [invisibleSliderHeight area that can be pressed]
			
			Rectangle {
				id: grooveRect
				anchors.bottom: parent.bottom
				anchors.bottomMargin: control.bottomPadding
				width: parent.width
				height: control.visibleSliderHeight

				radius: height

				layer.enabled: true
				layer.effect: OpacityMask {
					maskSource: Rectangle {
						x: grooveRect.x
						y: grooveRect.y
						width: grooveRect.width
						height: grooveRect.height
						radius: grooveRect.radius
					}
				}

				color: "#33FFFFFF"

				Item {
					id: cacheRectContainer
					anchors.fill: parent
					property var cachedRanges: []
					function updateCachedRanges() {
						var ranges = mpvObject.demuxerCacheState["seekable-ranges"]
						// console.log('seekable-ranges', ranges)
						if (ranges) {
							// for (var i = 0; i < ranges.length; i++) {
							// 	var map = ranges[i]
							// 	console.log('seekable-ranges', '    ', i, map, map['start'], map['end'])
							// }
							cacheRectContainer.cachedRanges = ranges
						} else {
							cacheRectContainer.cachedRanges = []
						}
					}

					Repeater {
						// model: mpvObject.demuxerCacheState["seekable-ranges"] || []
						model: cacheRectContainer.cachedRanges
						Rectangle {
							readonly property double startPos: modelData.start
							readonly property double endPos: modelData.end
							readonly property double startRatio: slider.maximumValue ? startPos / slider.maximumValue : 0
							readonly property double endRatio: slider.maximumValue ? endPos / slider.maximumValue : 0
							x: control.width * startRatio
							y: 0
							width: control.width * (endRatio - startRatio)
							height: grooveRect.height
							color: "#55FFFFFF"
						}
					}

					// The demuxerCacheStateChanged signal does not fire, so we watch
					// demuxerCacheDuration for changes instead.
					Connections {
						target: mpvObject
                        function onDemuxerCacheDurationChanged() {
							cacheRectContainer.updateCachedRanges()
						}
					}
				}

				Rectangle {
					width: styleData.handlePosition
					height: parent.height
                    color: "#ec810c"
                    //color: "#3DAEE6"
				}
			}

			Item {
				id: chapterMarkers
				anchors.fill: grooveRect

				Repeater {
					model: mpvObject.chapterListCount

					Image {
						readonly property double chapterPosition: mpvObject.getChapterTime(index)
						readonly property double positionRatio: slider.maximumValue ? chapterPosition / slider.maximumValue : 0
						x: control.width * positionRatio - width/2
						y: chapterMarkers.height/2
						width: 8
						height: 8
						source: "qrc:icons/Tethys/marker.png"
					}
				}
			}
		}

		handle: Item {
			height: parent.height

			Rectangle {
				anchors.centerIn: parent
				property int size: slider.mouseArea.containsMouse ? control.handleSize : 0
				width: size
				height: size
				radius: control.handleSize
				Behavior on size {
					NumberAnimation { duration: 400 }
				}
			}
		}
	}


	onPressedChanged: {
		if (pressed) {
			playingOnPressed = !mpvObject.paused
			// mpvObject.pause()
		}
		seekToValue()
		if (!pressed && playingOnPressed) {
			mpvObject.play()
		}
	}

	onValueChanged: {
		if (!ignoreValueChange) {
			seekDebounce.restart()
		}
	}

	Timer {
		id: seekDebounce
		interval: 100
		running: slider.pressed
		onTriggered: {
			seekToValue()
			if (slider.pressed) {
				restart()
			}
		}
	}

	function seekToValue() {
		mpvObject.seek(slider.value)
	}

	property real incrementSize: 5 // 5 seconds
	function decrement() {
		var nextValue = slider.value - incrementSize
		nextValue = Math.max(0, Math.min(nextValue, maximumValue))
		mpvObject.seek(nextValue)
	}
	function increment() {
		var nextValue = slider.value + incrementSize
		nextValue = Math.max(0, Math.min(nextValue, maximumValue))
		mpvObject.seek(nextValue)
	}
}

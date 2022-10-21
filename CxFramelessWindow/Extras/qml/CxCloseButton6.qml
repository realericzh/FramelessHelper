import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

AbstractButton {
    id: control

    width: 45
    height: 26

    property bool dark: false

    contentItem: Item {
        Image {
            id: icon
            anchors {
                centerIn: parent
            }

            width: 10
            height: 10

            visible: false

            fillMode: Image.PreserveAspectFit
            source: "qrc:/CxQuickFramelessWindow/Extras/res/close-button.svg"
        }

        ColorOverlay {
            id: overLay
            anchors {
                fill: icon
            }

            source: icon
            cached: true
            color: control.dark ? "#ffffff" : (control.down || control.hovered) ? "#ffffff" : "#000000"
            opacity: Window.active ? 1.0 : 0.5
        }
    }

    background: Rectangle {
        color: control.down ? "#8c0a15" : control.hovered ? "#e81123" : "transparent"
    }

    ToolTip.visible: control.hovered && !control.down
    ToolTip.delay: Qt.styleHints.mousePressAndHoldInterval
    ToolTip.text: qsTr("Close")
}



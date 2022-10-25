import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

AbstractButton {
    id: control

    width: 45
    height: 26

    property bool dark: false
    property real radius: 0.0

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

    background: Item {
        visible: control.down || control.hovered

        Item {
            id: backgroundItem
            anchors {
                fill: parent
            }
            visible: false

            Rectangle {
                width: backgroundItem.width - control.radius
                height: backgroundItem.height
                color: "#ff0000"
            }

            Rectangle {
                x: backgroundItem.width - control.radius
                y: control.radius
                width: control.radius
                height: backgroundItem.height - control.radius
                color: "#ff0000"
            }

            Rectangle {
                x: backgroundItem.width - control.radius * 2
                width: control.radius * 2
                height: width
                radius: control.radius
                color: "#ff0000"
            }
        }

        ColorOverlay {
            anchors {
                fill: parent
            }

            source: backgroundItem
            color: control.down ? "#8c0a15" : "#e81123"
        }
    }
}



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
            source: "qrc:/CxQuickFramelessWindow/Extras/res/minimize-button.svg"
        }

        ColorOverlay {
            id: overLay
            anchors {
                fill: icon
            }

            source: icon
            cached: true
            color: control.dark ? "#ffffff" : "#000000"
            opacity: Window.active ? 1.0 : 0.5
        }
    }

    background: Rectangle {
        visible: control.down || control.hovered
        color: control.dark ? "#ffffff" : "#000000"
        opacity: control.down ? 0.2 : control.hovered ? 0.1 : 0.0
    }
}

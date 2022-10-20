import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0

Button {
    id: control

    width: 45
    height: 26

    property string color: "black"
    property string colorHoverd: "white"
    property string colorPressed: "white"
    property string colorInactive: "#969696"

    property string bgcolorPressed: "#8c0a15"
    property string bgcolorHoverd: "#e81123"
    property string bgcolor: "transparent"

    property bool changeColor: true
    property bool active: changeColor ? Window.active : true

    contentItem: Item {
        Image {
            id: img
            width : 10
            height: 10
            visible: false
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            source: "qrc:/res/close-button1.svg"
        }

        ColorOverlay {
            id: overLay
            anchors.fill: img
            source: img
            cached: true
            color: (control.down || control.hovered) ? control.colorHoverd:
                                                       (control.active? control.color: control.colorInactive)
        }
    }

    background: Item {
        visible: control.down || control.hovered

        Rectangle {
            id: radiusRect
            width: 4
            height: 4
            radius: 2
            x: parent.width - 4

            color: control.down ? control.bgcolorPressed : (control.hovered ? control.bgcolorHoverd : control.bgcolor)
        }

        Rectangle {
            width: parent.width - radiusRect.width / 2
            height: parent.height
            color: radiusRect.color
        }

        Rectangle {
            width: radiusRect.width / 2
            height: parent.height - radiusRect.height / 2
            x: parent.width - radiusRect.width / 2
            y: radiusRect.height / 2
            color: radiusRect.color
        }
    }

    ToolTip.visible: hovered && !down
    ToolTip.delay: Qt.styleHints.mousePressAndHoldInterval
    ToolTip.text: qsTr("Close")
}



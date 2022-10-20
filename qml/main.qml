import QtQuick 2.9
import QtQuick.Window 2.2
import QtShark.Window 1.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12

Window {
    id: window
    visible: true
    width: 400
    height: 300
    title: qsTr("Qt Quick Inside")

    flags: Qt.Window | Qt.FramelessWindowHint

    color: "transparent"

    FramelessHelper {
        id: framelessHelper

        titleBarHeight: 60

        Component.onCompleted: {
            addExcludeItem(background)
            addExcludeItem(backgroundMask)
            addExcludeItem(backgroundOpacity)
            addExcludeItem(controls)
            addIncludeItem(titleBar)
        }
    }

    Image {
        id: background
        anchors.fill: parent
        anchors.margins: 1
        source: "qrc:/res/background.png"
        visible: false
    }

    Rectangle {
        id: backgroundMask
        anchors.fill: parent
        anchors.margins: 1
        color: "#ffffff"
        visible: false
    }

    OpacityMask {
        id: backgroundOpacity
        anchors.fill: background
        source: background
        maskSource: backgroundMask
    }

    Text {
        id: txt

        anchors {
            centerIn: parent
        }

        text: "Qt Quick Inside"
        font {
            family: "Arial"
            pointSize: 28
        }
        color: "#fefefe"

    }

    Row {
        id: colorPicker
        anchors {
            top: txt.bottom
            topMargin: 20
        }

        width: parent.width

        Slider {
            id: sr
            from: 0
            to: 1
            value: 0
            width: (parent.width - 20) / 3
        }
        Slider {
            id: sg
            from: 0
            to: 1
            value: 0
            width: (parent.width - 20) / 3
        }
        Slider {
            id: sb
            from: 0
            to: 1
            value: 0
            width: (parent.width - 20) / 3
        }
    }

    CustomTitleBar {
        id: titleBar
    }

    WindowBorder {
        // foregroundColor: Qt.rgba(sr.value, sg.value, sb.value, 1)
    }

    ThreeButtons {
        id: controls
        helper: framelessHelper
        color: Qt.rgba(sr.value, sg.value, sb.value, 1)
    }

    Component.onCompleted: {
        window.x = (Screen.width / 2) - 410;
    }
}

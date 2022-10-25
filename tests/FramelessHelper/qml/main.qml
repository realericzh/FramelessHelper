import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

import CxQuick.Window 1.0

Window {
    id: window

    width: 400
    height: 300

    visible: true

    title: qsTr("Qt Quick Inside")

    flags: Qt.Window | Qt.FramelessWindowHint

    color: "transparent"

    CxFramelessHelper {
        id: framelessHelper

        titleBarHeight: titleBar.height

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
        source: "qrc:/tests/res/background.png"
        visible: false
    }

    Rectangle {
        id: backgroundMask
        anchors.fill: parent
        color: "#ffffff"
        visible: false
        radius: 4
    }

    OpacityMask {
        id: backgroundOpacity
        anchors.fill: background
        source: background
        maskSource: backgroundMask
    }

    Text {
        anchors {
            centerIn: parent
        }

        text: "Qt Quick Inside"
        font {
            family: "Arial"
            pointSize: 28
        }
    }

    Item {
        id: titleBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        height: 28

        Row {
            id: controls

            anchors {
                top: parent.top
                right: parent.right
            }

            CxMinimizeButton {
                onClicked: { framelessHelper.triggerMinimizeButtonAction() }
            }

            CxMaximizeButton {
                onClicked: { framelessHelper.triggerMaximizeButtonAction() }
            }

            CxCloseButton {
                onClicked: { framelessHelper.triggerCloseButtonAction() }

                radius: 3
            }

            Component.onCompleted: {
                console.log("Warning: controls is not the last element!")
                console.log("Warning: controls 不是最后的一个元素, 小心它可能会被别的东西（比如图片）遮住而无法操作")
            }
        }
    }

    Component.onCompleted: {
        window.x = (Screen.width / 2) - 410;
    }
}

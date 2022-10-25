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

    CxFramelessHelper {
        id: framelessHelper

        titleBarHeight: titleBar.height

        Component.onCompleted: {
            addExcludeItem(controls)
            addIncludeItem(titleBar)
        }

        topDraggableMargin: 8
        leftDraggableMargin: 8
        rightDraggableMargin: 8
        bottomDraggableMargin: 8

        topMaximizedMargin: 5
        leftMaximizedMargin: 5
        rightMaximizedMargin: 5
        bottomMaximizedMargin: 5
    }

    Rectangle {
        anchors {
            fill: parent
        }

        color: "transparent"
        border {
            color: "#ff0000"
            width: 5
        }

        Rectangle {
            anchors {
                fill: parent
                margins: 5
            }

            color: "transparent"
            border {
                color: "#00ff00"
            }
        }

        Rectangle {
            anchors {
                fill: parent
                margins: 6
            }

            color: "transparent"
            border {
                color: "#0000ff"
            }
        }

        Rectangle {
            anchors {
                fill: parent
                margins: 7
            }

            color: "transparent"
            border {
                color: "#ff0000"
            }
        }
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
                topMargin: 1
                rightMargin: 1
            }

            CxMinimizeButton {
                onClicked: { framelessHelper.triggerMinimizeButtonAction() }
            }

            CxMaximizeButton {
                onClicked: { framelessHelper.triggerMaximizeButtonAction() }
            }

            CxCloseButton {
                onClicked: { framelessHelper.triggerCloseButtonAction() }
            }

            Component.onCompleted: {
                console.log("Warning: controls is not the last element!")
                console.log("Warning: controls 不是最后的一个元素, 小心它可能会被别的东西（比如图片）遮住而无法操作")
            }
        }
    }
}

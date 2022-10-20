import QtQuick 2.0
import QtQuick.Window 2.3

Rectangle {
    id: control

    anchors.fill: parent

    property string foregroundColor: "#000000"
    property string backgroundColor: "#000000"

    property bool changeColor: true
    property bool active: changeColor?Window.active: true

    border.width: 1
    color: "transparent"
    border.color: active ? foregroundColor : backgroundColor

    radius: 3
}

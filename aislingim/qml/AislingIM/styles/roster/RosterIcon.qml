import QtQuick 2.0

Rectangle {
    id: iconImage

    property string source

    anchors.top: parent.top
    anchors.topMargin: 6
    anchors.left: parent.left
    anchors.leftMargin: 6
    color: "transparent"

    width: 24
    height: 24

    Image {
        anchors.fill: parent
        source: parent.source
    }
}

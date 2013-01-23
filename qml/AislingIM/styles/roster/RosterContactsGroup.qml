import QtQuick 2.0

// The delegate for each section header
Rectangle {
    id: rosterGroup
    width: parent.width
    height: 32
    color: "transparent"

    Text {
        anchors.fill: parent
        anchors.leftMargin: 8

        verticalAlignment: Text.AlignVCenter
        renderType: Text.NativeRendering

        text: section
        font.bold: true
    }
}

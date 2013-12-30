import QtQuick 2.0

Rectangle {
    id: headerButton

    // props
    property string caption
    property int offset

    // behavior
    signal clicked

    anchors {
        top: parent.top
        bottom: parent.bottom
    }
    border.color: "#ccc"
    border.width: 1

    state: "normal"

    Text {
        anchors.fill: parent
        anchors.margins: 4
        anchors.leftMargin: offset
        verticalAlignment: Text.AlignVCenter

        text: headerButton.caption
        renderType: Text.NativeRendering
        font.pixelSize: 12
        font.bold: true
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true         //this line will enable mouseArea.containsMouse
        onClicked: headerButton.clicked()
    }

    states: [
        State {
            name: "normal"

            PropertyChanges { target: headerButton; color: "transparent" }
        },

        State {
            name: "hover"
            when: !mouseArea.pressed && mouseArea.containsMouse

            PropertyChanges { target: headerButton; color: "#f4f5f5" }
        },

        State {
            name: "clicked"
            when: mouseArea.pressed

            PropertyChanges { target: headerButton; color: "#e9ebeb" }
        }
    ]
}

import QtQuick 2.0

Rectangle {
    id: roundedButton

    property string caption
    property string icon

    property string color_normal: "#7fba00"
    property string color_hover: "#72a700"
    property string color_pressed: "#669500"
    property string color_text: "#fff"

    property int offset: 16

    signal clicked

    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
        margins: 8
    }

    color: color_normal
    radius: 20
    smooth: true
    width: textBox.width + offset + 16

    state: "normal"

    Rectangle {
        anchors.fill: parent
        anchors.leftMargin: offset
        color: "transparent"

        Text {
            id: textBox

            anchors {
                top: parent.top
                bottom: parent.bottom
            }
            verticalAlignment: Text.AlignVCenter

            color: color_text
            text: caption
            font.bold: true
            font.pixelSize: 12
            renderType: Text.NativeRendering
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true         //this line will enable mouseArea.containsMouse
        onClicked: roundedButton.clicked()
    }

    states: [
        State {
            name: "normal"

            PropertyChanges { target: roundedButton; color: color_normal }
        },

        State {
            name: "hover"
            when: !mouseArea.pressed && mouseArea.containsMouse

            PropertyChanges { target: roundedButton; color: color_hover }
        },

        State {
            name: "clicked"
            when: mouseArea.pressed

            PropertyChanges { target: roundedButton; color: color_pressed }
        }
    ]
}

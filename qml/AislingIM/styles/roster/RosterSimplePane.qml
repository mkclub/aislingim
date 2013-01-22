import QtQuick 2.0

Rectangle {
    id: pane_shape

    property string caption
    property string icon

    // alignment
    anchors.left: parent.left
    anchors.right: parent.right
    height: 36

    // color and shape
    border.color: "#ddd"
    border.width: 1
    color: "#e7f1f5"

    // behavior
    state: "normal"
    signal clicked


    RosterIcon {
        id: iconImage
        source: icon
    }

    Text {
        id: buttonCaption

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.left
        anchors.left: iconImage.right
        anchors.leftMargin: 10

        verticalAlignment: Text.AlignVCenter
        renderType: Text.NativeRendering
        font.pixelSize: 12
        font.bold: true

        text: caption
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true         //this line will enable mouseArea.containsMouse
        onClicked: pane_shape.clicked()
    }

//    ColorAnimation on border.color { to: "#bbb"; duration: 1000 }
    ColorAnimation on border.color { to: "#ddd"; duration: 1000 }

    states: [
        State {
             name: "normal"

             // setting gradient as "Gradient {...}" is not supported yet, so using hack proposed by Qt devs
             PropertyChanges { target: pane_shape; color: "#e7f1f5" }
             PropertyChanges { target: pane_shape; border.color: "#ddd" }
        },
        State {
             name: "hover"
             when: !mouseArea.pressed && mouseArea.containsMouse

             PropertyChanges { target: pane_shape; color: "#e7f1f5" }
             PropertyChanges { target: pane_shape; border.color: "#bbb" }
        },
        State {
             name: "pressed"
             when: mouseArea.pressed

             PropertyChanges { target: pane_shape; color: "#0095cc" }
             PropertyChanges { target: pane_shape; border.color: "#bbb" }
        }
    ]
}

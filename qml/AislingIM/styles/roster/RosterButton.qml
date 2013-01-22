import QtQuick 2.0

Rectangle {
    id: button_shape

    property string caption
    property string icon

    // behavior
    signal clicked
    state: "normal"

    // color and shape
    border.color: "#ddd"
    border.width: 1
    color: "#fff"

    anchors.top: parent.top
    width: parent.width / 2

    height: 36

    RosterIcon {
        id: iconImage
        source: icon
    }

    Text {
        id: buttonCaption

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: iconImage.right
        anchors.leftMargin: 10

        verticalAlignment: Text.AlignVCenter
        renderType: Text.NativeRendering

        text: caption
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true         //this line will enable mouseArea.containsMouse
        onClicked: button_shape.clicked()
    }

    states: [
        State {
             name: "normal"

             PropertyChanges { target: buttonCaption; color: "#000" }
        },
        State {
             name: "active"
             when: mouseArea.containsMouse

             PropertyChanges { target: buttonCaption; color: "#0099CC" }
        }
    ]

}

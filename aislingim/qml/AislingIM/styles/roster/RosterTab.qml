import QtQuick 2.0

Rectangle {
    id: tab_shape

    property string caption
    property string icon
    property bool active: false

    // behavior
    signal clicked

    // color and shape
    border.color: "#ddd"
    border.width: 1
    color: "#e7f1f5"

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
        font.pixelSize: 12
        font.bold: true

        text: caption
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true         //this line will enable mouseArea.containsMouse
        onClicked: tab_shape.clicked()
    }

    states: [
        State {
             name: "normal"

             // setting gradient as "Gradient {...}" is not supported yet, so using hack proposed by Qt devs
             PropertyChanges { target: tab_shape; color: "#e7f1f5" }
             PropertyChanges { target: tab_shape; border.color: "#ddd" }
        },
        State {
             name: "active"
             when: mouseArea.pressed || active

             PropertyChanges { target: tab_shape; color: "transparent" }
             PropertyChanges { target: tab_shape; border.color: "transparent" }
        }
    ]

}

import QtQuick 2.0

Rectangle {
    width: 300
    height: 600

    Rectangle {
        id: userTab

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 40

        border.color: "#ccc"
        border.width: 1
        color: "#e7f1f5"

        Rectangle {
            id: userStatusIcon

            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8

            width: 24
            height: 24
        }

        Text {
            id: userName

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: userStatusIcon.right
            anchors.leftMargin: 10
            anchors.right: userAvatar.left

            verticalAlignment: Text.AlignVCenter

            text: "graywolf"
            font.bold: true
        }

        Rectangle {
            id: userAvatar

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            width: 40

            color: "#666"
        }
    }

    Rectangle {
        id: serverTab

        anchors.top: userTab.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 4

        height: 40

        border.color: "#ccc"
        border.width: 1
        color: "#e7f1f5"

        Rectangle {
            id: serverIcon

            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8

            width: 24
            height: 24
        }

        Text {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            verticalAlignment: Text.AlignVCenter
            anchors.left: serverIcon.right
            anchors.leftMargin: 10

            text: "jabber.kiev.ua"
            font.bold: true
        }
    }
}

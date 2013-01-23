import QtQuick 2.0

// The delegate for each section header
Rectangle {
    id: rosterItem
    anchors.left: parent.left
    anchors.leftMargin: 4

    width: ListView.view.width
    height: 40

    color: ListView.isCurrentItem ? "#0095cc" : "transparent"
    property string textColor: ListView.isCurrentItem ? "white" : "black"
    property string textColor2: ListView.isCurrentItem ? "white" : "#bbb"

    MouseArea {
         id: mouseArea
         hoverEnabled: false
         anchors.fill: parent
         onClicked: rosterItem.ListView.view.currentIndex = index
    }

    Rectangle {
        id: rosterAvatar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 4

        width: 32
        border.width: 1
        border.color: "#ddd"

        Image {
            anchors.fill: parent
            anchors.margins: 1
            source: "../../images/logos/jabber-4.png"
        }
    }

    ConnectionState {
        id: rosterStatus

        anchors.top: parent.top
        anchors.left: rosterAvatar.right
        anchors.margins: 3

        height: 24
        width: 24
        state: online;
    }

    Rectangle {
        anchors.left: rosterStatus.right
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 8
        color: "transparent"

        Column {
            Text { text: contact; color: textColor; font.pixelSize: 11; renderType: Text.NativeRendering }
            Text { text: status; color: textColor2; renderType: Text.NativeRendering }
        }
    }
}

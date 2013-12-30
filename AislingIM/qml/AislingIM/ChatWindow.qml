import QtQuick 2.0

import "styles/chat"

Rectangle {
    width: 800
    height: 600

    anchors.margins: 4

    UserInfoPanel {
        id: userInfoPanel
        anchors.top: parent.top
        width: parent.width
    }

    ChatPanel {
        id: chatScreen
        anchors {
            top: userInfoPanel.bottom
            topMargin: 4
            bottom: parent.bottom
        }
        width: parent.width

    }
}

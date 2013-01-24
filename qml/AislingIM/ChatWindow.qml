import QtQuick 2.0

import "styles/chat"

Rectangle {
    width: 400
    height: 600

    anchors.margins: 4

    Rectangle {
        id: userPane;

        anchors.top: parent.top
        width: parent.width
        height: 140

        border.color: "#ccc"
        border.width: 1

        Rectangle {
            id: userNamePane
            anchors.top: parent.top
            width: parent.width
            height: 32

            border.color: "#bbb"
            border.width: 1

            color: "transparent"

            Text {
                anchors.fill: parent
                anchors.margins: 4
                verticalAlignment: Text.AlignVCenter

                text: "Sergii Gulenok"
                font.bold: true
            }

            Rectangle {
                id: closeButton
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                }
                width: 100
                border.color: "#ccc"
                border.width: 1

                Text {
                    anchors.fill: parent
                    anchors.margins: 4
                    verticalAlignment: Text.AlignVCenter

                    text: "Close"
                    font.bold: true
                }
            }

        }

        Rectangle {
            id: userInfoPane

            anchors {
                top: userNamePane.bottom
                bottom: parent.bottom
            }
            width: parent.width
            color: "transparent"

            Rectangle {
                id: userAvatar

                anchors {
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                }

                width: 110
                color: "transparent"

                Image {
                    anchors.centerIn: parent
                    source: "images/stubs/samurai-av-150.jpg"

                    width: 96
                    height: 96
                }
            }

            Rectangle {
                id: userDetails
            }
        }
    }


    Rectangle {
        id: chatScreen

        anchors {
            top: userPane.bottom
            topMargin: 4
            bottom: parent.bottom
        }
        width: parent.width

        border.color: "#ccc"
        border.width: 1

        Rectangle {
            id: actionsPane

            anchors {
                top: parent.top
            }
            border.color: "#ccc"
            border.width: 1

            width: parent.width
            height: 42

            color: "transparent"

            Rectangle {
                id: buttonVideoCall

                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    margins: 8
                }

                width: 100
                radius: 20
                color: "lime"

                Text {
                    anchors.centerIn: parent

                    color: "#fff"
                    text: "Video call"
                    font.bold: true
                }
            }

            Rectangle {
                id: buttonAudioCall

                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: buttonVideoCall.right
                    margins: 8
                }

                width: 100
                radius: 20
                color: "lime"

                Text {
                    anchors.centerIn: parent

                    color: "#fff"
                    text: "Audio call"
                    font.bold: true
                }
            }
        }

        ChatMessageList {
            anchors {
                top: actionsPane.bottom
                bottom: messagePane.top
            }

            width: parent.width
        }

        Rectangle {
            id: messagePane
            anchors.bottom: parent.bottom
            width: parent.width
            height: 32
        }
    }
}

import QtQuick 2.0

import "styles/chat"
import "models"

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
            id: chatMessageList
            anchors {
                top: actionsPane.bottom
                bottom: messagePane.top
            }

            width: parent.width
            messageModel: MessageListModel {}
        }

        Rectangle {
            id: messagePane
            anchors.bottom: parent.bottom
            width: parent.width
            height: 56


            function sendMessage() {
                if (chatMessageEdit.text.toString() != "") {
                    var isLast = chatMessageList.isLast()
                    chatMessageList.messageModel.append({
                                            sender: "Sergii Gulenok",
                                            message: chatMessageEdit.text,
                                            time: (new Date()).toLocaleTimeString()
                                        })
                    chatMessageEdit.text = ""
                    chatMessageList.update(isLast)
                }
            }

            Rectangle {
                id: chatMessageEditHolder
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    margins: 4
                    leftMargin: (parent.width - width) / 2
                }

                width:
                    if (parent.width > 600 ) parent.width - 200
                    else parent.width - 128

                border.width: 1
                border.color: "#ccc"

                TextEdit {
                    id: chatMessageEdit
                    anchors.fill: parent
                    anchors.margins: 4

                    textFormat: TextEdit.AutoText
                    renderType: Text.NativeRendering
                    wrapMode: TextEdit.WordWrap
                    selectByMouse: true

                    Keys.onReturnPressed:
                        if (event.modifiers & (Qt.ShiftModifier | Qt.AltModifier | Qt.ControlModifier))
                            event.accepted = false
                        else
                            messagePane.sendMessage()
                }
            }

            Rectangle {
                anchors.left: chatMessageEditHolder.right
                anchors.top: parent.top
                anchors.margins: 4
                width: 48
                height: 24
                color: "transparent"

                border.width: 1
                border.color: "#ccc"
                radius: 12

                Text {
                    anchors.centerIn: parent
                    text: "Send"
                    renderType: Text.NativeRendering
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: messagePane.sendMessage()
                }
            }
        }
    }
}

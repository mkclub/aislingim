import QtQuick 2.0

import "../../models"

Rectangle {
    id: chatPanel

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
        height: 44

        color: "transparent"

        RoundedButton {
            id: buttonVideoCall
            caption: "Video call"
            offset: 32

            anchors {
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                margins: 8
            }


            ButtonIcon {
                width: 28
                size: 16
                source: "../../images/video.png"
            }
        }

        RoundedButton {
            id: buttonAudioCall
            caption: "Audio call"
            offset: 32

            anchors {
                top: parent.top
                bottom: parent.bottom
                left: buttonVideoCall.right
                margins: 8
            }

            ButtonIcon {
                width: 28
                size: 16
                source: "../../images/speak.png"
            }
        }

        RoundedButton {
            id: buttonShare
            caption: "Share"
            offset: 32

            anchors {
                top: parent.top
                bottom: parent.bottom
                left: buttonAudioCall.right
                margins: 8
            }

            ButtonIcon {
                width: 28
                size: 16
                source: "../../images/up.png"
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
            var message = chatMessageEdit.text.toString();
            if (message != "") {
                message = message.replace(/\n/g, "<br>")
                var isLast = chatMessageList.isLast()
                chatMessageList.messageModel.append({
                                        sender: "Sergii Gulenok",
                                        message: message,
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
                if (parent.width > 600 ) parent.width - 188
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
            anchors {
                left: chatMessageEditHolder.right
                top: parent.top
                right: parent.right
                leftMargin: 4
            }
            height: 36

            RoundedButton {
                id: buttonPostMessage
                caption: "Send"
                onClicked: messagePane.sendMessage()
                anchors.margins: 4

                color_normal: "white"
                color_hover: "#eee"
                color_pressed: "#ddd"
                color_text: "#888"

                border.width: 1
                border.color: "#ccc"
            }
        }
    }
}

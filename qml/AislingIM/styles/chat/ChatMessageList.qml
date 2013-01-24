import QtQuick 2.0
import QtDesktop 1.0

import "../../components"

Rectangle {
    property string displayText: "<table width='100%'></table>"

    id: chatMessageList
    property variant rosterModel

    ScrollArea {
        id: scrollArea
        frame: false
        anchors.fill: parent

        TextEdit {
            id: chatMessageListView
            width: chatMessageList.width - 20

            text: displayText
            textFormat: TextEdit.RichText
            renderType: Text.NativeRendering
            readOnly: true
            wrapMode: TextEdit.WordWrap
            selectByMouse: true
        }
    }

    Rectangle {
        anchors {
            top: parent.top
            right: parent.right
        }

        width: 20
        height: 20

        color: "gray"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var dt = new Date()
                chatMessageListView.text += "<tr width='100%'>
        <td align='right' style='padding: 5px; color: #aaa;'>Sergii Gulenok</td>
        <td style='padding: 5px'> text <a href='http://google.com/'>test</a></td>
        <td style='padding: 5px; color: #aaa;'>" + dt.toLocaleTimeString() + "</td></tr>"
                console.log(scrollArea.contentY)
                console.log(scrollArea.contentHeight)
                if (scrollArea.contentHeight > scrollArea.height)
                    scrollArea.contentY = scrollArea.contentHeight - scrollArea.height
                }
        }
    }
}

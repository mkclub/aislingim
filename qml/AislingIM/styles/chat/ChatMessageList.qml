import QtQuick 2.0
import QtDesktop 1.0

import "../../components"
import "../../models"

Rectangle {
    id: chatMessageList
    property variant messageModel

    ScrollArea {
        id: scrollArea
        frame: false
        anchors.fill: parent

        TextEdit {
            id: chatMessageListView
            width: chatMessageList.width - 20

            text: messageModel.toHtml()
            textFormat: TextEdit.RichText
            renderType: Text.NativeRendering
            readOnly: true
            wrapMode: TextEdit.WordWrap
            selectByMouse: true
        }
    }

    function update(needScroll) {
        if (scrollArea.contentHeight > scrollArea.height && needScroll)
            scrollArea.contentY = scrollArea.contentHeight - scrollArea.height
    }

    function isLast() {
        return scrollArea.contentY >= scrollArea.contentHeight - scrollArea.height
    }
}

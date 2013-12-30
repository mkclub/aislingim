import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

import "../../components"
import "../../models"

Rectangle {
    id: chatMessageList
    property variant messageModel

    ScrollView {
        id: scrollArea
//        frame: false
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
        console.log(scrollArea.contentY)
        console.log(scrollArea.contentHeight - scrollArea.height)
        return scrollArea.contentY >= scrollArea.contentHeight - scrollArea.height
    }
}

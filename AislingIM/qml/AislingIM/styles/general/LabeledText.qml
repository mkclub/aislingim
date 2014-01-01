import QtQuick 2.0
import QtQuick.Controls 1.0
//import QtQuick.Layouts 1.0

Rectangle {
    id: labeledText

    property string label
    property alias value: loginText.text

    //border.width: 1
    width: parent.width / 2
    height: 24

    Label {
        id: loginLabel
        anchors.top: parent.top
        anchors.right: loginText.left
        anchors.bottom: parent.bottom
        verticalAlignment: Text.AlignVCenter

        text: label
    }

    TextField {
        id: loginText

        anchors.fill: parent
        anchors.leftMargin: 100
    }
}

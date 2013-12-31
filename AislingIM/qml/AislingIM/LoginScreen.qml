import QtQuick 2.0
import QtQuick.Controls 1.0

import "styles/general"

Rectangle {
    id: loginScreen
    width: 600
    height: 200

    Grid {
        id: loginGrid
        anchors.fill: parent
        columns: 2
        rows: 3
        rowSpacing: 4.0

        flow: Grid.TopToBottom

        LabeledText {
            label: "Login: "
            value: "graywolf"
        }

        LabeledText {
            label: "Password: "
            value: "xxx"
        }

        LabeledText {
            label: "Resource: "
            value: "home"
        }

        LabeledText {
            label: "Server: "
            value: "jabber.kiev.ua"
        }

        Rectangle {
            width: parent.width / 2
            height: 24
        }

        Rectangle {
            width: parent.width / 2
            height: 24

            Button {
                anchors.right: parent.right
                text: "Connect"
            }

        }
    }
}

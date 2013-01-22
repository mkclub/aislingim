import QtQuick 2.0

Rectangle {
    id: rosterContactList
    property variant rosterModel

    // The delegate for each section header
    Component {
        id: rosterGroup

        Rectangle {
            width: container.width
            height: 32
            color: "transparent"

            Text {
                anchors.fill: parent
                anchors.leftMargin: 8

                verticalAlignment: Text.AlignVCenter
                renderType: Text.NativeRendering

                text: section
                font.bold: true
            }
        }
    }

    // The delegate for each section header
    Component {
        id: rosterItem

        Item {
            width: container.width
            height: 40

            Rectangle {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 4

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

                Rectangle {
                    anchors.left: rosterAvatar.right
                    anchors.leftMargin: 16
                    anchors.top: parent.top
                    anchors.topMargin: 8

                    Column {
                        Text { text: contact; font.pixelSize: 11; renderType: Text.NativeRendering }
                        Text { text: status; color: "#bbb"; renderType: Text.NativeRendering }
                    }
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 1
        model: rosterModel
        delegate: rosterItem

        section.property: "group"
        section.criteria: ViewSection.FullString
        section.delegate: rosterGroup

        boundsBehavior: Flickable.DragOverBounds
        focus: true
        clip: true
    }
}

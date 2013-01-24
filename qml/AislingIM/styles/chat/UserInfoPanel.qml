import QtQuick 2.0

Rectangle {
    id: userInfoPanel;

    property bool expanded: true
    property string contactName: "Sergii Gulenok"

    height: userInfoPane.height + userInfoTop.height

    border.color: "#ccc"
    border.width: 1

    Rectangle {
        id: userInfoTop
        anchors.top: parent.top
        width: parent.width
        height: 32
        color: "transparent"

        HeaderButton {
            id: userNamePane

            anchors.left: parent.left
            anchors.right: closeButton.left

            caption: contactName
            offset: 32

            onClicked: userInfoPanel.expanded = !userInfoPanel.expanded

            ToggleIcon {
                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 4
                }

                source: "../../images/star.png"
            }
        }

        HeaderButton {
            id: closeButton
            anchors.right: parent.right
            width: 100

            caption: "Close"
            offset: 32

            ToggleIcon {
                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 4
                }
                enabled: false
                on: true
                source: "../../images/cross.png"
            }
        }
    }


    Rectangle {
        id: userInfoPane

        anchors.top: userInfoTop.bottom
        width: parent.width
        height: 120
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
                source: "../../images/stubs/samurai-av-150.jpg"

                width: 96
                height: 96
            }
        }

        Rectangle {
            id: userDetails
        }
    }

    states: [
        State {
            name: "expanded"
            when: expanded
            PropertyChanges { target: userInfoPane; height: 120 }
        },

        State {
            name: "collapsed"
            when: !expanded
            PropertyChanges { target: userInfoPane; height: 0 }
            PropertyChanges { target: userInfoPane; opacity: 0 }
        }
    ]
}

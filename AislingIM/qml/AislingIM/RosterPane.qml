import QtQuick 2.1

import "styles/roster"
import "stubs"

Rectangle {
    id: roster
    width: 300
    height: 600

    RosterSimplePane {
        id: userTab
        anchors.top: parent.top

        caption: "graywolf"

        ConnectionState {
            anchors.top: parent.top
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 6

            width: 24
            height: 24

            state: "connecting"
        }

        Rectangle {
            id: userAvatar

            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1
            anchors.right: parent.right
            anchors.rightMargin: 1

            border.width: 1
            border.color: "silver"

            width: 36
            color: "transparent"

            Image {
                anchors.fill: parent
                anchors.margins: 1
                source: "images/stubs/samurai-av-150.jpg"
                fillMode: Image.PreserveAspectCrop
            }
        }
    }

    RosterSimplePane {
        id: serverTab

        anchors.top: userTab.bottom
        anchors.topMargin: 4

        caption: "jabber.kiev.ua"
        icon: "../../images/server.png"
    }

    Rectangle {
        id: rosterHolder

        anchors.top: serverTab.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4

        border.color: "#ddd"
        border.width: 1

        Rectangle {
            id: rosterSwitch

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            color: "transparent"

            height: 36

            RosterTab {
                id: contactsSwitch
                caption: "Contacts"
                icon: "../../images/person.png"
                active: true

                anchors.left: parent.left
            }

            RosterTab {
                id: recentSwitch
                caption: "Recent"
                icon: "../../images/chat.png"
                state: "normal"

                anchors.left: contactsSwitch.right
            }
        }

        Rectangle {
            id: searchPane;

            anchors.top: rosterSwitch.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 36
            color: "transparent"

            Rectangle {
                anchors.fill: parent
                anchors.margins: 6

                border.width: 1
                border.color: "#bbb"

                Rectangle {
                    id: searchIcon
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    color: "transparent"

                    width: 24

                    Image {
                        anchors.fill: parent
                        anchors.margins: 4
                        opacity: 0.5

                        source: "images/search.png"
                    }
                }

                TextInput {
                    id: searchInputBox

                    anchors.fill: parent
                    anchors.left: searchIcon.right
                    anchors.leftMargin: 30
                    anchors.topMargin: 5

                    color: "silver"
                    font.pixelSize: 11
                    renderType: Text.NativeRendering

                    text: "Search"
                }
            }
        }

        RosterContactsList {
            anchors.top: searchPane.bottom
            anchors.bottom: rosterActions.top
            anchors.bottomMargin: -1
            width: parent.width

            border.color: "#ddd"
            rosterModel: StubRoster {}
        }

        Rectangle {
            id: rosterActions

            anchors.bottom: parent.bottom
            width: parent.width
            height: 36

            RosterButton {
                id: addContact
                caption: "Add a Contact"
                icon: "../../images/add.png"

                anchors.left: parent.left
            }

            RosterButton {
                id: joinConference
                caption: "Join a Conference"
                icon: "../../images/chat2.png"

                anchors.left: addContact.right
            }
        }
    }
}

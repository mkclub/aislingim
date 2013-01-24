import QtQuick 2.0

import "../../components"

Rectangle {
    id: rosterContactList
    property variant rosterModel

    ListView {
        id: rosterContactListView
        anchors.margins: 1
        model: rosterModel
        delegate: RosterContactsItem {}
        clip: true
        focus: true

        section.property: "group"
        section.criteria: ViewSection.FullString
        section.delegate: RosterContactsGroup {}

        boundsBehavior: Flickable.DragOverBounds
    }

    ScrollBar {
        target: rosterContactListView
    }
}

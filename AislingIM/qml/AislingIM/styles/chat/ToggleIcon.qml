import QtQuick 2.0

Rectangle {
    id: toggleIcon

    property string source

    property bool on

    // Behavior
    signal doSwitch(bool on)

    width: 24
    height: 24

    color: "transparent"


    Image {
        id: icon
        anchors.fill: parent
        anchors.margins: 4
        source: toggleIcon.source

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: { on = !on; doSwitch(on); }
            enabled: toggleIcon.enabled
        }
    }

    states: [
        State {
            name: "on"
            when: on
            PropertyChanges { target: icon; opacity: 1 }
        },

        State {
            name: "off"
            when: !on
            PropertyChanges { target: icon; opacity: 0.2 }
        }
    ]
}

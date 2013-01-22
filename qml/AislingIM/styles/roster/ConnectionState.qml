import QtQuick 2.0

Rectangle {
    state: "online"
    color: "transparent"

    Image {
        id: statusImage
        anchors.fill: parent
        anchors.margins: (parent.width - 16) / 2

        width: 16
        height: 16
    }

    states: [
        State { name: "online"; PropertyChanges { target: statusImage; source: "images/status/online.png" } },
        State { name: "offline"; PropertyChanges { target: statusImage; source: "images/status/offline.png" } },
        State { name: "away"; PropertyChanges { target: statusImage; source: "images/status/away.png" } },
        State { name: "x-away"; PropertyChanges { target: statusImage; source: "images/status/x-away.png" } },
        State { name: "dnd"; PropertyChanges { target: statusImage; source: "images/status/dnd.png" } },
        State { name: "connecting"; PropertyChanges { target: statusImage; source: "images/status/connecting.png" } }
    ]
}

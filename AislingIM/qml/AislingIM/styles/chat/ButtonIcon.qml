import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: buttonIcon

    property int size: 24
    property string source
    property string iconColor: "#fff"

    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }

    color: "transparent"

    Image {
        id: image
        width: size
        height: size
        anchors.centerIn: parent
        source: buttonIcon.source
    }

    ColorOverlay {
        id: icon_shader;
        source: image;
        anchors.fill: image;
        color: iconColor
    }
}

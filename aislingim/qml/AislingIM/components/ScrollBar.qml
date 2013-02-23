import QtQuick 2.0

Rectangle {
    id: scrollBar
    property variant orientation: Qt.Vertical
    property variant target
    property int step: 20
    property int size: 16

    height: orientation === Qt.Vertical ? target.height : size
    width: orientation === Qt.Vertical ? size : target.width

    anchors.right: target.right
    anchors.bottom: target.bottom;

    border.color: "#afafaf"
    color: "#f0f0f0"
    smooth: true

    function isVerticalNeeded()
    {
        return track.height === slider.height;
    }

    function isHorizontalNeeded()
    {
        return track.width === slider.width;
    }

    states: [
        State { name: "nothing"; },
        State { name: "disabled"; when: orientation === Qt.Vertical ? isVerticalNeeded() : isHorizontalNeeded() }
    ]
    transitions: [
        Transition { to: "disabled";
            PropertyAction { target: scrollBar; property: "visible"; value: false; }
        },
        Transition { to: "*";
            PropertyAction { target: scrollBar; property: "visible"; value: true; }
        }
    ]

    Timer {
        property int scrollAmount

        id: timer
        repeat: true
        interval: 10
        onTriggered: {
            if(orientation === Qt.Vertical)
            {
                target.contentY = Math.max(0, Math.min(target.contentY + scrollAmount,
                                          target.contentHeight - target.height));
            }
            else
            {
                target.contentX = Math.max(0, Math.min(target.contentX + scrollAmount,
                                          target.contentWidth - target.width));
            }
        }
    }

     Rectangle{
        id: track
        anchors { fill: parent; } // topMargin: 2; bottomMargin: 2; leftMargin: 2; rightMargin: 2; }
        color: "transparent"

        MouseArea {
            anchors.fill: parent
            onPressed: {
                if(orientation === Qt.Vertical)
                {
                    timer.scrollAmount = target.height * (mouseY < slider.y ? -1 : 1) // scroll by a page
                }
                else
                {
                    timer.scrollAmount = target.width * (mouseX < slider.x ? -1 : 1) // scroll by a page
                }
                timer.running = true;
            }
            onReleased: {
                timer.running = false;
            }
        }

        Rectangle{
            id: slider
            border.color: "#afafaf"
            color: "#a6a6a6"
            smooth: true

            function calcWidth()
            {
                if (target.visibleArea.xPosition < 0)
                    return Math.max(30, Math.min(target.width / target.contentWidth * track.width, track.width - x) + target.width * target.visibleArea.xPosition)
                else
                    return Math.min(target.width / target.contentWidth * track.width, track.width - x);
            }

            function calcHeight()
            {
                if (target.visibleArea.yPosition < 0)
                    return Math.max(30, Math.min(target.height / target.contentHeight * track.height, track.height-y) +target.height * target.visibleArea.yPosition)
                else
                    return Math.min(target.height / target.contentHeight * track.height, track.height - y)
            }

            function calcY()
            {
                return Math.max(0,Math.min(track.height-30, target.visibleArea.yPosition * track.height));
            }

            function calcX()
            {
                return Math.max(0,Math.min(track.width-30, target.visibleArea.xPosition * track.width));
            }

            width: orientation === Qt.Vertical ? size : calcWidth()
            height: orientation === Qt.Vertical ? calcHeight() : size

            y: orientation === Qt.Vertical ? calcY() : 0
            x: orientation === Qt.Vertical ? 0 : calcX()

            MouseArea {
                anchors.fill: parent
                drag.target: parent
                drag.axis: orientation === Qt.Vertical ? Drag.YAxis : Drag.XAxis;
                drag.minimumY: 0
                drag.maximumY: orientation === Qt.Vertical ? track.height - height : 0
                drag.minimumX: 0
                drag.maximumX: orientation === Qt.Vertical ? 0 : track.width - width

                onPositionChanged: {
                    if (pressedButtons == Qt.LeftButton) {
                        if (orientation === Qt.Vertical)
                            target.contentY = slider.y * target.contentHeight / track.height
                        else
                            target.contentX = slider.x * target.contentWidth / track.width
                    }
                }
            }
        }
     }
 }

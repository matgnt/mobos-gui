import Qt 4.7
import "content"

Rectangle {
    id: container
    //anchors.fill: parent
    color: "#646464"
    width: parent.width
    height: parent.height

    signal clicked

    MouseArea {
        anchors.fill: parent
        onClicked: container.clicked()
    }

    Clock {
        city: "Linz"
        shift: +1
        anchors.centerIn: parent
    }

}

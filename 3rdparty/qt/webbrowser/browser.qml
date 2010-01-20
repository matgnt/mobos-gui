import Qt 4.6
import "."

Rectangle {
    width: 640
    height: 480
    property alias urlString: browserComponent.urlString


    webbrowser {
        id: browserComponent
        anchors.fill: parent
    }
}

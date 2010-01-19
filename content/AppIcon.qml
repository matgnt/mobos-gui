import Qt 4.6

Item {
    id: container

    signal clicked

    property string iconSource: ""
    property string text: ""
    property int textSize: 16
    property string smallText: ""
    property int smallTextSize: 10

    BorderImage {
        id: buttonImage
        opacity: 1
        source: iconSource
        width: container.width; height: container.height
    }
    Text {
        id: mainText
        text: container.text
        color: "#FFFFFF"
        anchors.centerIn: buttonImage; font.bold: true
        style: Text.Raised; styleColor: "black"
        font.pixelSize: textSize
    }
    Text {
        text: container.smallText
        color: "#FFFFFF"
        anchors.top: mainText.bottom ; font.bold: true
        anchors.horizontalCenter: mainText.horizontalCenter
        style: Text.Raised; styleColor: "black"
        font.pixelSize: smallTextSize
    }
    MouseRegion {
        id: mouseRegion
        anchors.fill: buttonImage
        onClicked: { container.clicked(); }
    }

    states: State {
                name: "Pressed"
                when: mouseRegion.pressed == true
                PropertyChanges { target: container; opacity: 0.8 }
            }
}

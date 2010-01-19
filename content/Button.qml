import Qt 4.6

Item {
    id: container

    signal clicked

    property string text
    property bool keyUsing: false

    BorderImage {
        id: buttonImage
        opacity: 1
        source: "images/toolbutton.sci"
        width: container.width; height: container.height
    }
    MouseRegion {
        id: mouseRegion
        anchors.fill: buttonImage
        onClicked: { container.clicked(); }
    }
    Text {
        id: btnText
        color: if(container.keyUsing){"#DDDDDD";} else {"#FFFFFF";}
        anchors.centerIn: buttonImage; font.bold: true
        text: container.text; style: Text.Raised; styleColor: "black"
        font.pixelSize: 12
    }
    states: [
        State {
            name: "Pressed"
            when: mouseRegion.pressed == true
            PropertyChanges { target: container; opacity: 0.8 }
        },
        State {
            name: "Focused"
            when: container.focus == true
            PropertyChanges { target: btnText; color: "#FFFFFF" }
        }
    ]
    transitions: Transition {
        ColorAnimation { target: btnText; }
    }
}

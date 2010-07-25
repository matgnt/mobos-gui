import Qt 4.7

Item {
    id: container
    width: 240
    height: 320
    //property string number: ""

    Text {
        id: txtNumber
        anchors.centerIn: parent
        color: "#FFFFFF"
        style: Text.Raised; styleColor: "black"
        font.pixelSize: 16
        text: "Dialing...";
    }

    Loading {
        anchors.top: txtNumber.bottom;
        anchors.horizontalCenter: txtNumber.horizontalCenter;
    }


}

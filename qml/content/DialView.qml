import Qt 4.6

Item {
    id: container
    //anchors.centerIn: parent
    width: 240
    height: 320
    property int iconKeyWidth: width / 3  // default values
    property int iconKeyHeight: height / 6 // change from outside

    signal back


    Rectangle {
        id: numberBlock
        color: "#C0C0C0"
        width: parent.width
        height: parent.height

        //anchors.top: numberField.bottom

        Column {
            spacing: 2
            anchors.centerIn: parent
            Item {
                id: numberField
                function appendText(str) {
                    txtNumber.text = txtNumber.text + str
                }
                function backSpace() {
                    txtNumber.text = txtNumber.text.slice(0,txtNumber.text.length - 1)
                }

                width: parent.width
                height: iconKeyHeight
                BorderImage {
                    source: "images/black_box_100.png"
                    anchors.fill: parent
                    height: iconKeyHeight
                }
                TextInput {
                    id: txtNumber
                    width: parent.width - 8
                    anchors.centerIn: parent
                    //anchors.fill: parent
                    font.pixelSize: 16;
                    font.bold: true
                    color: "white"
                    horizontalAlignment: TextInput.AlignRight
                }
            }

            Grid {
                columns: 3
                rows: 5
                spacing: 2
                //anchors.centerIn: numberBlock
                //anchors.top: numberField.bottom


                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key1
                    text: "1"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key2
                    text: "2"
                    smallText: "ABC"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key3
                    text: "3"
                    smallText: "DEF"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key4
                    text: "4"
                    smallText: "GHI"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key5
                    text: "5"
                    smallText: "JKL"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key6
                    text: "6"
                    smallText: "MNO"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key7
                    text: "7"
                    smallText: "PQRS"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key8
                    text: "8"
                    smallText: "TUV"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key9
                    text: "9"
                    smallText: "WXYZ"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: keyAsterisk
                    text: "*"
                    textSize: 24
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: key0
                    text: "0"
                    smallText: "+"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: keyHash
                    text: "#"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { numberField.appendText(text) }
                }

                AppIcon {
                    iconSource: "images/key_100.png"
                    id: keySaveToContacts
                    text: ""
                    width: iconKeyWidth
                    height: iconKeyHeight
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: keyCall
                    text: "Call"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: { Gsm.dial(txtNumber.text) }
                }
                AppIcon {
                    iconSource: "images/key_100.png"
                    id: keyBack
                    text: "<-"
                    width: iconKeyWidth
                    height: iconKeyHeight
                    onClicked: {numberField.backSpace() }
                }

            }
        }
    }
}

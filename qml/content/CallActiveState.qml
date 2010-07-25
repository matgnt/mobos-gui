import Qt 4.7
import "../ofonohelper.js" as Helper

Item {
    id: container
    width: 240
    height: 320
    property string callId: ""

    Connections {
        target: OfonoContext

        onActiveCall: {
            txtNumber.text = Helper.getCallerNumber(id);
            callId = id;
            console.log("CallActiveState onActiveCall" + id);
        }
    }

    Text {
        id: numberCaption
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height / 4
        text: "Number: "
        color: "#FFFFFF"
        style: Text.Raised; styleColor: "black"
        font.pixelSize: 16

    }

    Text {
        id: txtNumber
        anchors.top: numberCaption.bottom
        anchors.horizontalCenter: numberCaption.horizontalCenter
        color: "#FFFFFF"
        style: Text.Raised; styleColor: "black"
        font.pixelSize: 16

    }
    Text {
        id: activeCaption
        anchors.top: txtNumber.bottom
        anchors.horizontalCenter: txtNumber.horizontalCenter
        text: "Active since:"
        color: "#FFFFFF"
        style: Text.Raised; styleColor: "black"
        font.pixelSize: 16

    }

    Text {
        id: txtActiveSince
        anchors.top: activeCaption.bottom
        anchors.horizontalCenter: activeCaption.horizontalCenter
        color: "#FFFFFF"
        style: Text.Raised; styleColor: "black"
        font.pixelSize: 16

    }

    AppIcon {
        id: btnCancel
        anchors.top: txtActiveSince.bottom
        anchors.horizontalCenter: txtActiveSince.horizontalCenter
        width: 48
        height: 48
        iconSource: "images/gpl/Gnome-call-stop_48.png"
        onClicked: OfonoContext.hangupCall(callId)
    }


}

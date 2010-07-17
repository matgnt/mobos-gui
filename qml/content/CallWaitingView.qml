import Qt 4.7
import "../ofonohelper.js" as Helper

Item {
    id: container
    width: 240
    height: 320
    property string callId: ""

    Text {
        x: 92
        y: 23
        text: "Number: "
        color: "#FFFFFF"
        style: Text.Raised; styleColor: "black"
        font.pixelSize: 16

    }

    Text {
        id: txtNumber
        x: 92
        y: 72
        text: Helper.getCallerNumber(callId);
        color: "#FFFFFF"
        style: Text.Raised; styleColor: "black"
        font.pixelSize: 16

    }


    AppIcon {
        id: btnAccept
        x: 41
        y: 129
        width: 48
        height: 48
        iconSource: "images/gpl/Gnome-call-start_48.png"
        onClicked: OfonoContext.answerCall(callId)
    }
    Loading {
        x: 104
        y: 139

    }

    AppIcon {
        id: btnCancel
        x: 152
        y: 129
        width: 48
        height: 48
        iconSource: "images/gpl/Gnome-call-stop_48.png"
        onClicked: OfonoContext.hangupCall(callId)
    }


}

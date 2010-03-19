import Qt 4.6

Item {
    id: container
    width: 240
    height: 320



        AppIcon {
            id: btnAccept
            x: 15
            y: 125
            width: 84
            height: 71
            iconSource: "images/gpl/Phone_58.png"
            //onClicked: openDial()
        }
        Loading {
            x: 104
            y: 139

        }

        AppIcon {
            id: btnCancel
            x: 142
            y: 125
            width: 84
            height: 71
            iconSource: "images/gpl/Phone_58.png"
            //onClicked: openDial()
        }


}

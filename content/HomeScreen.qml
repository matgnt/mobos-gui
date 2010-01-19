import Qt 4.6

Item {
    id: container
    property int iconSize: 58

    signal openDial

    Grid {
        columns: 4
        spacing: 10

        AppIcon {
            id: btnDial
            height: iconSize
            width: iconSize
            iconSource: "images/gpl/Phone_58.png"
            onClicked: openDial()
        }
        AppIcon {
            id: btnBrowser
            height: iconSize
            width: iconSize
            iconSource: "images/gpl/Browser_58.png"
        }
        AppIcon {
            id: btnCalendar
            height: iconSize
            width: iconSize
            iconSource: "images/gpl/Calendar_58.png"
        }
        AppIcon {
            id: btnSettings
            height: iconSize
            width: iconSize
            iconSource: "images/gpl/Settings_58.png"
        }
        AppIcon {
            id: btnChat
            height: iconSize
            width: iconSize
            iconSource: "images/gpl/Chat_58.png"
        }
        AppIcon {
            id: btnMaps
            height: iconSize
            width: iconSize
            iconSource: "images/gpl/Maps_58.png"
        }
        AppIcon {
            id: btnNotes
            height: iconSize
            width: iconSize
            iconSource: "images/gpl/Notes_58.png"
        }

    }

}

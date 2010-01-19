import Qt 4.6

import "content" as AppModules

Item {
    id: screen; width: 320; height: 480
    property string runningApp: ""

    Rectangle {
        id: background
        anchors.fill: parent; color: "#343434";

        Image { source: "content/images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }

        // here we show all our different views, e.g. ContactView, DialView
        Item {
            id: views
            x: 2; width: parent.width - 4
            //y:60 //Below the title bars
            y: 2
            height: 380
        }

        AppModules.HomeScreen{
            id: homeView
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width; height: parent.height-60;
            //x: -(screen.width * 1.5)
            onOpenDial: screen.runningApp = "dial"
        }

        AppModules.DialView{
            id: dialView
            x: -(screen.width*1.5)
            //x: 2
            y: 2;
            width: parent.width -4
            height: 380
            onBack: screen.runningApp = ""
        }



    }

    states: [
        State {
            name: "dial"
            when: screen.runningApp == "dial"
            PropertyChanges{ target: dialView; x: 0 }
            PropertyChanges{ target: homeView; x: (screen.width*2) }

        },
        State {
            name: "home"
            when: screen.runningApp == ""
            PropertyChanges{ target: dialView; x: -(screen.width*5) }
            PropertyChanges{ target: homeView; x: 0 }
        }
    ]

    transitions: [
        Transition { NumberAnimation { matchProperties: "x,y"; duration: 500; easing: "easeInOutQuad" } }
    ]

}

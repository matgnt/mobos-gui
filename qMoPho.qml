import Qt 4.6

import "content" as AppModules
import "3rdparty/qt/clocks" as ClockModule
import "3rdparty/qt/webbrowser" as WebbrowserModule

Item {
    id: screen; width: 240; height: 320
    //property string runningApp: ""

    Rectangle {
        id: background
        anchors.fill: parent; color: "#343434";

        Image { source: "content/images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }

        // title bar
        Item {
            id: titleBar
            width: parent.width
            height: 35
            Image {
                source: "content/images/grey_box_100.png"
                anchors.fill: parent
            }
           AppModules.AppIcon {
                iconSource: "images/key_100.png"
                id: btnHome
                text: "Home"
                width: parent.width / 4
                height: parent.height - 2
                onClicked: { screen.state = "" }
            }

        }

        // here we show all our different views, e.g. ContactView, DialView
        Item {
            id: views
            x: 2; width: parent.width - 4
            //y:60 //Below the title bars
            //y: 2
            anchors.top: titleBar.bottom
            height: screen.height - titleBar.height

            AppModules.HomeScreen{
                id: homeView
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width; height: parent.height-60;
                //x: -(screen.width * 1.5)
                onOpenDial: screen.state = "dial"
                onOpenClock: screen.state = "clock"
                onOpenBrowser: screen.state = "browser"
                onOpenContacts: screen.state = "contacts"

            }

            AppModules.DialView{
                id: dialView
                x: -(screen.width*5)
                //x: 2
                y: 2;
                width: parent.width
                height: parent.height
                //iconKeyWidth: parent.width / 3
                //iconKeyHeight: parent.height / 6
                onBack: screen.runningApp = ""
            }

            ClockModule.clocks {
                id: clockView
                y: 2;
                x: -(screen.width*5)
                onClicked: screen.runningApp = ""
            }

            WebbrowserModule.webbrowser {
                id: borwserView
                y: 2;
                x: -(screen.width*5)
                x: 0
                width: parent.width
                height: parent.height
            }

            AppModules.ContactsList {
                id: contacts
                x: -(screen.width*5)
                width: parent.width
                height: parent.height

            }


        }




    }

    states: [
        State {
            name: "dial"
            PropertyChanges{ target: dialView; x: 0 }
            PropertyChanges{ target: homeView; x: (screen.width*2) }

        },
        State {
            name: "clock"
            PropertyChanges{ target: clockView; x: 0 }
            PropertyChanges{ target: homeView; x: (screen.width*2) }
        },
        State {
            name: "browser"
            PropertyChanges{ target: borwserView; x:0 }
            PropertyChanges{ target: homeView; x: (screen.width*2) }
        },
        State {
            name: "contacts"
            PropertyChanges{ target: contacts; x:0 }
            PropertyChanges{ target: homeView; x: (screen.width*2) }
        }


    ]

    transitions: [
        Transition { NumberAnimation { matchProperties: "x,y"; duration: 500; easing: "easeInOutQuad" } }
    ]

}

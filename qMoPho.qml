import Qt 4.6

import "content" as AppModules
import "3rdparty/qt/clocks" as ClockModule
import "3rdparty/qt/webbrowser" as WebbrowserModule

Item {
    id: screen; width: 320; height: 480
    property string runningApp: ""

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
        }

        // here we show all our different views, e.g. ContactView, DialView
        Item {
            id: views
            x: 2; width: parent.width - 4
            //y:60 //Below the title bars
            //y: 2
            anchors.top: titleBar.bottom
            height: 380

            AppModules.HomeScreen{
                id: homeView
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width; height: parent.height-60;
                //x: -(screen.width * 1.5)
                onOpenDial: screen.runningApp = "dial"
                onOpenClock: screen.runningApp = "clock"
                onOpenBrowser: screen.runningApp = "browser"
            }

            AppModules.DialView{
                id: dialView
                x: -(screen.width*5)
                //x: 2
                y: 2;
                width: parent.width -4
                height: 404
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
                //x: -(screen.width*5)
                x: 0
                width: parent.width
                height: parent.height
            }

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
            PropertyChanges{ target: clockView; x: -(screen.width*5) }
            PropertyChanges{ target: borwserView; x: -(screen.width*5) }
            PropertyChanges{ target: homeView; x: 0 }
        },
        State {
            name: "clock"
            when: screen.runningApp == "clock"
            PropertyChanges{ target: clockView; x: 0 }
            PropertyChanges{ target: homeView; x: (screen.width*2) }
        },
        State {
            name: "browser"
            when: screen.runningApp == "browser"
            PropertyChanges{ target: borwserView; x:0 }
            PropertyChanges{ target: homeView; x: (screen.width*2) }
        }

    ]

    transitions: [
        Transition { NumberAnimation { matchProperties: "x,y"; duration: 500; easing: "easeInOutQuad" } }
    ]

}

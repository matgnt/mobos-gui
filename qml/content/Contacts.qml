import Qt 4.7


Rectangle {
    id: rectangle1
    width: 320
    height: 480

    // db script
    function findGreetings(seconds) {
        var db = openDatabaseSync("QmlExampleDB", "1.0", "The Example QML SQL!", 1000000);
        var text = ""

        db.transaction(
                function(tx) {
            // Create the database if it doesn't already exist
            tx.executeSql('CREATE TABLE IF NOT EXISTS Greeting(salutation TEXT, salutee TEXT)');

            // Add (another) greeting row
            tx.executeSql('INSERT INTO Greeting VALUES(?, ?)', [ seconds, 'world' ]);

            // Show all added greetings
            var rs = tx.executeSql('SELECT * FROM Greeting');

            var r = ""
            for(var i = 0; i < rs.rows.length; i++) {
                r += rs.rows.item(i).salutation + ", " + rs.rows.item(i).salutee + "\n"
                //console.log(r)
            }
            text += r
        }
        )
        //console.log(text)
        return text
    }

    // temp model
    ListModel {
         id: contactModel
         ListElement {
             name: "Bill Smith"
             number: "555 3264"
         }
         ListElement {
             name: "John Brown"
             number: "555 8426"
         }
         ListElement {
             name: "Sam Wise"
             number: "555 0473"
         }
     }


    Component {
        id: contactDelegate

        Item {
            id: wrapper
            width: listView.width
            height: 40

            Text { text: "Name: " + name }

        }

    }

    // connect model and view
    ListView {
        id: listView
        model: contactModel
        delegate: contactDelegate
        width: parent.width;
        //anchors.bottom: toolBar.top
        height: 200
        anchors.top: parent.top

    }



    ContactsToolbar { id: toolBar;
 height: 40;
 anchors.bottomMargin: 0
 anchors.bottom: parent.bottom
        width: parent.width; opacity: 0.9
        onAddContact: {
            console.log("addContact")
            var date = new Date;
            //console.log()
            var res = findGreetings(date.getSeconds())
            console.log(res)
        }

    }


}

import Qt 4.6

Item {
    id: toolbar


    signal back
    signal addContact

    BorderImage { source: "images/titlebar.sci"; width: parent.width; height: parent.height + 14; y: -7 }

    Button {
        id: btnBack
        text: "Back"
        anchors.left: parent.left; anchors.leftMargin: 5; y: 3; width: 140; height: 32
        onClicked: toolbar.back()
    }

    Button {
        id: btnAddContact
        text: "Add Contact..."
        anchors.right: parent.right; anchors.rightMargin: 5; y: 3; width: 140; height: 32
        onClicked: toolbar.addContact()
    }
}

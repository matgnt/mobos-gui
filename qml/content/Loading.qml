import Qt 4.7

Image {
    id: loading; source: "images/loading.png"; transformOrigin: "Center"
    NumberAnimation on rotation {
        id: rotationAnimation; from: 0; to: 360; running: loading.visible == true; loops: Animation.Infinite; duration: 900
    }
}

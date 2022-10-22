import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Color Swatches")

    Rectangle {
        anchors.fill: parent
        color: "#2E2E33"
    }

    ColorSwatch {
        anchors.fill: parent
        onColorChanged: (color)=> {
                             console.log("Current color: ", color)
                         }
    }
}

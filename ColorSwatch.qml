import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Shapes
import QtQuick.Controls

import Qt.labs.platform

import ColorSwatch

Page {
    id: root
    objectName: "Color_Palette"
    anchors.fill: parent
    anchors.margins: 6

    property color highlightColor: "white"
    property color borderColor: "black"

    signal colorChanged(color selectedColor)

    QtObject {
        id: internal
        property color currentSelectedColor: "transparent"
        onCurrentSelectedColorChanged: root.colorChanged(internal.currentSelectedColor)
    }

    header: RowLayout {

        Item {
            Layout.preferredWidth: 48
            Layout.preferredHeight: 48

            Item {
                anchors.fill: parent

                Rectangle {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    width: parent.width / 2
                    height: width
                    color: "white"
                }

                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    width: parent.width / 2
                    height: width
                    color: "white"
                }

                Rectangle {
                    anchors.top: parent.top
                    anchors.right: parent.right
                    width: parent.width / 2
                    height: width
                    color: "lightgray"
                }

                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    width: parent.width / 2
                    height: width
                    color: "lightgray"
                }

                Rectangle {
                    anchors.centerIn: parent
                    width: Math.sqrt((parent.width* parent.width) + (parent.width* parent.width)) - 4 //parent.width
                    height: 4
                    color: "red"
                    rotation: 45
                }
            }

            Rectangle {
            anchors.fill: parent
            border.color: "black"
            border.width: 2
            color: internal.currentSelectedColor
            }
        }

        Item { Layout.fillWidth: implicitWidth > 0 ? false : true }

        ComboBox {
            id: cmbox
            Layout.alignment: Qt.AlignRight
            Layout.maximumWidth: 180
            implicitContentWidthPolicy: ComboBox.WidestTextWhenCompleted
            flat: true
            textRole: "Title"
            valueRole: "Value"
            model: swatchesModel

            property bool initialized: false

            onCurrentValueChanged: {
                if (initialized) {
                    swatchesModel.setCurrentSwatch(currentValue)
                    colorPaletteModel.load(currentValue)
                }
            }

            Component.onCompleted: {
                const index = swatchesModel.currentSwatch()
                const curIndex = indexOfValue(index)
                currentIndex = (curIndex === -1) ? 0 : curIndex
                initialized = true
            }
        }

        ToolButton {
            Layout.alignment: Qt.AlignRight
            display: AbstractButton.IconOnly
            Layout.preferredWidth: 48
            Layout.preferredHeight: 48
            padding: 0
            spacing: 0
            horizontalPadding: 0
            flat: true
            icon.source: "qrc:/ColorSwatch/assets/task--add.svg"
            text: "New Swatch"
            onClicked: dialog.open()
        }

        ToolButton {
            Layout.alignment: Qt.AlignRight
            display: AbstractButton.IconOnly
            Layout.preferredWidth: 48
            Layout.preferredHeight: 48
            padding: 0
            spacing: 0
            horizontalPadding: 0
            flat: true
            icon.source: "qrc:/ColorSwatch/assets/subtract.svg"
            text: "New Swatch"
            onClicked: {
                swatchesModel.removeByID(cmbox.currentValue)
                cmbox.decrementCurrentIndex()
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 6
        id: mainLayout

        Flickable {
            Layout.fillWidth: true
            Layout.fillHeight: true
            boundsBehavior: Flickable.StopAtBounds
            boundsMovement: Flickable.StopAtBounds
            contentWidth: flow.implicitWidth
            contentHeight: flow.implicitHeight
            clip: true

            MouseArea {
                objectName: "Color_Palette_Reset_Selection"
                width: mainLayout.width
                height: mainLayout.height
                onClicked: {
                    flow.selectedItem = -1
                }
            }

            Flow {
                id: flow
                objectName: "Color_Palette_Flow_Layout"
                width: mainLayout.width
                height: mainLayout.height
                spacing: 6

                property int selectedItem: -1

                Repeater {
                    id: repeater
                    objectName: "Color_Palette_Repeater"

                    model: colorPaletteModel

                    Rectangle {
                        id: swatch
                        objectName: "Color_Palette_Swatch"

                        width: Screen.pixelDensity * 5
                        height: width
                        color: model.ColorSwatch
                        border.color: root.borderColor
                        border.width: index === flow.selectedItem ? 3 : 1
                        radius: 2

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                flow.selectedItem = index
                                if ( index !== -1 ) {
                                    const color = colorPaletteModel.colorAt( index )
                                    internal.currentSelectedColor = color
                                }
                            }
                        }

                        Shape {
                            objectName: "Color_Palette_Selected_Shape"
                            anchors.fill: parent
                            opacity: index === flow.selectedItem

                            Behavior on opacity { NumberAnimation{ duration: 150; easing.type: Easing.InOutCubic } }

                            ShapePath {
                                strokeWidth: 1
                                fillColor: "transparent"
                                strokeColor: root.highlightColor
                                strokeStyle: ShapePath.DashLine
                                dashPattern: [ 1, 3 ]
                                startX: 0; startY: 0
                                PathLine { x: swatch.width; y: 0 }
                                PathLine { x: swatch.width; y: swatch.height }
                                PathLine { x: 0; y: swatch.width }
                                PathLine { x: 0; y: 0 }
                            }
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            ToolButton {
                Layout.alignment: Qt.AlignRight
                display: AbstractButton.IconOnly
                Layout.preferredWidth: 48
                Layout.preferredHeight: 48
                padding: 0
                spacing: 0
                horizontalPadding: 0
                flat: true
                icon.source: "qrc:/ColorSwatch/assets/subtract.svg"
                text: "Delete"
                onClicked: {
                    if (flow.selectedItem !== -1) {
                        colorPaletteModel.removeAt(flow.selectedItem, cmbox.currentValue)
                        flow.selectedItem -= 1
                        internal.currentSelectedColor = colorPaletteModel.colorAt( flow.selectedItem )
                    }
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignRight
                display: AbstractButton.IconOnly
                Layout.preferredWidth: 48
                Layout.preferredHeight: 48
                padding: 0
                spacing: 0
                horizontalPadding: 0
                flat: true
                icon.source: "qrc:/ColorSwatch/assets/add.svg"
                text: "Add"
                onClicked: colorDialog.open()
            }
        }
    }

    // ***************************************
    // MODELS
    // ***************************************
    ColorPaletteModel{ id: colorPaletteModel }
    SwatchesModel { id: swatchesModel }

    // ***************************************
    // DIALOGS
    // ***************************************
    InputDialog {
        id: dialog
        title: qsTr("ADD SWATCH")
        onReturnValue: (value) => {
                           swatchesModel.add(value)
                           cmbox.incrementCurrentIndex()
                           colorPaletteModel.clear(cmbox.currentValue)
                           internal.currentSelectedColor = "transparent"
                       }
    }

    ColorDialog {
        id: colorDialog
        onAccepted: {
            colorPaletteModel.addColor(color, cmbox.currentValue)
            flow.selectedItem = repeater.count - 1
            internal.currentSelectedColor = colorPaletteModel.colorAt( flow.selectedItem )
        }
    }
}

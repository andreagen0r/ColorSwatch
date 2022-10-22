import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root
    width: 400
    modal: true
    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.CloseOnEscape

    signal returnValue(string input)

    footer: DialogButtonBox {
        Button {
            id: cancelButton
            text: qsTr("Cancel")
            flat: true
            onClicked: reject()
        }

        Button {
            id: acceptButton
            text: qsTr("Accept")
            onClicked: actionAdd.trigger()
        }
    }

    ColumnLayout {
        id: layout
        anchors.fill: parent
        spacing: 12

        TextField {
            id: txtField
            Layout.fillWidth: true
            focus: true
            onEditingFinished: actionAdd.trigger()
            placeholderText: qsTr("New swatch")
            font.pointSize: 12

            Label {
                id: errorLabel
                anchors.top: parent.bottom
                anchors.topMargin: 4
                opacity: 0
                color: "red"
                text: "The value can't be empty"

                Behavior on opacity { NumberAnimation{ duration: 250; easing.type: Easing.InOutCubic } }
            }
        }
    }

    Action {
        id: actionAdd
        onTriggered: {
            if (txtField.text !== "") {
                returnValue(txtField.text)
                txtField.clear()
                accept()
            } else {
                errorLabel.opacity = 1
                timer.start()
                txtField.focus = true
            }
        }
    }

    Timer {
        id: timer
        interval: 3000
        onTriggered: {
            errorLabel.opacity = 0
        }
    }
}

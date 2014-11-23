import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: soundDialog
    property string selectedSound

        Column {
            id: column
            width: (soundDialog.width/1.5)
            spacing: Theme.paddingMedium
            anchors.horizontalCenter: parent.horizontalCenter

            DialogHeader {
                title: "Click sound:"
            }

            Button {
                width: column.width
                x:Theme.paddingMedium
                text: "beep"
                color: (selectedSound == "beep") ? Theme.highlightColor : Theme.primaryColor
                onClicked: selectedSound = "beep"
            }
            Button {
                width: column.width
                x:Theme.paddingMedium
                text: "click"
                color: (selectedSound == "click") ? Theme.highlightColor : Theme.primaryColor
                onClicked: selectedSound = "click"
            }
            Button {
                width: column.width
                x:Theme.paddingMedium
                text: "metronome"
                color: (selectedSound == "metronome") ? Theme.highlightColor : Theme.primaryColor
                onClicked: selectedSound = "metronome"
            }
            Button {
                width: column.width
                x:Theme.paddingMedium
                text: "seiko"
                color: (selectedSound == "seiko") ? Theme.highlightColor : Theme.primaryColor
                onClicked: selectedSound = "seiko"
            }
            Button {
                width: column.width
                x:Theme.paddingMedium
                text: "sticks"
                color: (selectedSound == "sticks") ? Theme.highlightColor : Theme.primaryColor
                onClicked: selectedSound = "sticks"
            }
        }
}

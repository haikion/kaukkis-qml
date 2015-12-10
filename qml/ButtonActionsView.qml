//Contains button output settings
import QtQuick 2.0
import Sailfish.Silica 1.0
import org.kaukkis 1.0

Dialog {
    id: dialogRoot
    property var buttonModel //Should be defined by the creator.

    Component.onCompleted: {
        console.log("buttonModel = " + buttonModel);
    }

    SilicaListView {
        //anchors.top: dialogHeader.bottom
        //anchors.bottom: dialogRoot.bottom
        anchors.fill: parent
        focus: true //Does what?
        model: ButtonActionsModel
        id: listView
        delegate: delegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }


        Component.onCompleted: {
            console.log("model="+model+" parent="+parent+" width="+width+" height="+height);
        }
    }

    Component {
        id: delegate

        Text {
            id: rect
            text: name
            font.bold: true
            styleColor: "green"

            Component.onCompleted: {
                console.log("name="+name)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    listView.currentIndex = index
                }
            }
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            console.log(" Currentindex=" + listView.currentIndex)
            ButtonActionsModel.setButtonAction(buttonModel, listView.currentIndex); //TODO: Add button ptr
        }
    }
}

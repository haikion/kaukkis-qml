//Contains plugin settings view

import QtQuick 2.0
import Sailfish.Silica 1.0
import org.kaukkis 1.0

Dialog {
    id: dialogRoot

    Component.onCompleted: {
        console.log("PluginDialogModel = " + PluginDialogModel);
    }

    SilicaListView {
        anchors.fill: parent
        model: PluginDialogModel
        id: listView
        delegate: delegate
        spacing: 2

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
            font.pixelSize:  50

            Component.onCompleted: {
                console.log("name=" + name + "listView.count=" + listView.count)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Attempting to open dialog with QML url: " + PluginDialogModel.pluginDailogQML(index));
                    //TODO: Figure out how plugin dialog is suppose to communicate with plugin ...Fucking QML
                    pageStack.push(PluginDialogModel.pluginDailogQML(index));
                }
            }
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            console.log(" Currentindex=" + listView.currentIndex)
        }
    }
}


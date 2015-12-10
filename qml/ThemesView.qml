//Contains button output settings
import QtQuick 2.0
import Sailfish.Silica 1.0
import org.kaukkis 1.0

Dialog {
    id: dialogRoot
    property string selectedName: "default"

    Component.onCompleted: {
        console.log("ThemesModel = " + ThemesModel);
    }

    DialogHeader {
        id: dialogHeader
    }

    SilicaListView {
        anchors.top: dialogHeader.bottom
        anchors.bottom: dialogRoot.bottom
        //anchors.fill: parent
        focus: true //Does what?
        model: ThemesModel
        id: listView
        delegate: delegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }


        Component.onCompleted: {
            console.log("currentItem.name="+currentItem.name+" parent="+parent+" width="+width+" height="+height);
            currentIndex = ThemesModel.currentThemeIndex();
            selectedName = currentItem.name
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
                    selectedName = name
                }
            }
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            console.log("currentIndex =" + listView.currentIndex)
            ThemesModel.setTheme(listView.currentIndex)
        }
    }
}

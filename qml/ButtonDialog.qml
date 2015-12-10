import QtQuick 2.0
import Sailfish.Silica 1.0
import org.kaukkis 1.0

Dialog {
    id: dialogRoot
    property int buttonType: 0;

    ButtonDialogModel {id: dialogModel}
    ButtonsModel {id: buttonsModel}

    DialogHeader {
        id: header
        title: qsTr("Choose button icon")
    }

    Component {
        id: rectDelegate
        Image {
            id: rect

            width: 100
            height: 100
            source: imagePath

            Component.onCompleted: {
                console.log("imagePath="+imagePath)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    buttonsGrid.currentIndex = index
                    buttonType = type;
                }
            }
        }
    }

    GridView {
        width: parent.width
        height: parent.height
        cellWidth: 130;
        cellHeight: 130;
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true //Does what?
        model: buttonsModel
        id: buttonsGrid
        anchors.top: header.bottom

        delegate: rectDelegate

        Component.onCompleted: {
            console.log("model="+model+" parent="+parent+" width="+width+" height="+height);
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            console.log("selectedButton="+buttonType)
        }
    }
}

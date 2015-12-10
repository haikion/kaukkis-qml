import QtQuick 2.0
import Sailfish.Silica 1.0
import org.kaukkis 1.0

Image {
    //Button model
    property Button buttonModel     //Needs to be defined in createObject
    property var connection;
    //anchors.centerIn: parent
    id: buttonView
    source: buttonModel.imageReleasedURL
    state: buttonModel.modelState
    Component.onCompleted: {
        //QML is buggy peace of shit so object binding doesn't work with dynamic objects
        //hence manual approach.
        buttonModel.modelStateChanged.connect(updateState)
        buttonView.x = buttonModel.x
        buttonView.y = buttonModel.y
    }

    Component.onDestruction: {
        //Destroy all dynamically created signal connections
        buttonModel.modelStateChanged.disconnect(updateState)
    }

    function updateState() {
        state = buttonModel.modelState;
    }

    states: [
        State {
            name: "USE"
            PropertyChanges {target: mouseArea; drag. axis: Drag.None}
            PropertyChanges {target: mouseArea; onPressAndHold: {}}
            PropertyChanges {target: mouseArea; onPressed: {
                    buttonView.source = buttonModel.imagePressedURL;
                    buttonModel.press();
                }
            }
            PropertyChanges {target: mouseArea; onReleased: {
                    buttonView.source = buttonModel.imageReleasedURL;
                    buttonModel.release();
                }
            }
        },
        State {
            name: "EDIT"
            PropertyChanges {target: mouseArea; drag.axis: Drag.XAndYAxis}
            PropertyChanges {target: mouseArea; onPressed: {}}
            PropertyChanges {target: mouseArea; onPressAndHold: contextMenu.show(buttonView)}
            PropertyChanges {target: mouseArea; onReleased: {
                    buttonModel.x = buttonView.x;
                    buttonModel.y = buttonView.y;
                }
            }
        }
    ]

    MouseArea {
        anchors.fill: parent
        drag.target: buttonView
        drag.axis: Drag.XandYAxis
        id: mouseArea;
        onPressed:  { //REMOVE???
            buttonView.source = buttonModel.imagePressedURL;
        }
        onReleased: {//REMOVE???
            buttonView.source = buttonModel.imageReleasedURL;
            buttonModel.x = buttonView.x;
            buttonModel.y = buttonView.y;
        }
        onPressAndHold: {//REMOVE???
            contextMenu.show(buttonView);
        }
    }

    ContextMenu {
        id: contextMenu;
        MenuItem {
            text: "Remove Button"
            onClicked: {
                console.log("Remove Button")
                buttonModel.removeSelf();
                buttonView.destroy();
            }
        }
        MenuItem {
            text: "Button action Settings"
            onClicked:   {
                var dialog = pageStack.push(Qt.resolvedUrl("ButtonActionsView.qml"), {buttonModel: buttonModel})
            }
        }
        MenuItem {
            text: "Choose Button Image"
            onClicked:   {
               var dialog = pageStack.push(Qt.resolvedUrl("ButtonDialog.qml"))
                dialog.accepted.connect(function() {
                    buttonModel.setType(dialog.buttonType);
                    buttonView.source = buttonModel.imageReleasedURL;
                    console.log("Button theme set: " + dialog.buttonType);
                })
            }
        }
    }
}

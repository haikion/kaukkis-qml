import QtQuick 2.0
import Sailfish.Silica 1.0
import org.kaukkis 1.0

Dialog {
    property string name

    Column {
        width: parent.width
        spacing: 2

        DialogHeader { }
        Row {
            spacing: 2

            Label {
                text: "IP: "
            }

            TextField {
                id: ipField
                text: "192.168.1.5"
            }
        }

        Row {
            spacing: 2

            Label {
                text: "Port: "
            }

            TextField {
                id: portField
                validator: IntValidator {}
                text: "4848"
            }
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            NetworkOutput.setIP(ipField.text);
            NetworkOutput.setPort(portField.text);
        }
    }
}

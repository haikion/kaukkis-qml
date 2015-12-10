import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    SilicaListView {
        anchors.fill: parent
        spacing: Theme.paddingLarge

        header: DialogHeader {
            title: qsTr("About")
        }

        model: VisualItemModel {

            PageHeader {
                title: qsTr("%1 %2").arg(Qt.application.name).arg(Qt.application.version)
            }

            Label {
                wrapMode: Text.WordWrap
                anchors {
                    left: parent ? parent.left : undefined
                    right: parent ? parent.right : undefined
                    margins: Theme.paddingLarge
                }
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("QtQuick 2 promises superior performance, a
                    new particle system and a host of new possibilities: http://doc.qt.nokia.co
                            m/qt5/qtquick2-whatsnew.html It is also quite ripe for testing if you are into that ki
nd of thing. This is my personally recommended approach to testing QtQuick 2 on your n9(
                        50) at this point in time and I have to stress that
QtQuick 2 promises superior performance, a new particle system and a host of new possibilities: http://doc.qt.nokia.com/qt5/qtquick2-whatsnew.html It is also quite ripe for testing if you are into that kind of thing. This is my personally recommended approach to testing QtQuick 2 on your n9(50) at this point in time and I have to stress that
QtQuick 2 promises superior performance, a new particle system and a host of new possibilities: http://doc.qt.nokia.com/qt5/qtquick2-whatsnew.html It is also quite ripe for testing if you are into that kind of thing. This is my personally recommended approach to testing QtQuick 2 on your n9(50) at this point in time and I have to stress that
QtQuick 2 promises superior performance, a new particle system and a host of new possibilities: http://doc.qt.nokia.com/qt5/qtquick2-whatsnew.html It is also quite ripe for testing if you are into that kind of thing. This is my personally recommended approach to testing QtQuick 2 on your n9(50) at this point in time and I have to stress that
QtQuick 2 promises superior performance, a new particle system and a host of new possibilities: http://doc.qt.nokia.com/qt5/qtquick2-whatsnew.html It is also quite ripe for testing if you are into that kind of thing. This is my personally recommended approach to testing QtQuick 2 on your n9(50) at this point in time and I have to stress that")
            }

            SectionHeader {
                text: qsTr("Contact")
            }

            Column {
                anchors {
                    left: parent ? parent.left : undefined
                    right: parent ? parent.right : undefined
                    margins: Theme.paddingLarge
                }
                Label {
                    width: parent.width
                    textFormat: Text.StyledText
                    linkColor: Theme.highlightColor
                    font.pixelSize: Theme.fontSizeSmall
                    truncationMode: TruncationMode.Fade
                    text: "Bug reports: <a href='https://github.com/haikion/kaukkis/issues'>GitHub</a>"
                    onLinkActivated: Qt.openUrlExternally(link)
                }
            }

            SectionHeader {
                text: qsTr("Developers")
            }

            Label {
                textFormat: Qt.RichText
                wrapMode: Text.WordWrap
                anchors {
                    left: parent ? parent.left : undefined
                    right: parent ? parent.right : undefined
                    margins: Theme.paddingLarge
                }
                font.pixelSize: Theme.fontSizeSmall
                text: "Niko Häikiö (haikion@github)"
            }

            Item { width: 1; height: 1 }
        }

        VerticalScrollDecorator { }
    }
}

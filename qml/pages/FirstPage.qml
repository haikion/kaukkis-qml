/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import "../"

Page {
    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent
        id: silicaFlickable
        state: "EDIT" //Initial state USE or EDIT
        RemoteView {id: remoteView}
        property var useMenuNames: ["Edit Mode", "About"]
        property var editMenuNames: ["Use Mode", "Add New Button", "Plugin Settings", "Theme Selection"]

        function menuActions(i) {
            if (silicaFlickable.state == "USE")
            {
                switch (i) {
                    case 0:
                        silicaFlickable.state = "EDIT"
                        break;
                    case 1:
                        pageStack.push(Qt.resolvedUrl("../AboutDialog.qml"))
                        //pageStack.push(Qt.resolvedUrl("../ButtonActionsView.qml"))
                        break;
                }
            }
            else
            {
                switch (i) {
                    case 0:
                        silicaFlickable.state = "USE"
                        remoteView.saveSettings()
                        break;
                    case 1:
                        remoteView.createButton()
                        break;
                    case 2:
                        pageStack.push(Qt.resolvedUrl("../PluginDialogView.qml"))
                        break;
                    case 3:
                        //TODO: Implement Theme menu
                        pageStack.push(Qt.resolvedUrl("../ThemesView.qml"))
                        break;
                }
            }
        }

        states: [
            State {
                name: "USE"
                PropertyChanges {target: repeater; model: silicaFlickable.useMenuNames}
                PropertyChanges {target: remoteView; state: "USE"}
            },
            State {
                name: "EDIT"
                PropertyChanges {target: repeater; model: silicaFlickable.editMenuNames}
                PropertyChanges {target: remoteView; state: "EDIT"}
            }
        ]

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            id: pullDownMenu
            Repeater {
                model: silicaFlickable.useMenuNames
                id: repeater
                MenuItem {
                    text: modelData
                    onClicked: silicaFlickable.menuActions(index)
                }
            }
        }
    }
}



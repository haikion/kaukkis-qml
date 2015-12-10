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

#ifdef QT_QML_DEBUG
#include <QtQuick>
#include <QQuickItem>
#include <sailfishapp.h>
#endif

#include "remote.h"
#include "buttonsmodel.h"
#include "buttonactionsmodel.h"
#include "pluginhandler.h"
#include "plugindialog.h"
#include "themesmodel.h"

//I'm not very good with this.. ;__;
namespace singletons {
    ButtonActionsModel* buttonActionsModel;
    PluginDialog* pluginDialogModel;
    ThemesModel* themesModel;
    Remote* remote;
}

static QObject* pluginDialogProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    qDebug() << "Running pluginDialogProvider";
    return singletons::pluginDialogModel;
}

static QObject* buttonActionsProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    qDebug() << "Running buttonActionsModelProvider 2";
    return singletons::buttonActionsModel;
}

static QObject* themesModelProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    qDebug() << "Running themesModelProvider";
    return singletons::themesModel;
}

static QObject* remoteProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    qDebug() << "Running remoteProvider";
    return singletons::remote;
}

int main(int argc, char *argv[])
{
    //SailfishApp::main(); //will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    QGuiApplication* app = SailfishApp::application(argc, argv); // to get the QGuiApplication *
    PluginHandler* pluginHandler = new PluginHandler(app);
    singletons::remote = new Remote();
    singletons::buttonActionsModel = new ButtonActionsModel(app, pluginHandler);
    singletons::pluginDialogModel = new PluginDialog(app, pluginHandler);
    singletons::themesModel = new ThemesModel(singletons::remote);

   //Remote* remote = new Remote("Default remote", view->engine(), view->rootObject());
    QQuickView* view = SailfishApp::createView(); // to get a new QQuickView * instance
    qDebug() << "Registering QML types";
    qmlRegisterType<ButtonsModel>("org.kaukkis", 1, 0, "ButtonsModel"); //Used in buttonDialog
    qmlRegisterType<ButtonActionsModel>("org.kaukkis", 1, 0, "RemoteOutputsModel");
    qmlRegisterSingletonType<Remote>("org.kaukkis", 1, 0, "Remote", remoteProvider);
    qmlRegisterSingletonType<PluginDialog>("org.kaukkis", 1, 0, "PluginDialogModel", pluginDialogProvider);
    qmlRegisterSingletonType<ButtonActionsModel>("org.kaukkis", 1, 0, "ButtonActionsModel", buttonActionsProvider);
    qmlRegisterSingletonType<ThemesModel>("org.kaukkis", 1, 0, "ThemesModel", themesModelProvider);
    view->setSource(SailfishApp::pathTo("qml/harbour-kaukkisQML.qml"));
    view->showFullScreen();
    return app->exec();
    //return SailfishApp::main(argc, argv);
}


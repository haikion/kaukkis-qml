#ifndef NETWORKOUTPUT_H
#define NETWORKOUTPUT_H

#include <vector>
#include <QString>
#include <QSignalMapper>
#include <QSettings>
#include <QtCore/qplugin.h>
#include <QtQuick>
#include "../../iremoteoutput.h"
#include "../../buttonaction.h"
#include "client.h"

namespace Ui {
    class NetworkOutputDialog;
}

class NetworkOutput : public QObject, public IRemoteOutput
{

    Q_OBJECT
    Q_INTERFACES(IRemoteOutput)
    Q_PLUGIN_METADATA(IID "org.kaukkis.NetworkOutput") //Jolla compatibility

public:
    NetworkOutput();

    virtual std::vector<ButtonAction> buttonActions() const;
    virtual QString name() const;
    virtual QString settingsDialogQML();

public slots:
    //QML
    void setPort(const QString& port);
    void setIP(const QString& ip);

private slots:
    void sendKeyPress(int keyInt);
    void sendKeyRelease(int keyInt);

private:
    static const QString NAME;
    static const std::vector<Qt::Key> SUPPORTED_KEYS;

    //Gets defined as 'this' in consturctor.
    //Work-a-around for static function being unable use 'this' directly.
    static QObject* this_;
    //Holds all buttton actions of this plugin
    std::vector<ButtonAction> buttonActions_;
    //network client
    Client client_;
    Ui::NetworkOutputDialog* ui_;
    QSettings settings_;

    static QObject* provider(QQmlEngine* engine, QJSEngine* scriptEngine);
    void buildButtonActions();
    ButtonAction generateButtonAction(const Qt::Key key);
    void saveSettings();
    bool loadSettings();
};

#endif // NETWORKOUTPUT_H

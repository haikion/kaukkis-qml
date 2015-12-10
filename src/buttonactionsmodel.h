#ifndef REMOTEOUTPUTSMODEL_H
#define REMOTEOUTPUTSMODEL_H

#include <QAbstractListModel>
#include "button.h"
#include "iremoteoutput.h"
#include "pluginhandler.h"

class ButtonActionsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ButtonActionRoles {
        NameRole = Qt::UserRole + 1
    };

    ButtonActionsModel(QObject* parent = 0, PluginHandler* pluginHandler = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
    void setButtonModel(Button *button);
    void setButtonAction(Button *button, int index);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ButtonAction> buttonActions_;
    QList<IRemoteOutput*> remoteOutputs_;
    Button* button_;
    PluginHandler* pluginHandler_;
};

#endif // REMOTEOUTPUTSMODEL_H

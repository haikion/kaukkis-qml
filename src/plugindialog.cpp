#include "plugindialog.h"

PluginDialog::PluginDialog(QObject *parent, PluginHandler* pluginHandler):
        QAbstractListModel(parent),
        pluginHandler_(pluginHandler)
{
}

QVariant PluginDialog::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= pluginHandler_->plugins().size())
        return QVariant();

    const IRemoteOutput* plugin = pluginHandler_->plugins().at(index.row());
    if (role == NameRole)
        return  plugin->name();
    return QVariant();
}

QString PluginDialog::pluginDailogQML(unsigned i)
{
    IRemoteOutput* plugin = pluginHandler_->plugins().at(i);
    return plugin->settingsDialogQML();
}

QHash<int, QByteArray> PluginDialog::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

int PluginDialog::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return pluginHandler_->plugins().size();
}

#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <vector>
#include <QAbstractListModel>
#include <QQuickItem>
#include "pluginhandler.h"
#include "iremoteoutput.h"

class PluginDialog : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PluginsRoles {
        NameRole = Qt::UserRole + 1
    };

    struct PluginData {
        QString name;
    };

    PluginDialog(QObject* parent = 0, PluginHandler* pluginHandler = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
    QString pluginDailogQML(unsigned i);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    std::vector<IRemoteOutput*> plugins_;

    PluginHandler* pluginHandler_;
};

#endif // PLUGINDIALOG_H

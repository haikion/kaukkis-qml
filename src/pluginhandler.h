#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <vector>
#include <QObject>
#include "iremoteoutput.h"

class PluginHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PluginHandler)

public:
    QObject* provider();

    PluginHandler(QObject* parent = 0);
    std::vector<IRemoteOutput*> plugins() const;

private:
    static const std::vector<QString> PLUGINS_DIRS;

    std::vector<IRemoteOutput*> plugins_;

    void loadDynamicPlugins();
    void loadStaticPlugins();
};

#endif // PLUGINLOADER_H

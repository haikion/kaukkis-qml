#include <set>
#include <QDir>
#include <QString>
#include <QApplication>
#include <QPluginLoader>
#include "pluginhandler.h"
#include "src/plugins/NetworkOutput/networkoutput.h"

const std::vector<QString> PluginHandler::PLUGINS_DIRS = {"/usr/lib/kaukkis/plugins", "plugins"};

PluginHandler::PluginHandler(QObject* parent):
    QObject(parent)
{
    loadStaticPlugins();
    //loadDynamicPlugins();
}

std::vector<IRemoteOutput *> PluginHandler::plugins() const
{
    return plugins_;
}

QObject *PluginHandler::provider()
{
    return this;
}

void PluginHandler::loadStaticPlugins()
{
    //For devolopment purporses only
    //ready plugins should be dynamic
    plugins_.push_back(new NetworkOutput());
}

//Scans plugin dir for new plugins
void PluginHandler::loadDynamicPlugins()
{
    std::set<QString> pluginNames;

    QDir fileBrowser(qApp->applicationDirPath());

    qDebug() << "Loading plugins...current directory: " << fileBrowser.path();;

    for (const QString& pluginsDir : PLUGINS_DIRS)
    {
        if ( ! fileBrowser.cd(pluginsDir) )
        {
            qDebug() << "Unable to open directory: " << pluginsDir;
            continue;
        }
        qDebug() << "Opening directory: " << pluginsDir;
        //Iterate through plugin directories
        for (const QString& pluginDir : fileBrowser.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QDir fileBrowser2 = fileBrowser;
            bool rVal = fileBrowser2.cd(pluginDir);
            qDebug() << "Opening plugin directory: " << pluginDir;
            Q_ASSERT_X(rVal, "loadOutputPlugins()", "Directory could not be opened.");
            //Open plugin files
            for (const QString& pluginFile : fileBrowser2.entryList(QDir::Files))
            {
                QPluginLoader pluginLoader(fileBrowser2.absoluteFilePath(pluginFile));
                QObject* plugin = pluginLoader.instance();
                if (plugin)
                {
                    qDebug() << "Detected plugin file: " << pluginFile;
                    IRemoteOutput* newRemoteOutput = qobject_cast<IRemoteOutput*>(plugin);
                    if (newRemoteOutput)
                    {
                        auto rVal = pluginNames.insert(newRemoteOutput->name());
                        if (rVal.second)
                        {
                            qDebug() << "Loaded " << newRemoteOutput->name() << " plugin.";
                            //remoteOutputs2_.push_back(std::unique_ptr<IRemoteOutput>(newRemoteOutput));
                            plugins_.push_back(newRemoteOutput);
                        }
                        else
                        {
                            qDebug() << "Duplicated plugin detected: " << newRemoteOutput->name();
                        }
                    }
                }
                else
                {
                    qDebug() << "Error loading plugin: " << pluginLoader.errorString();
                }
            }
        }
    }
    //NetworkOutput* newPlugin = new NetworkOutput();
    //remoteOutputs_.push_back(newPlugin);
    //remoteOutputs_.push_back(std::unique_ptr<IRemoteOutput>(newPlugin));
}

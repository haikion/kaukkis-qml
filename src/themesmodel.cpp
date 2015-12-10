#include <QDir>
#include <QDebug>
#include "themesmodel.h"

const std::vector<QString> ThemesModel::THEMES_DIRS = {"themes", "/usr/share/kaukkis/themes"};

ThemesModel::ThemesModel(Remote* remote)  :
    QAbstractListModel(remote)
{
    loadThemes();
}

ThemesModel::~ThemesModel()
{
    for (Theme* theme : themes_)
    {
        delete theme;
    }
}

void ThemesModel::setTheme(int index)
{
    remote()->setTheme(themes_.at(index));
}

int ThemesModel::currentThemeIndex() const
{
    for (unsigned i = 0; i < themes_.size(); ++i)
    {
        Theme* theme = themes_.at(i);
        //TODO: ThemesModel should be the sole owner of
        //themes. Now remote generates default theme.
        if (theme->name() == remote()->theme()->name())
        {
            return i;
        }
    }
    return 0;
}

void ThemesModel::loadThemes()
{
    QDir fileBrowser(qApp->applicationDirPath());
    qDebug() << "ThemeDialog: Loading themes...current directory: " << fileBrowser.path();;

    for (const QString& themesDir : THEMES_DIRS)
    {
        qDebug() << "ThemeDialog: Opening directory: " << themesDir;
        if ( ! fileBrowser.cd(themesDir) )
        {
            qDebug() << "ThemeDialog: Unable to open directory: " << themesDir;
            continue;
        }
        //Iterate through theme directoriesF
        for (const QString& themeDir : fileBrowser.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QDir fileBrowser2 = fileBrowser;
            bool rVal = fileBrowser2.cd(themeDir);
            Q_ASSERT_X(rVal, "ThemeDialog: loadThemes()", "Directory could not be opened.");
            qDebug() << "ThemeDialog: new theme found: " << themeDir;
            Theme* newTheme = new Theme(themeDir);
            //TODO: Check if theme was able to load
            themes_.push_back(newTheme);
        }
    }
}

Remote* ThemesModel::remote() const
{
    return qobject_cast<Remote*>(parent());
}


QVariant ThemesModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= themes_.size())
        return QVariant();

    Theme* theme = themes_.at(index.row());
    if (role == NameRole)
        return theme->name();
    return QVariant();
}

QHash<int, QByteArray> ThemesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

int ThemesModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return themes_.size();
}

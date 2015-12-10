#ifndef THEMEDIALOG_H
#define THEMEDIALOG_H

#include <vector>
#include "theme.h"
#include "remote.h"

//TODO: Convert into list model
class ThemesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ThemesRoles {
        NameRole = Qt::UserRole + 1
    };

    explicit ThemesModel(Remote *remote);
    ~ThemesModel();

    void setActiveRemote(Remote* remote);


    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public  slots:
    int currentThemeIndex() const;
    void setTheme(int index);

private:
    QHash<int, QByteArray> roleNames() const;
    std::vector<Theme*> themes_;

    static const std::vector<QString> THEMES_DIRS;

    void loadThemes();
    Remote* remote() const;
};

#endif // THEMEDIALOG_H

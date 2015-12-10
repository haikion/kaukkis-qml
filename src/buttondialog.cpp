/**
 * @(#) ButtonDialog.cpp
 */

#include <map>
#include <QDebug>
#include <QList>
#include "buttondialog.h"
#include "buttonaction.h"
#include "buttontheme.h"
#include "theme.h"
#include "buttonitem.h"

ButtonDialog::ButtonDialog()
{
}

ButtonDialog::ButtonDialog(QQuickView *view)
{
    QList<QObject*> dataList;
    Theme theme = Theme("default"); //TODO: Enable different themes

    qDebug() << "ButtonDialog() called view = " << view;
    //Construct selection menu.
    for (auto it = BUTTON_NAMES.begin(); it != BUTTON_NAMES.end(); ++it)
    {
        QString name = it->second;
        ButtonType bt = it->first;
        ButtonTheme buttonTheme = theme.buttonTheme(bt);
        dataList.push_back(new ButtonItem(name, buttonTheme.imageReleasedURL, this));
    }
    view->rootContext()->setContextProperty("buttonsModel", QVariant::fromValue(dataList));
    qDebug() << "dataList size: " << dataList.size();
}

QList<QString> ButtonDialog::buttonImageURLs() const
{
    QList<QString> urls;
    Theme theme = Theme("default"); //TODO: Enable different themes

    qDebug() << "buttonImagesURLS() called";
    //Construct selection menu.
    for (auto it = BUTTON_NAMES.begin(); it != BUTTON_NAMES.end(); ++it)
    {
        QString name = it->second;
        ButtonType bt = it->first;
        ButtonTheme buttonTheme = theme.buttonTheme(bt);
        urls.push_back(buttonTheme.imageReleasedURL);
    }
    qDebug() << "urls: " << urls;
    return urls;
}

/**
 * @(#) Remote.h
 */

#ifndef REMOTE_H_H
#define REMOTE_H_H

#include <vector>
#include <memory>
#include <QList>
#include <QGraphicsScene>
#include <QtQuick>
#include <QSettings>
#include "theme.h"
#include "button.h"

//implements remote UI
class Remote: public QQmlComponent
{
    Q_OBJECT

public:
    explicit Remote(QString name, QQmlEngine* engine, QQuickItem *parent = 0);
    explicit Remote();

    //Sets theme for the remote.
    void setTheme(Theme* theme);
    Theme* theme() const;
    //std::vector<ButtonAction> availableButtonsActions() const;
    void addButtonAction(const ButtonAction& newAction);
    //MainWindow* mainWindow() const;
    void addButton(Button* button);   //Sets remote as the owner of the button.
    void saveAndUse();

public slots:
    //Adds new button to the remote.
    void removeButton(Button* button);
    //Creates new button for the remote and returns pointer to it.
    Button* createButton();
    QList<Button*> buttons() const;
    Button* button(int index) const;
    int buttonCount() const;
    //Activates normal mode.
    void useMode();
    void saveSettings();
    //Activates editing mode.
    void editMode();

private:
    static const QString ORGANIZATION;
    static const QString APPLICATION;

    QString name_;
    std::unique_ptr<QSettings> settings_;
    Theme* theme_;
    //MainWindow* mainWindow_;
    QList<Button*> buttons_;
    std::vector<ButtonAction> avaibleButtonActions_;
    //std::vector<Button*> buttons();

    void loadSettings();
};

#endif

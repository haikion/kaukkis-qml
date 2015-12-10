/**
 * @(#) Button.cpp
 */


#include <QDebug>
#include <QtGlobal>
#include <QtQuick>
#include <sailfishapp.h>
#include "button.h"
#include "remote.h"

Button::Button(ButtonType type, ButtonTheme theme, Remote* parent):
    //QQmlComponent(parent), //TODO: Maemo compatibility.     QGraphicsPixmapItem(parent2, scene),
    type_(type),
    remote_(parent),
    x_(1),
    y_(1)
{
    qDebug() << "Created new button";
   // loadUrl(SailfishApp::pathTo("qml/button.qml"));
    setTheme(theme);
    setState("USE");
    //QObject *managObj = create(); //FIXME: Memory leak?
    // QQuickItem* item = qobject_cast<QQuickItem*>(managObj);
    //item->setParentItem(qobject_cast<QQuickItem*>(parent));
    //parent->engine()->rootContext()->setContextProperty("button", this); //TODO: How to make this unique?
   // editMode();
    //scene->addItem(this);
    //buttonDialog_ = std::unique_ptr<ButtonDialog>(new ButtonDialog(this, remote()->mainWindow()));
    //Create right click menu
   // QAction* customizeAction = new QAction("Customize", &contextMenu_);
   // QAction* deleteAction = new QAction("Delete", &contextMenu_);
    //contextMenu_.addAction(customizeAction);
    //contextMenu_.addAction(deleteAction);
   // ButtonDialog* buttonDialog = new ButtonDialog(this, remote()->mainWindow());
    //connect(customizeAction, SIGNAL(triggered()), buttonDialog, SLOT(show()));
    //connect(deleteAction, SIGNAL(triggered()), this, SLOT(removeSelf()));
}

Button::Button():
    type_(ButtonType::BLANK) //Default type
{
    //Exists only to allow qmlRegisterType
    Q_ASSERT_X(false, "Button::Button", "This constructor should never be used");
}

//Sets theme for the image a.k.a changes its image.
void Button::setTheme(const ButtonTheme& theme)
{
    qDebug() << "Theme set";
    theme_ = theme;
    emit imagePressedURLChanged(theme_.imagePressedURL);
    emit imageReleasedURLChanged(theme_.imageReleasedURL);
    //setPixmap(theme_.imageReleased);
}

void Button::setRemote(Remote *remote)
{
    qDebug() << "remote: " << remote;
    remote_= remote;
    remote_->addButton(this);
}

void Button::setType(int type)
{
    type_ = static_cast<ButtonType>(type);
    Theme theme = Theme("default"); //TODO: allow custom themes
    setTheme(theme.buttonTheme(type_));
}

void Button::press()
{
    qDebug() << "Mouse press";

    if (state_ == "USE")
    {
        //Use Mode
        //Perform all press actions
        for ( const ButtonAction& action : buttonActions() )
        {
            action.pressAction->trigger();
        }
    }
}

void Button::release()
{
    qDebug() << "Mouse release";

    if (state_ == "USE")
    {
        //Perform all release actions
        for ( const ButtonAction& action : buttonActions() )
        {
            action.releaseAction->trigger();
        }
    }
}

int Button::x() const
{
    return x_;
}

int Button::y() const
{
    return y_;
}

ButtonType Button::type() const
{
    return type_;
}

//Activates editing mode for the button. Basically makes it movable and allows buttonDialog
void Button::editMode( )
{
    qDebug() << "editMode called";
    setState("EDIT");
}

void Button::useMode()
{
    qDebug() << "useMode() called";
    setState("USE");
}

ButtonType Button::buttonType() const
{
    return type_;
}

QList<ButtonAction> Button::buttonActions() const
{
    return buttonActions_;
}


std::vector<ButtonAction> Button::availbleButtonActions() const
{
    return std::vector<ButtonAction>();
    //return remote()->availableButtonsActions();
}


void Button::setButtonActions(const QList<ButtonAction>& buttonActions)
{
    buttonActions_ = buttonActions;
}


Remote* Button::remote() const
{
    return static_cast<Remote*>(parent());
    //return static_cast<Remote*>(scene());
}

void Button::removeSelf()
{
    qDebug() << "removeSelf called";
    //scene()->removeItem(this);
}

QString Button::state() const
{
    return state_;
}

void Button::setState(const QString& state)
{
    qDebug() << "setState() called";
    if (state != state_)
    {
        state_ = state;
        emit modelStateChanged();
        qDebug() << "stateChanged() emited";
    }
}

void Button::setX(int newVal)
{
    qDebug() << "setX called newVal =" << newVal;
    x_ = newVal;
}

void Button::setY(int newVal)
{
    qDebug() << "setY called newVal =" << newVal;
    y_ = newVal;
}

QString Button::imagePressedURL() const
{
    return theme_.imagePressedURL;
}

QString Button::imageReleasedURL() const
{
    return theme_.imageReleasedURL;
}

//Returns ButtonAction with given pluginName and name. Returns empty buttonAction if
//nothing was found.
ButtonAction Button::findButtonAction(const QString& pluginName, const QString& name) const
{
    qDebug().nospace() << "Searching button action pluginName="
                       << pluginName << " name=" << name;
    for (ButtonAction bt : availbleButtonActions())
    {
        if (bt.pluginName == pluginName && bt.name == name)
        {
            return bt;
        }
    }
    //Return empty buttonAction if nothing was found.
    qDebug() << "Not found";
    return ButtonAction();
}

/*
void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    qDebug() << "Mouse press event";

    if (!editingMode_)
    {
        //Use Mode
        //setPixmap(theme_.imagePressed);
        //Perform all press actions
        for ( const ButtonAction& action : buttonActions() )
        {
            action.pressAction->trigger();
        }
    }
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "Mouse release event";

    if (!editingMode_)
    {
        //setPixmap(theme_.imageReleased);
        //Perform all release actions
        for ( const ButtonAction& action : buttonActions() )
        {
            action.releaseAction->trigger();
        }
    }
    //QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void Button::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    Q_UNUSED(event);
    qDebug() << "Context menu triggered";
    if (editingMode_)
    {
        //contextMenu_.popup(event->screenPos());
    }
}

void Button::saveActionSettings(QSettings* settings)
{
    qDebug() << "saveActionSettings called";
    settings->beginGroup("actions");
    for (int i = 0; i < buttonActions_.size(); ++i)
    {
        settings->beginGroup("action" + QString::number(i));
        ButtonAction bt = buttonActions_.at(i);
        settings->setValue("pluginName", bt.pluginName);
        settings->setValue("name", bt.name);
        settings->endGroup();
    }
    settings->endGroup();
}

void Button::loadActionSettings(QSettings *settings)
{
    qDebug() << "loadActionSettings called. Current group: " << settings->group();
    settings->beginGroup("actions");
    for (QString actionSettings : settings->childGroups())
    {
        settings->beginGroup(actionSettings);
        ButtonAction bt = findButtonAction(settings->value("pluginName").toString(),
                                           settings->value("name").toString());
        if (bt.pluginName != "" && bt.name != "") //Test if anything was found.
        {
            buttonActions_.append(bt);
        }
        settings->endGroup();
    }
    settings->endGroup();
}
*/

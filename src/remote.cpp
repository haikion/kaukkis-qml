/**
 * @(#) Remote.cpp
 */

#include <sailfishapp.h>
#include <QDebug>
#include "remote.h"
#include "buttontype.h"
#include "buttondialog.h"


const QString Remote::ORGANIZATION = "org";
const QString Remote::APPLICATION = "kaukkis";

using namespace std;

Remote::Remote():
    name_("default"),
    theme_(new Theme("default")) //Default value, will be overwritten if settings are found.
{
    qmlRegisterType<Button>("org.kaukkis", 1, 0, "Button");
    qDebug() << "Registered button QML type";
    qmlRegisterType<ButtonDialog>("org.kaukkis",1,0,"ButtonDialogModel");
    qDebug() << "Registered ButtonDialogModel QML type";


    //FIXME: Why this isn't part of the loadSettings() ?
    settings_ = std::unique_ptr<QSettings>(new QSettings(ORGANIZATION, APPLICATION, this));
    settings_->beginGroup(name_);
    loadSettings();
}

void Remote::removeButton(Button* button)
{
    qDebug() << "removeButton called";
    buttons_.removeAll(button);
}

Button* Remote::createButton()
{
    Button* newButton = new Button(ButtonType::BLANK, theme_->buttonTheme(ButtonType::BLANK),  this);
    buttons_.push_back(newButton);
    return newButton;
}

QList<Button *> Remote::buttons() const
{
    return buttons_;
}

Button* Remote::button(int index) const
{
    return buttons_.at(index);
}

int Remote::buttonCount() const
{
    return buttons_.size();
}

//Activates editing mode.
void Remote::editMode( )
{
    qDebug() << "Remote edit";
    //TODO: Change BG?
    for (Button* button : buttons())
    {
        button->editMode();
    }
}


//Sets theme for the remote.
void Remote::setTheme(Theme* theme)
{
    theme_ = theme;
    for (Button* button : buttons())
    {
        button->setTheme(theme_->buttonTheme(button->buttonType()));
    }
}

Theme*Remote::theme() const
{
    return theme_;
}

//Activates normal mode.
void Remote::useMode()
{
    //TODO: Change BG back to normal?
    for (Button* button : buttons())
    {
        button->useMode();
    }
}

//Saves and transfers to use mode
void Remote::saveAndUse()
{
    qDebug() << "saveAndUse() called";
    saveSettings();
    //setSceneRect(itemsBoundingRect());
    useMode();
}

void Remote::addButtonAction(const ButtonAction& newAction)
{
    avaibleButtonActions_.push_back(newAction);
}

void Remote::loadSettings( )
{
    //Test if saves exist
    if (! settings_->contains("theme"))
    {
        qDebug() << "Saves not found!";
        return;
    }

    QString themeName = settings_->value("theme").toString();
    //unique_ptr<Theme> newTheme = std::unique_ptr<Theme>(new Theme(themeName));
    setTheme(new Theme(themeName));

    //Load all buttons for the remote.
    buttons_.clear(); //FIXME: Memory leak!
    for (QString buttonSettings : settings_->childGroups())
    {
        settings_->beginGroup(buttonSettings);
        int posX = settings_->value("positionX").toInt();
        int posY = settings_->value("positionY").toInt();
        ButtonType type = static_cast<ButtonType>(settings_->value("buttonType").toUInt());
        Button* newButton = new Button(type, theme_->buttonTheme(type), this);
        newButton->setX(posX);
        newButton->setY(posY);
        //newButton->loadActionSettings(settings_.get());
        settings_->endGroup();
        buttons_.push_back(newButton);
    }
    qDebug() << "Loaded " << buttons().size()  << " buttons";
}

void Remote::saveSettings( )
{
    qDebug() << "Saving " << buttons().size() << " buttons.";
    //Clear old settings
    settings_->clear();

    settings_->setValue("theme", theme_->name());
    for (int i = 0; i < buttons().size(); ++i )
    {
        Button* button = buttons().at(i);
        //Buttons don't have unique name so name them.
        //TODO: Consider moving button centric saves to button class.
        QString name = "button" + QString::number(i);
        settings_->beginGroup(name);
        settings_->setValue("positionX", button->x());
        settings_->setValue("positionY", button->y());
        settings_->setValue("buttonType", static_cast<unsigned>(button->buttonType()));
        //button->saveActionSettings(settings_.get());
        settings_->endGroup();
    }
    settings_->sync();
    qDebug() << "Saved settings to file: " << settings_->fileName();
}

void Remote::addButton(Button *button)
{
    qDebug() << "Add Button called";
    button->setTheme(theme_->buttonTheme(button->type()));
}

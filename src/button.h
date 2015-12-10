/**
 * @(#) Button.h
 */

#ifndef BUTTON_H_H
#define BUTTON_H_H

#include <vector>
#include <QQuickItem>
#include "theme.h"
#include "buttondialog.h"
#include "buttonaction.h"
#include "buttontype.h"

class Remote;

//Implements remote button.
class Button: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX)
    Q_PROPERTY(int y READ y WRITE setY)
    Q_PROPERTY(QString imagePressedURL READ imagePressedURL NOTIFY imagePressedURLChanged)
    Q_PROPERTY(QString imageReleasedURL READ imageReleasedURL NOTIFY imageReleasedURLChanged)
    Q_PROPERTY(QString modelState READ state() WRITE setState() NOTIFY modelStateChanged)

    //Q_PROPERTY(Remote* remote WRITE setRemote)

public:
    Button(ButtonType type, ButtonTheme theme , Remote *parent);
    //Button(ButtonType type, ButtonTheme theme);
    Button();

    //Activates editing mode for the button.
    //Basically makes it movable and allows buttonDialog
    void editMode();
    void useMode();
    ButtonType buttonType() const;
    QList<ButtonAction> buttonActions() const;
    void setButtonActions(const QList<ButtonAction>& buttonActions);
    std::vector<ButtonAction> availbleButtonActions() const;

    void setX(int newVal);
    void setY(int newVal);
    //These functions are called when the settings is handling this button
    //in order to load active actions.
    //void saveActionSettings(QSettings* settings);
   // void loadActionSettings(QSettings* settings);
    ButtonType type() const;
    QString state() const;
    void setState(const QString& state);

//protected:
    //virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
    //virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    //virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

public slots:
    QString imagePressedURL() const;
    QString imageReleasedURL() const;
    //Sets theme for the image a.k.a changes its image.
    void setTheme(const ButtonTheme& theme);
    void setRemote(Remote *remote);
    void setType(int type);
    //QML doesn't recognize enum class hence int instead of ButtonType
    void press();
    void release();
    int x() const;
    int y() const;
    void removeSelf(); //Removes button from the remote Model

signals:
    void modelStateChanged();
    void imagePressedURLChanged(QString newVal);
    void imageReleasedURLChanged(QString newVal);

private:
    QList<ButtonAction> buttonActions_;
    ButtonType type_;
    ButtonTheme theme_;
    //True if edit mode is active
    //bool editingMode_;
    QString state_;
    Remote* remote_;
    int x_;
    int y_;
    //QMenu contextMenu_;
    //std::unique_ptr<ButtonDialog> buttonDialog_;

    Remote* remote() const;
    //Returns ButtonAction with given pluginName and name. Returns empty buttonAction if
    //nothing was found.
    ButtonAction findButtonAction(const QString& pluginName, const QString& name) const;
};

#endif


#include "buttonitem.h"

ButtonItem::ButtonItem(const QString& buttonName, const QString& imagePath, QObject *parent) :
    QObject(parent)
{
    buttonName_ = buttonName;
    imagePath_ = imagePath;
}

QString ButtonItem::buttonName() const
{
    return buttonName_;
}

QString ButtonItem::imagePath() const
{
    return imagePath_;
}

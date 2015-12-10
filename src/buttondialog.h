/**
 * @(#) ButtonDialog.h
 */

#ifndef BUTTONDIALOG_H_H
#define BUTTONDIALOG_H_H

#include <QList>
#include <QString>
#include <QtQuick>
#include "button.h"
#include "buttonaction.h"
#include "buttontype.h"

class Button;

//Dialog for editing a button.
class ButtonDialog: public QObject
{
    Q_OBJECT

public:
    ButtonDialog();
    ButtonDialog(QQuickView* view);
    //Ui::ButtonDialog* ui;

private:
    //Button* parent_;
    //std::vector<ButtonAction> availableActions_;
public slots:
    //void accepted();
    //void show();
    QList<QString> buttonImageURLs() const;
};

#endif

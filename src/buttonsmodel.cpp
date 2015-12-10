/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QDebug>
#include "buttonsmodel.h"
#include "theme.h"

ButtonsModel::ButtonsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Theme theme = Theme("default"); //TODO: Enable different themes

    qDebug() << "ButtonsModel() called view";
    //Construct selection menu.
    for (auto it = BUTTON_NAMES.begin(); it != BUTTON_NAMES.end(); ++it)
    {
        ButtonDemo button;
        button.type  = it->first;
        ButtonTheme buttonTheme = theme.buttonTheme(button.type);
        button.imagePath = buttonTheme.imageReleasedURL;
        addButton(button);
    }
    qDebug() << "m_buttons size: " << m_buttons.size();
}

void ButtonsModel::addButton(const ButtonDemo& button)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_buttons << button;
    endInsertRows();
}

int ButtonsModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_buttons.count();
}

QVariant ButtonsModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_buttons.count())
        return QVariant();

    const ButtonDemo& button = m_buttons[index.row()];
    if (role == NameRole)
        return static_cast<int>(button.type);
    else if (role == PathRole)
        return button.imagePath;
    return QVariant();
}

//![0]
QHash<int, QByteArray> ButtonsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "type";
    roles[PathRole] = "imagePath";
    return roles;
}
//![0]


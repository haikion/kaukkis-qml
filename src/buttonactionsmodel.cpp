#include "buttonactionsmodel.h"

ButtonActionsModel::ButtonActionsModel(QObject *parent, PluginHandler* pluginHandler) :
        QAbstractListModel(parent), pluginHandler_(pluginHandler)
{
    //Build index of plugins
    for (IRemoteOutput* output : pluginHandler_->plugins() )
    {
        qDebug() << "Processing plugin: " << output->name();
        for (ButtonAction action : output->buttonActions())
        {
            buttonActions_.push_back(action);
        }
    }
}

void ButtonActionsModel::setButtonModel(Button *button)
{
    button_ = button;
}

//TODO: Add button ptr
void ButtonActionsModel::setButtonAction(Button* button, int index)
{
    qDebug() << "Selecting button action with index: " << index << "button: " << button;
    if (index > 0 && index < buttonActions_.count())
    {
        QList<ButtonAction> buttonActions;
        buttonActions.push_back(buttonActions_.at(index));
        button->setButtonActions(buttonActions);
        qDebug() << "Button action set";
    }
}

QVariant ButtonActionsModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= buttonActions_.count())
        return QVariant();

    ButtonAction bt = buttonActions_[index.row()];
    if (role == NameRole)
        return QString(bt.pluginName + " / " + bt.name);
    return QVariant();
}

QHash<int, QByteArray> ButtonActionsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

int ButtonActionsModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return buttonActions_.count();
}


/*
void RemoteOutputsModel::show()
{
    ui->listWidget->clear();

    for (IRemoteOutput* output : parent_->remoteOutputs() )
    {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setText(output->name());
        item->setData(Qt::UserRole, qVariantFromValue((void*) output));
        ui->listWidget->addItem(item);
    }

    QWidget::show();
}
*/

#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include <QObject>

class ButtonItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString buttonName READ buttonName)
    Q_PROPERTY(QString imagePath READ imagePath)
public:
    explicit ButtonItem(const QString& buttonName, const QString& imagePath, QObject *parent = 0);

signals:

public slots:
    QString buttonName() const;
    QString imagePath() const;

private:
    QString buttonName_;
    QString imagePath_;
};

#endif // BUTTONITEM_H

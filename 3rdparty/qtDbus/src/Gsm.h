#ifndef GSM_H
#define GSM_H

#include <QObject>
#include <QVariant>

class Gsm : public QObject
{
Q_OBJECT
public:
    explicit Gsm(QObject *parent = 0);

    void popup();

private:
    QList<QVariant> Notify(const QString &app_name, uint id, const QString &icon, const QString &summary, const QString &body, const QStringList &actions, const QVariantMap &hints, qint32 timeout);

signals:

public slots:

};

#endif // GSM_H

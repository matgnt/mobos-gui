#include "Gsm.h"
#include <QtCore/QDebug>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>

Gsm::Gsm(QObject *parent) :
    QObject(parent)
{
}

void Gsm::popup()
{
    QDBusInterface interface("org.freedesktop.Notifications",
                                "/org/freedesktop/Notifications",
                                "org.freedesktop.Notifications");

    if(!interface.isValid()) {
        qDebug() << interface.lastError();
        return;
    }

    QStringList actions;
    QVariantMap hints;
    QList<QVariant> argumentList = Notify(NULL, 0, NULL, QString("MyPopup"), QString("MyPopup Text"), actions, hints, qint32(5000));
    QDBusReply<uint> reply = interface.callWithArgumentList(QDBus::AutoDetect, QLatin1String("Notify"), argumentList);

    if(reply == QDBusMessage::InvalidMessage) {
        qDebug() << "reply: " << reply.error();
    } else {
        //
    }

}

QList<QVariant> Gsm::Notify(const QString &app_name, uint id, const QString &icon, const QString &summary, const QString &body, const QStringList &actions, const QVariantMap &hints, qint32 timeout)
{
       QList<QVariant> argumentList;
       argumentList << qVariantFromValue(app_name) << qVariantFromValue(id) << qVariantFromValue(icon) << qVariantFromValue(summary) << qVariantFromValue(body) << qVariantFromValue(actions) << qVariantFromValue(hints) << qVariantFromValue(timeout);
       return argumentList;
}

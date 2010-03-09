#include "Gsm.h"
#include <QtCore/QDebug>
#include <QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>

#include "dbus/OfonoProxy.h"
#include "dbus/NotificationsProxy.h"

Gsm::Gsm(QObject *parent) :
    QObject(parent)
{
}

void Gsm::popup()
{
    QStringList actions;
    QVariantMap hints;

    OrgFreedesktopNotificationsInterface* notify = new OrgFreedesktopNotificationsInterface("org.freedesktop.Notifications", "/org/freedesktop/Notifications", QDBusConnection::sessionBus ());

    notify->Notify(NULL, 0, NULL, "MyPopupSummary", "MyPopupBody", actions, hints, qint32(5000));

}

void Gsm::setPowerOn() {
    OrgOfonoModemInterface* ofono = new OrgOfonoModemInterface("org.ofono", "/phonesim", QDBusConnection::systemBus());
    ofono->SetProperty("Powered", QDBusVariant(true));

}

void Gsm::setPowerOff() {
    OrgOfonoModemInterface* ofono = new OrgOfonoModemInterface("org.ofono", "/phonesim", QDBusConnection::systemBus());
    ofono->SetProperty("Powered", QDBusVariant(false));

}

#include "Gsm.h"
#include <QtCore/QDebug>
#include <QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>

#include "dbus/OfonoModem.h"

Gsm::Gsm(QObject *parent) :
    QObject(parent)
{
}

void Gsm::setPowerOn() {
    OrgOfonoModemInterface* ofono = new OrgOfonoModemInterface("org.ofono", "/phonesim", QDBusConnection::systemBus());
    ofono->SetProperty("Powered", QDBusVariant(true));

}

void Gsm::setPowerOff() {
    OrgOfonoModemInterface* ofono = new OrgOfonoModemInterface("org.ofono", "/phonesim", QDBusConnection::systemBus());
    ofono->SetProperty("Powered", QDBusVariant(false));

}

//QML_DEFINE_TYPE(Gsm, 1,0, Gsm, Gsm);

#include "Gsm.h"
#include <QtCore/QDebug>
#include <QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>

#include "dbus/OfonoModem.h"
#include "dbus/OfonoVoiceCallManager.h"

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

void Gsm::dial(QString number)
{
    OrgOfonoVoiceCallManagerInterface* ofono = new OrgOfonoVoiceCallManagerInterface("org.ofono", "/phonesim", QDBusConnection::systemBus());
    qDebug() << "Dial number: " << number;
    ofono->Dial(number, "default");
}

//QML_DEFINE_TYPE(Gsm, 1,0, Gsm, Gsm);

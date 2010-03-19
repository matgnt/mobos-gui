#ifndef OFONO_H
#define OFONO_H

#include <QObject>
#include <QtDeclarative/qdeclarative.h>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>

#include "dbus/OfonoModem.h"
#include "dbus/OfonoVoiceCallManager.h"
#include "voicecalls.h"

#define OFONO_MODEM_OBJECT_PATH "/phonesim"


class Ofono : public QObject
{
Q_OBJECT
Q_PROPERTY(QString waitingNumber READ getWaitingNumber NOTIFY waitingCallChanged)

public:
    Ofono(QObject *parent = 0);
    ~Ofono();

    QString getWaitingNumber();

private:

signals:
    void callsChanged();

public slots:
    void setPowerOn();
    void setPowerOff();
    void dial(QString number);

    // incoming DBus signals
    void PropertyChanged(const QString &name, const QDBusVariant &value);

private:
    OrgOfonoVoiceCallManagerInterface* m_VoiceCallManager;
    QString m_waitingNumber;
    VoiceCalls m_voiceCalls;

};

QML_DECLARE_TYPE(Ofono);

#endif // OFONO_H

#ifndef GSM_H
#define GSM_H

#include <QObject>
#include <QtDeclarative/qdeclarative.h>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusArgument>

#include "dbus/OfonoModem.h"
#include "dbus/OfonoVoiceCallManager.h"
#include "voicecalls.h"

#define OFONO_MODEM_OBJECT_PATH "/phonesim"


class Gsm : public QObject
{
Q_OBJECT
Q_PROPERTY(QString waitingNumber READ getWaitingNumber NOTIFY waitingCallChanged)

public:
    Gsm(QObject *parent = 0);
    ~Gsm();

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

QML_DECLARE_TYPE(Gsm);

#endif // GSM_H

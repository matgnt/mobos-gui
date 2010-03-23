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
#define OFONO_STATE_INCOMING "incoming"
#define OFONO_STATE_OUTGOING "dialing"


class Ofono : public QObject
{
Q_OBJECT
//Q_PROPERTY(QString waitingNumber READ getWaitingNumber NOTIFY waitingCallChanged)

public:
    Ofono(QObject *parent = 0);
    ~Ofono();

    QString getWaitingNumber();
    static VoiceCallState translateState(QString);

private:

signals:
    void callsChanged();
    void incomingCall(QString number, QString voicecallId);
    void outgoingCall(QString number, QString voicecallId);

public slots:
    // methods, but listed as slots to execute them from QML
    void setPowerOn();
    void setPowerOff();
    void dial(QString number);
    void answerCall(QString id);
    void hangupCall(QString id);

    // incoming DBus signals
    void PropertyChanged(const QString &name, const QDBusVariant &value);

    // slots to process internal signals to emit simpler signals for QML
    void processChangedCalls();

private:
    OrgOfonoVoiceCallManagerInterface* m_VoiceCallManager;
    QString m_waitingNumber;
    VoiceCalls m_voiceCalls;

};

//QML_DECLARE_TYPE(Ofono);

#endif // OFONO_H

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
#define OFONO_STATE_HELD "held"
#define OFONO_STATE_ALERTING "alerting"
#define OFONO_STATE_ACTIVE "active"
#define OFONO_STATE_DISCONNECTED "disconnected"

/**
 * \brief
 * Connection class to all the DBus-Proxies.
 */
class Ofono : public QObject
{
Q_OBJECT
//Q_PROPERTY(QString waitingNumber READ getWaitingNumber NOTIFY waitingCallChanged)

public:
    Ofono(QObject *parent = 0);
    ~Ofono();

    QString getWaitingNumber();
    /**
     * Just map the oFono call states to the c++ state enum
     * If there is no matching state, it returns the enum state NONE (0)
     */
    static VoiceCallState translateState(QString);

private:

signals:
	/**
	 * Emited whenever oFono DBus sends "Calls".
	 * The list of current calls changed.
	 * Used internally to emit either incomingCall() or outgoingCall()
	 */
    void callsChanged();
	/**
	 * Emited whenever an incoming call is announced via oFono DBus.
	 */
    void incomingCall(QString id);
    /**
     * Emited whenever an outgoing call is announced via oFono DBus.
     */
    void outgoingCall(QString id);

    void acceptedCall(QString id);
    void disconnectedCall(QString id);

public slots:
    /**
     * Slot for incoming DBus oFono signals
     */
    void PropertyChanged(const QString &name, const QDBusVariant &value);

    /**
     * Slot to process internal signals to emit simpler signals for QML
     */
    void processChangedCalls();

public:
    /**
     * Set the oFono "powered" property to "true"
     */
    Q_INVOKABLE void setPowerOn();
    /**
     * Set the oFono "powered" property to "false"
     */
    Q_INVOKABLE void setPowerOff();
    /**
     * DBus VoiceCallManager.Dial
     * @param number The number to dial.
     */
    Q_INVOKABLE void dial(QString number);
    /**
     * @param id DBus VoiceCall Object Path
     */
    Q_INVOKABLE void answerCall(QString id);
    /**
     * @param id DBus VoiceCall Object Path
     */
    Q_INVOKABLE void hangupCall(QString id);
    /**
     * @param id The Call-ID which is the voicecall object path
     * @return The phone number for the Call-ID
     */
    Q_INVOKABLE QString getPhoneNumber(QString id);

private:
    OrgOfonoVoiceCallManagerInterface* m_VoiceCallManager;
    QString m_waitingNumber;
    /**
     * Updated list of all the current VoiceCalls in the system.
     */
    VoiceCalls m_voiceCalls;

    VoiceCall* getCall(QString id);

};

//QML_DECLARE_TYPE(Ofono);

#endif // OFONO_H

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
    void incomingCall(QString number, QString voicecallId);
    /**
     * Emited whenever an outgoing call is announced via oFono DBus.
     */
    void outgoingCall(QString number, QString voicecallId);

public slots:
    // methods, but listed as slots to execute them from QML
	/**
	 * To be executed from QML.
	 * Set the oFono "powered" property to "true"
	 */
    void setPowerOn();
	/**
	 * To be executed from QML.
	 * Set the oFono "powered" property to "false"
	 */
    void setPowerOff();
    /**
     * To be executed from QML.
     * DBus VoiceCallManager.Dial
     * @param number The number to dial.
     */
    void dial(QString number);
    /**
     * To be executed from QML.
     * @param id DBus VoiceCall Object Path
     */
    void answerCall(QString id);
    /**
     * To be executed from QML.
     * @param id DBus VoiceCall Object Path
     */
    void hangupCall(QString id);


    /**
     * Slot for incoming DBus oFono signals
     */
    void PropertyChanged(const QString &name, const QDBusVariant &value);

    /**
     * Slot to process internal signals to emit simpler signals for QML
     */
    void processChangedCalls();

private:
    OrgOfonoVoiceCallManagerInterface* m_VoiceCallManager;
    QString m_waitingNumber;
    /**
     * Updated list of all the current VoiceCalls in the system.
     */
    VoiceCalls m_voiceCalls;

};

//QML_DECLARE_TYPE(Ofono);

#endif // OFONO_H

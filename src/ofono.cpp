#include "ofono.h"
#include "dbus/OfonoVoiceCall.h"
#include <QtCore/QDebug>
#include <QDBusConnection>

Ofono::Ofono(QObject *parent) :
    QObject(parent)
{
    m_VoiceCallManager = new OrgOfonoVoiceCallManagerInterface("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());

    // DBus signals
    connect(m_VoiceCallManager, SIGNAL(PropertyChanged(const QString, const QDBusVariant)), this, SLOT(PropertyChanged(const QString, const QDBusVariant)));

    // connect the process slots
    connect(this, SIGNAL(callsChanged()), this, SLOT(processChangedCalls()));

}

void Ofono::setPowerOn() {
    OrgOfonoModemInterface ofono("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());
    ofono.SetProperty("Powered", QDBusVariant(true));
}

void Ofono::setPowerOff() {
    OrgOfonoModemInterface* ofono = new OrgOfonoModemInterface("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());
    ofono->SetProperty("Powered", QDBusVariant(false));

}

void Ofono::dial(QString number)
{
    OrgOfonoVoiceCallManagerInterface* ofono = new OrgOfonoVoiceCallManagerInterface("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());
    qDebug() << "Dial number: " << number;
    ofono->Dial(number, "default");
}

void Ofono::processChangedCalls()
{
    QListIterator<VoiceCall> itr(m_voiceCalls);
    while(itr.hasNext()) {
        VoiceCall call = itr.next();
        VoiceCallState state = call.getState();
        switch (state)
        {
            case INCOMING:
                emit incomingCall(call.getNumber(), call.getId());
                break;
            case OUTGOING:
                emit outgoingCall(call.getNumber(), call.getId());
                break;
        }
    }
}

void Ofono::answerCall(QString id)
{
    OrgOfonoVoiceCallInterface voicecall("org.ofono", id, QDBusConnection::systemBus());
    voicecall.Answer();
}
void Ofono::hangupCall(QString id)
{
    OrgOfonoVoiceCallInterface voicecall("org.ofono", id, QDBusConnection::systemBus());
    voicecall.Hangup();
}

void Ofono::PropertyChanged(const QString &name, const QDBusVariant &value)
{
    qDebug() << name;
    if(name == "Calls") {

        const QVariant var = value.variant();
        const QDBusArgument arg = var.value<QDBusArgument>();
        VoiceCalls calls;
        arg >> calls;

        qDebug() << calls;
        m_voiceCalls = calls;
        emit callsChanged();

    }
}

QString Ofono::getWaitingNumber()
{
    return "55555";
}

/*
 * Map the QDbusArgument for one call to the corresponding Qt type VoiceCall.
 */
const QDBusArgument &operator>>(const QDBusArgument &a, VoiceCall &voicecall) {
    QDBusObjectPath opath;
    a >> opath;

    // get call properties
    QString path = opath.path();
    qDebug() << path;
    OrgOfonoVoiceCallInterface ofono("org.ofono", path, QDBusConnection::systemBus());
    QDBusPendingReply<QVariantMap> reply = ofono.GetProperties();
    //QDBusPendingReply<> reply = ofono.Answer();
    reply.waitForFinished();
    if(reply.isValid()) {
        qDebug() << "count: " << reply.count();
        QVariantMap val = reply.value();
        qDebug() << val;
        QString nr = val["LineIdentification"].toString();
        QString stateVal = val["State"].toString();
        VoiceCallState state = Ofono::translateState(stateVal);

        //m_waitingNumber = nr.toString();
        //emit waitingCallChanged();
        VoiceCall vc(path, nr, state);
        voicecall = vc;

    } else {
        qDebug() << "Invalid reply: " << reply.error().message();
    }


    return a;
}

/*
 * Just map the oFono call states to the c++ state enum
 * If there is no matching state, it returns the enum state NONE (0)
 */
VoiceCallState Ofono::translateState(QString state)
{
    if(state == OFONO_STATE_INCOMING) {
        return INCOMING;
    } else if(state == OFONO_STATE_OUTGOING) {
        return OUTGOING;
    } else {
        return NONE;
    }
}

Ofono::~Ofono()
{
	delete m_VoiceCallManager;
}
//QML_DEFINE_TYPE(Ofono, 1,0, Ofono, Ofono);

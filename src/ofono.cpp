#include "ofono.h"
#include "dbus/OfonoVoiceCall.h"
#include <QtCore/QDebug>
#include <QDBusConnection>
#include "voicecallupdaterofono.h"

Ofono::Ofono(QObject *parent) :
    QObject(parent)
{
    m_VoiceCallManager = new OrgOfonoVoiceCallManagerInterface("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());

    // DBus signals
    connect(m_VoiceCallManager, SIGNAL(PropertyChanged(const QString, const QDBusVariant)), this, SLOT(PropertyChanged(const QString, const QDBusVariant)));

    // connect the process slots
    connect(this, SIGNAL(callsChanged(VoiceCalls)), this, SLOT(processChangedCalls(VoiceCalls)));

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

//void Ofono::processChangedCalls(VoiceCalls calls)
//{

//    VoiceCalls old_calls = m_voiceCalls;

//    // update our local calls
//    m_voiceCalls = calls;

//    // go through the list of the current calls and compare it with our old calls
//    QListIterator<VoiceCall> itr(m_voiceCalls);
//    while(itr.hasNext()) {
//        VoiceCall call = itr.next();

//        VoiceCall* c = old_calls.getCall(call.getId());
//        if(c) {
//            // emit signal only if the state has changed
//            if(c->getState() != call.getState()) {
//                emitCallState(call);
//            }

//        } else {
//            // there was no corresponding call, therefore emit the state anyway
//            emitCallState(call);
//        }

//    }
//}

void Ofono::emitCallState(const VoiceCall* call)
{
    VoiceCallState state = call->getState();
    switch (state)
    {
    case INCOMING:
            emit incomingCall(call->getId());
            break;
    case OUTGOING:
            emit outgoingCall(call->getId());
            break;
    case HELD:
            emit heldCall(call->getId());
            break;
    case ALERTING:
            emit alertingCall(call->getId());
            break;
    case ACTIVE:
            emit activeCall(call->getId());
            break;
    case DISCONNECTED:
            emit disconnectedCall(call->getId());
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
        const QDBusArgument a = var.value<QDBusArgument>();

        VoiceCalls calls;
        calls.empty();

        a.beginArray();
        while(!a.atEnd()) {
            QDBusObjectPath opath;
            a >> opath;
            VoiceCallUpdaterOfono* ofonoCall = new VoiceCallUpdaterOfono(opath.path());
            VoiceCall* vc = new VoiceCall(ofonoCall);
            connect(vc, SIGNAL(update(const VoiceCall*)), this, SLOT(processCallUpdate(const VoiceCall*)));
            calls.append(vc);
        }
        a.endArray();

        qDebug() << calls;
        //emit callsChanged(calls);
        m_voiceCalls = calls;

    }
}

void Ofono::processCallUpdate(const VoiceCall* call)
{
    emitCallState(call);
}

QString Ofono::getWaitingNumber()
{
    return "55555";
}

QString Ofono::getPhoneNumber(QString id)
{
    VoiceCall* call = m_voiceCalls.getCall(id);
    if(call) {
        QString number = call->getNumber();
        return number;
    }
    return "0";
}


/*
 * Map the QDbusArgument for one call to the corresponding Qt type VoiceCall.
 */
//const QDBusArgument &operator>>(const QDBusArgument &a, VoiceCall &voicecall) {
//    QDBusObjectPath opath;
//    a >> opath;

//    // get call properties
//    QString path = opath.path();
//    qDebug() << path;
//    // move to VoiceCallUpdaterOfono
//    OrgOfonoVoiceCallInterface ofono("org.ofono", path, QDBusConnection::systemBus());
//    QDBusPendingReply<QVariantMap> reply = ofono.GetProperties();
//    //QDBusPendingReply<> reply = ofono.Answer();
//    reply.waitForFinished();
//    if(reply.isValid()) {
//        qDebug() << "count: " << reply.count();
//        QVariantMap val = reply.value();
//        qDebug() << val;
//        QString nr = val["LineIdentification"].toString();
//        QString stateVal = val["State"].toString();
//        VoiceCallState state = Ofono::translateState(stateVal);

//        //m_waitingNumber = nr.toString();
//        //emit waitingCallChanged();
//        VoiceCall vc(path, nr, state);
//        voicecall = vc;

//    } else {
//        qDebug() << "Invalid reply: " << reply.error().message();
//    }
//    // move end

//    return a;
//}

VoiceCallState Ofono::translateState(QString state)
{
    if(state == OFONO_STATE_INCOMING) {
        return INCOMING;
    } else if(state == OFONO_STATE_OUTGOING) {
        return OUTGOING;
    } else if(state == OFONO_STATE_HELD) {
        return HELD;
    } else if(state == OFONO_STATE_ALERTING) {
        return ALERTING;
    } else if(state == OFONO_STATE_ACTIVE) {
        return ACTIVE;
    } else if(state == OFONO_STATE_DISCONNECTED) {
        return DISCONNECTED;
    } else {
        return NONE;
    }
}

Ofono::~Ofono()
{
	delete m_VoiceCallManager;
}
//QML_DEFINE_TYPE(Ofono, 1,0, Ofono, Ofono);

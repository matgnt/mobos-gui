#include "Gsm.h"
#include "dbus/OfonoVoiceCall.h"
#include <QtCore/QDebug>
#include <QDBusConnection>

Gsm::Gsm(QObject *parent) :
    QObject(parent)
{
    m_VoiceCallManager = new OrgOfonoVoiceCallManagerInterface("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());
	// DBus signals
	connect(m_VoiceCallManager, SIGNAL(PropertyChanged(const QString, const QDBusVariant)), this, SLOT(PropertyChanged(const QString, const QDBusVariant)));

}

void Gsm::setPowerOn() {
    OrgOfonoModemInterface ofono("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());
    ofono.SetProperty("Powered", QDBusVariant(true));
}

void Gsm::setPowerOff() {
    OrgOfonoModemInterface* ofono = new OrgOfonoModemInterface("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());
    ofono->SetProperty("Powered", QDBusVariant(false));

}

void Gsm::dial(QString number)
{
    OrgOfonoVoiceCallManagerInterface* ofono = new OrgOfonoVoiceCallManagerInterface("org.ofono", OFONO_MODEM_OBJECT_PATH, QDBusConnection::systemBus());
    qDebug() << "Dial number: " << number;
    ofono->Dial(number, "default");
}

void Gsm::PropertyChanged(const QString &name, const QDBusVariant &value)
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

QString Gsm::getWaitingNumber()
{
    return "55555";
}

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
        QVariant nr = val["LineIdentification"];

        //m_waitingNumber = nr.toString();
        //emit waitingCallChanged();
        VoiceCall vc(path, nr.toString(), NONE); // TODO: fix state
        voicecall = vc;

    } else {
        qDebug() << "Invalid reply: " << reply.error().message();
    }


    return a;
}

/*
 * Map the QDbusArgument for "Calls" Property to the corresponding Qt typ.
 * In DBus it is an array of object pathes.
 */
const QDBusArgument &operator>>(const QDBusArgument &a,  VoiceCalls &calls) {
    calls.empty();

    a.beginArray();
    while(!a.atEnd()) {
        QDBusObjectPath opath;
        a >> opath;
        //calls.append(opath.path());

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
            QVariant nr = val["LineIdentification"];

            //m_waitingNumber = nr.toString();
            //emit waitingCallChanged();
            VoiceCall vc(path, nr.toString(), NONE); // TODO: fix state
            calls.append(vc);

        } else {
            qDebug() << "Invalid reply: " << reply.error().message();
        }

    }
    a.endArray();

    return a;
}

Gsm::~Gsm()
{
	delete m_VoiceCallManager;
}
//QML_DEFINE_TYPE(Gsm, 1,0, Gsm, Gsm);

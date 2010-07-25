#include "voicecallupdaterofono.h"
#include "dbus/OfonoVoiceCall.h"
#include "ofono.h"

VoiceCallUpdaterOfono::VoiceCallUpdaterOfono(QString call_object_path) :
        VoiceCallUpdaterIF(call_object_path),
        m_VoiceCall("org.ofono", call_object_path, QDBusConnection::systemBus())
{

    // connect the PropertyChanged signal from D-Bus
    connect(&m_VoiceCall, SIGNAL(PropertyChanged(const QString, const QDBusVariant)), this, SLOT(PropertyChanged(const QString, const QDBusVariant)));

     //get the number
        QDBusPendingReply<QVariantMap> reply = m_VoiceCall.GetProperties();
        reply.waitForFinished();
        if(reply.isValid()) {
            //qDebug() << "count: " << reply.count();
            QVariantMap val = reply.value();
            //qDebug() << val;
            m_number = val["LineIdentification"].toString();

        } else {
            qDebug() << "Invalid reply: " << reply.error().message();
        }

}

void VoiceCallUpdaterOfono::PropertyChanged(const QString property, const QDBusVariant value)
{
    qDebug() << "VoiceCallUpdaterOfono::PropertyChanged" << property;

    if(property == "State") {
        const QVariant var = value.variant();
        qDebug() << "VoiceCallUpdaterOfono::PropertyChanged var: " << var.toString();
        m_state = Ofono::translateState(var.toString());

        emit VoiceCallUpdaterIF::update();

    } else {
        qDebug() << "VoiceCallUpdaterOfono::PropertyChanged: No handling for property implemented: " << property;
    }

}

VoiceCallUpdaterOfono::~VoiceCallUpdaterOfono()
{
    qDebug() << "VoiceCallUpdaterOfono::~VoiceCallUpdaterOfono()";
}

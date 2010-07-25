#ifndef VOICECALLUPDATEROFONO_H
#define VOICECALLUPDATEROFONO_H

#include <QObject>
#include <QString>
#include "voicecall.h"
#include "voicecallupdaterif.h"
#include "dbus/OfonoVoiceCall.h"

class VoiceCallUpdaterOfono : public VoiceCallUpdaterIF
{
Q_OBJECT

public:
    VoiceCallUpdaterOfono(QString);
    ~VoiceCallUpdaterOfono();

public slots:
    virtual void PropertyChanged(const QString property, const QDBusVariant value);

private:
    OrgOfonoVoiceCallInterface m_VoiceCall;

};

#endif // VOICECALLUPDATEROFONO_H

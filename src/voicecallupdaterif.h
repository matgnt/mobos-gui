#ifndef VOICECALLUPDATERIF_H
#define VOICECALLUPDATERIF_H

#include "VoiceCallStateEnum.h"
#include <QString>
#include <QObject>
#include <QDBusVariant>

class VoiceCallUpdaterIF : public QObject
{
Q_OBJECT

public:
    VoiceCallUpdaterIF(QString id);
    //VoiceCallUpdaterIF(const VoiceCallUpdaterIF&){}
    virtual VoiceCallState getState();
    virtual QString getNumber();
    virtual QString getId();

signals:
    /**
     * Inform that there are updates available.
     */
    void update();

protected:
    VoiceCallState m_state;
    QString m_number;
    QString m_id;

};

#endif // VOICECALLUPDATERIF_H

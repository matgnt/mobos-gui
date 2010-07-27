#ifndef VOICECALLS_H
#define VOICECALLS_H

#include "voicecall.h"
#include <QObject>
#include <QList>

/**
 * \brief
 * A list of VoiceCall
 */
class VoiceCalls : public QObject
{
Q_OBJECT

public:
    VoiceCalls();
    VoiceCalls(const QList<VoiceCall*> voicecalls);
    ~VoiceCalls() {}
    VoiceCall* getCall(QString id);
    //QDebug operator<<(QDebug, const VoiceCalls);
    void append(VoiceCall* voiceCall);
    bool empty() const;


signals:
    void update(VoiceCall* voiceCall);

public slots:
    void processCallUpdate(VoiceCall* voiceCall);

private:
    QList<VoiceCall*> m_VoiceCalls;

};

#endif // VOICECALLS_H

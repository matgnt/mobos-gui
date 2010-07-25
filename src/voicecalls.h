#ifndef VOICECALLS_H
#define VOICECALLS_H

#include "voicecall.h"
#include <QList>

/**
 * \brief
 * A list of VoiceCall
 */
class VoiceCalls : public QList<VoiceCall*>
{

public:
    VoiceCalls() {}
    VoiceCalls(const QList<VoiceCall*> voicecalls);
    ~VoiceCalls() {}
    VoiceCall* getCall(QString id);
    //QDebug operator<<(QDebug, const VoiceCalls);


signals:

public slots:

};

#endif // VOICECALLS_H

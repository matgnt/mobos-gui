#ifndef VOICECALLS_H
#define VOICECALLS_H

#include "voicecall.h"
#include <QList>

/**
 * \brief
 * A list of VoiceCall
 */
class VoiceCalls : public QList<VoiceCall>
{

public:
    VoiceCalls() {}
    VoiceCalls(const QList<VoiceCall> &voicecalls);
    ~VoiceCalls() {}
    //QDebug operator<<(QDebug, const VoiceCalls);

signals:

public slots:

};

#endif // VOICECALLS_H

#include "voicecalls.h"

VoiceCalls::VoiceCalls(const QList<VoiceCall*> voicecalls)
    : QList<VoiceCall*>(voicecalls)
{
}

VoiceCall* VoiceCalls::getCall(QString id)
{
    QListIterator<VoiceCall*> itr(*this);
    while(itr.hasNext()) {
        VoiceCall* call = itr.next();
        if(call->getId() == id) {
            return call;
        }
    }
    return 0;
}


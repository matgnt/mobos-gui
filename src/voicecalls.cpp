#include "voicecalls.h"

VoiceCalls::VoiceCalls()
{
}

VoiceCalls::VoiceCalls(const QList<VoiceCall*> voicecalls)
    : m_VoiceCalls(voicecalls)
{
}

VoiceCall* VoiceCalls::getCall(QString id)
{
    QListIterator<VoiceCall*> itr(m_VoiceCalls);
    while(itr.hasNext()) {
        VoiceCall* call = itr.next();
        if(call->getId() == id) {
            return call;
        }
    }
    return 0;
}

void VoiceCalls::processCallUpdate(VoiceCall *voiceCall)
{
    emit update(voiceCall);
    // after other instances are informed we can remove the call if it's a disconnect-update
    if(voiceCall->getState() == DISCONNECTED) {
        bool removed = m_VoiceCalls.removeOne(voiceCall);
        // if it was removed successfully, we need to delete it additionaly
        if(removed) {
            delete voiceCall;
        } else {
            qDebug() << "Could not remove call from list: " << voiceCall->getId();
        }
    }
}

void VoiceCalls::append(VoiceCall* voiceCall)
{
    connect(voiceCall, SIGNAL(update(VoiceCall*)), this, SLOT(processCallUpdate(VoiceCall*)));
    m_VoiceCalls.append(voiceCall);
    qDebug() << "VoiceCalls::append" << this->m_VoiceCalls.count();
}

bool VoiceCalls::empty() const
{
    return m_VoiceCalls.empty();
}

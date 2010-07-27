#include "voicecall.h"


VoiceCall::VoiceCall(VoiceCallUpdaterIF* updater) : m_updater(updater)
{
    // connect the signal to get update information
    connect(m_updater, SIGNAL(update()), this, SLOT(processUpdate()));
}

void VoiceCall::processUpdate()
{
    //qDebug() << "VoiceCall::update() " << m_updater->getState();
    emit update(this);
}

QString VoiceCall::getNumber() const
{
    return m_updater->getNumber();
}
VoiceCallState VoiceCall::getState() const
{
    return m_updater->getState();
}
QString VoiceCall::getId() const
{
    return m_updater->getId();
}

VoiceCall::~VoiceCall()
{
    delete m_updater;
}

QDebug operator<<(QDebug dbg, const VoiceCall* voicecall)
{
    dbg.nospace() << "Number: " << voicecall->getNumber() << " State: " << voicecall->getState() << " Object Path: " << voicecall->getId();
    return dbg.maybeSpace();
}
QDebug operator<<(QDebug dbg, const VoiceCall &voicecall)
{
    dbg.nospace() << "Number: " << voicecall.getNumber() << " State: " << voicecall.getState() << " Object Path: " << voicecall.getId();
    return dbg.maybeSpace();
}

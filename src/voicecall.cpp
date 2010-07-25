#include "voicecall.h"

//VoiceCall::VoiceCall(QObject *parent) :
//    QObject(parent)
//{
//}
VoiceCall::VoiceCall(QString objectPath, QString number, VoiceCallState state) :
        m_objectPath(objectPath), m_number(number), m_state(state)
{
}

VoiceCall::VoiceCall(const VoiceCall &voicecall) :
        m_objectPath(voicecall.m_objectPath), m_number(voicecall.m_number), m_state(voicecall.m_state), m_updater(voicecall.m_updater)
{
    // connect the signal to get update information
    connect(m_updater, SIGNAL(update()), this, SLOT(processUpdate()));
}

VoiceCall::VoiceCall(VoiceCallUpdaterIF* updater) : m_updater(updater)
{
    // connect the signal to get update information
    connect(m_updater, SIGNAL(update()), this, SLOT(processUpdate()));
}

void VoiceCall::processUpdate()
{
    //qDebug() << "VoiceCall::update() " << m_updater->getState();
    m_state = m_updater->getState();
    m_number = m_updater->getNumber();
    emit update(this);
}

void VoiceCall::setNumber(QString number)
{
    m_number = number;
}
void VoiceCall::setState(VoiceCallState state)
{
    m_state = state;
}

QString VoiceCall::getNumber() const
{
    return m_number;
}
QString VoiceCall::getObjectPath() const
{
    return m_objectPath;
}
VoiceCallState VoiceCall::getState() const
{
    return m_state;
}
QString VoiceCall::getId() const
{
    return getObjectPath();
}

//VoiceCall& VoiceCall::operator =(const VoiceCall& voiceCall)
//{
//    m_objectPath = voiceCall.getObjectPath();
//    m_number = voiceCall.getNumber();
//    m_state = voiceCall.getState();
//    return *this;
//}

VoiceCall::~VoiceCall()
{
    // TODO: ptential memory leak. can not be deleted here because the objects are
    // copied serveral times an the pointer is necessary because of the signal/slot
    // connections in it.
    //delete m_updater;
}

QDebug operator<<(QDebug dbg, const VoiceCall* voicecall)
{
    dbg.nospace() << "Number: " << voicecall->getNumber() << " State: " << voicecall->getState() << " Object Path: " << voicecall->getObjectPath();
    return dbg.maybeSpace();
}
QDebug operator<<(QDebug dbg, const VoiceCall &voicecall)
{
    dbg.nospace() << "Number: " << voicecall.getNumber() << " State: " << voicecall.getState() << " Object Path: " << voicecall.getObjectPath();
    return dbg.maybeSpace();
}

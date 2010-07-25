#include "voicecallupdaterif.h"

VoiceCallUpdaterIF::VoiceCallUpdaterIF(QString id): m_id(id)
{
}

VoiceCallState VoiceCallUpdaterIF::getState()
{
    return m_state;
}

QString VoiceCallUpdaterIF::getNumber()
{
    return m_number;
}

QString VoiceCallUpdaterIF::getId()
{
    return m_id;
}

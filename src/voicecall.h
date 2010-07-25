#ifndef VOICECALL_H
#define VOICECALL_H

#include <QObject>
#include <QDebug>
#include "VoiceCallStateEnum.h"
#include <voicecallupdaterif.h>


/**
 * \brief
 * The C++ counterpart to the oFono API description in oFono/doc/VoiceCall.txt
 */
class VoiceCall : public QObject
{
Q_OBJECT
public:
    //VoiceCall() {}
    VoiceCall(VoiceCallUpdaterIF* updater);
    /**
     * @param objectPath is the identifier for each VoiceCall because it is unique in the oFono DBus interface.
     * @param number The calling/called phone number of the VoiceCall.
     * @param state The current state of the VoiceCall.
     */
    //VoiceCall(QString objectPath, QString number, VoiceCallState state);
    /**
     * Copy Constructor because the class is used with Qt lists.
     */
    //VoiceCall(const VoiceCall &voicecall);
    virtual ~VoiceCall();
    /**
     * Assign operator because the class is used with Qt lists.
     */
    VoiceCall& operator=(const VoiceCall& voiceCall);


    /**
     * Wraps just around getObjectPath()
     * @return The DBus object path is used as id.
     */
    QString getId() const;
    /**
     * @return The calling/called phone number.
     */
    QString getNumber() const;
    /**
     * @return The current state of the VoiceCall.
     */
    VoiceCallState getState() const;

    //void update(const VoiceCall& call);

signals:
    void update(const VoiceCall*);

public slots:
    void processUpdate();

private:
    VoiceCallUpdaterIF* m_updater;


};

QDebug operator<<(QDebug dbg, const VoiceCall &voicecall);

#endif // VOICECALL_H

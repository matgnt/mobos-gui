#ifndef VOICECALL_H
#define VOICECALL_H

#include <QObject>
#include <QDebug>

enum VoiceCallState
{
    NONE,
    INCOMING,
    OUTGOING
};

class VoiceCall : public QObject
{
Q_OBJECT
public:
    VoiceCall() {}
    VoiceCall(QString objectPath, QString number, VoiceCallState state);
    VoiceCall(const VoiceCall &voicecall);
    virtual ~VoiceCall() {}
    VoiceCall& operator=(const VoiceCall& voiceCall);


    QString getId() const;
    QString getObjectPath() const;
    QString getNumber() const;
    VoiceCallState getState() const;


signals:

public slots:
    void setNumber(QString);
    void setState(VoiceCallState);
    //void setObjectPath()

private:
    QString m_number;
    VoiceCallState m_state;
    QString m_objectPath;


};

QDebug operator<<(QDebug dbg, const VoiceCall &voicecall);

#endif // VOICECALL_H

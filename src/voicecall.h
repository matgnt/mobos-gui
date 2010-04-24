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

/**
 * \brief
 * The C++ counterpart to the oFono API description in oFono/doc/VoiceCall.txt
 */
class VoiceCall : public QObject
{
Q_OBJECT
public:
    VoiceCall() {}
    /**
     * @param objectPath is the identifier for each VoiceCall because it is unique in the oFono DBus interface.
     * @param number The calling/called phone number of the VoiceCall.
     * @param state The current state of the VoiceCall.
     */
    VoiceCall(QString objectPath, QString number, VoiceCallState state);
    /**
     * Copy Constructor because the class is used with Qt lists.
     */
    VoiceCall(const VoiceCall &voicecall);
    virtual ~VoiceCall() {}
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
     * @return The DBus object path is used as id.
     * @see getId
     */
    QString getObjectPath() const;
    /**
     * @return The calling/called phone number.
     */
    QString getNumber() const;
    /**
     * @return The current state of the VoiceCall.
     */
    VoiceCallState getState() const;


signals:

public slots:
	/**
	 * To be executed from QML.
	 * Change/Set th VoiceCall's phone number.
	 */
    void setNumber(QString);
    /**
     * To be executed from QML.
     * Change/Set the VoiceCall's current state.
     */
    void setState(VoiceCallState);
    //void setObjectPath()

private:
    QString m_number;
    VoiceCallState m_state;
    QString m_objectPath;


};

QDebug operator<<(QDebug dbg, const VoiceCall &voicecall);

#endif // VOICECALL_H

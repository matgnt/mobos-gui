#ifndef GSM_H
#define GSM_H

#include <QObject>
#include <QtDeclarative/qdeclarative.h>

class Gsm : public QObject
{
Q_OBJECT
public:
    explicit Gsm(QObject *parent = 0);

private:

signals:

public slots:
    void setPowerOn();
    void setPowerOff();
    void dial(QString number);


};

QML_DECLARE_TYPE(Gsm);

#endif // GSM_H

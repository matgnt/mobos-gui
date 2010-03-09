#ifndef GSM_H
#define GSM_H

#include <QObject>

class Gsm : public QObject
{
Q_OBJECT
public:
    explicit Gsm(QObject *parent = 0);

    void popup();
    void setPowerOn();
    void setPowerOff();

private:

signals:

public slots:

};

#endif // GSM_H

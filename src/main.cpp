/*
 * main.cpp
 *
 *  Created on: 17.05.2009
 *      Author: matthias
 */
#include <QtGui/QApplication>

#include "ofono.h"

#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qmlRegisterType<Ofono>("OfonoLib", 1, 0, "Ofono");

    QDeclarativeView view;
    view.rootContext()->setContextProperty("OfonoContext", new Ofono());
    view.setSource(QUrl::fromLocalFile(":qml/mobos-gui.qml"));
    view.show();

    return a.exec();
}

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
#include <QtDeclarative/QDeclarativeComponent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDeclarativeView view;

    view.rootContext()->setContextProperty("OfonoContext", new Ofono());

    QFile f(":qml/dummydata/Recipes.qml");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QDeclarativeComponent comp(view.engine());
    comp.setData(data, QUrl());
    QObject *dummyData = comp.create();

    if(comp.isError()) {
        QList<QDeclarativeError> errors = comp.errors();
        foreach (const QDeclarativeError &error, errors) {
            qWarning() << error;
        }
    }

    if (dummyData) {
        qWarning() << "Loaded dummy data.";
        view.rootContext()->setContextProperty("Recipes", dummyData);
        //dummyData->setParent(this);
    }

    view.setSource(QUrl("qrc:qml/mobos-gui.qml"));
    view.setSceneRect(0, 0, 240, 320);
    view.show();

    return a.exec();
}

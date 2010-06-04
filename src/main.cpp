/*
 * main.cpp
 *
 *  Created on: 17.05.2009
 *      Author: matthias
 */
#include <QtGui/QApplication>

#include "ofono.h"

#include <QtGui>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QGraphicsObject>
#include <QtDeclarative/QDeclarativeContext>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qmlRegisterType<Ofono>("OfonoLib", 1, 0, "Ofono");


    QDeclarativeEngine *engine = new QDeclarativeEngine();
    QDeclarativeContext *context = engine->rootContext();
    context->setContextProperty("OfonoContext", new Ofono());
    QDeclarativeComponent component(engine, QUrl::fromLocalFile(":qml/mobos-gui.qml"));
    // to print out errors in the qml file
    if(component.isError()) {
        QListIterator<QDeclarativeError> itr (component.errors());
        while(itr.hasNext()) {
            QDeclarativeError current = itr.next();
            qDebug() << current;
        }
    }
    QGraphicsObject *object = qobject_cast<QGraphicsObject *>(component.create());

    // load qml into the view
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 240, 320);
    scene.addItem(object);

    QGraphicsView view(&scene);
    view.show();
    //ui.graphicsView->setScene(scene);
    //ui.graphicsView->show();


    return a.exec();
}

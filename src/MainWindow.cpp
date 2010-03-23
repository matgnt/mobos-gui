/*
 * MainWindow.cpp
 *
 *  Created on: 17.05.2009
 *      Author: matthias
 */

#include <QtCore/QDebug>
#include "MainWindow.h"
//#include "dbus/Notifications.h"
#include "ofono.h"

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QGraphicsObject>
#include <QtDeclarative/QDeclarativeContext>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

    QML_REGISTER_TYPE(OfonoLib, 1,0, Ofono, Ofono);


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
    QGraphicsScene* scene = new QGraphicsScene(0, 0, 240, 320);
    scene->addItem(object);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->show();
}

/**
 * http://www.galago-project.org/specs/notification/0.9/x408.html#command-notify
 */

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

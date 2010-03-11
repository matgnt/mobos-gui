/*
 * MainWindow.cpp
 *
 *  Created on: 17.05.2009
 *      Author: matthias
 */

#include <QtCore/QDebug>
#include "MainWindow.h"
//#include "dbus/Notifications.h"
#include "Gsm.h"

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QGraphicsObject>
#include <QtDeclarative/QDeclarativeContext>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(0, 0, 240, 320);
    QDeclarativeEngine *engine = new QDeclarativeEngine;
    QDeclarativeContext *context = engine->rootContext();
    context->setContextProperty("Gsm", new Gsm);
    QDeclarativeComponent component(engine, QUrl::fromLocalFile("./qml/qMoPho.qml"));
    QGraphicsObject *object = qobject_cast<QGraphicsObject *>(component.create());
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

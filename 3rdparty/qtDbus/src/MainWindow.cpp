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
	connect(ui.btnSystemPopup, SIGNAL(clicked()), this, SLOT(btnSystemPopupClicked()));
    connect(ui.btnPowerOn, SIGNAL(clicked()), this, SLOT(btnPowerOnClicked()));
    connect(ui.btnPowerOff, SIGNAL(clicked()), this, SLOT(btnPowerOffClicked()));

    QGraphicsScene* scene = new QGraphicsScene(0, 0, 240, 320);
    QDeclarativeEngine *engine = new QDeclarativeEngine;
    QDeclarativeContext *context = engine->rootContext();
    context->setContextProperty("Gsm", new Gsm);
    QDeclarativeComponent component(engine, QUrl::fromLocalFile("/home/matthias/qt-projects/qMoPho/qMoPho.qml"));
    QGraphicsObject *object = qobject_cast<QGraphicsObject *>(component.create());
    scene->addItem(object);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->show();
}

/**
 * http://www.galago-project.org/specs/notification/0.9/x408.html#command-notify
 */
void MainWindow::btnSystemPopupClicked()
{
    Gsm gsm;
    gsm.popup();
}

void MainWindow::btnPowerOnClicked()
{
    Gsm gsm;
    gsm.setPowerOn();
}

void MainWindow::btnPowerOffClicked()
{
    Gsm gsm;
    gsm.setPowerOff();
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

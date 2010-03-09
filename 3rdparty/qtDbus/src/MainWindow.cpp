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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	connect(ui.btnSystemPopup, SIGNAL(clicked()), this, SLOT(btnSystemPopupClicked()));
}

/**
 * http://www.galago-project.org/specs/notification/0.9/x408.html#command-notify
 */
void MainWindow::btnSystemPopupClicked()
{
    Gsm gsm;
    gsm.popup();
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

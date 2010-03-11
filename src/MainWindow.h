/*
 * MainWindow.h
 *
 *  Created on: 17.05.2009
 *      Author: matthias
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0);
	virtual ~MainWindow();

private:
	Ui::MainWindow ui;
};

#endif /* MAINWINDOW_H_ */

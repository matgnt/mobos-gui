/*
 * main.cpp
 *
 *  Created on: 17.05.2009
 *      Author: matthias
 */
#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow main;
    main.show();

    return a.exec();
}

/********************************************************************************************************************************************
 *  IsoSDK - a powerful CD/DVD/BD recording SDK for Linux, macOS, Windows and Android.
 *  Copyright (c) 2002-2022 Ingo Foerster (pixbytesl@gmail.com).
 *  http://www.isosdk.com
 ********************************************************************************************************************************************/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    //If you want to see the menubar inside the app, add this line, else the menubar is in finder.
    //QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

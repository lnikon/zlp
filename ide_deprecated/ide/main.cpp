#include "mainwindow.h"
#include <QApplication>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <thread>
#include <future>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}

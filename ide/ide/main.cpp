#include "mainwindow.h"
#include <QApplication>

#include <thread>
#include <future>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    std::__future_base::_Result<int> res;

    std::promise<int> promise_obj;
    std::future<int> future_obj;

    return 0;
//    return a.exec();
}

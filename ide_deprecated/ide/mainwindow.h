#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QTabWidget*     mainTabWidget_{Q_NULLPTR};

    void setupMainToolbar();

    void openSourceFile();
    void compileSourceFile();
};

#endif // MAINWINDOW_H

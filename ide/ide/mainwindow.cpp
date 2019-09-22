#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMainToolbar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMainToolbar()
{
    ui->mainToolBar->setMovable(false);
    ui->mainToolBar->addAction(QIcon(":/icons/new_file.png"), "New File");
    ui->mainToolBar->addAction(QIcon(":/icons/open_file.png"), "Open File");
    ui->mainToolBar->addSeparator();
}

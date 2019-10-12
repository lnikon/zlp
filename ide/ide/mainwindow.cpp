#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sourcetextedit.h"

#include "code_generator.hpp"

#include <QAction>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTabBar>

#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->setMovable(false);

    QMenu* fileMenu = new QMenu("File", ui->menuBar);
    ui->menuBar->addMenu(fileMenu);

    QAction* openAction = new QAction(QIcon(":/icons/open_file.png"), "&Open...", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openSourceFile);
    ui->mainToolBar->addAction(openAction);
    fileMenu->addAction(openAction);

    QAction* compileAction = new QAction(QIcon(":/icons/new_file.png"), "&Compile...", this);
    connect(compileAction, &QAction::triggered, this, &MainWindow::compileSourceFile);
    ui->mainToolBar->addAction(compileAction);
    fileMenu->addAction(compileAction);

    mainTabWidget_ = new QTabWidget;

    QHBoxLayout* mainHboxLayout = new QHBoxLayout(this);
    mainHboxLayout->addWidget(mainTabWidget_);

    ui->centralWidget->setLayout(mainHboxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMainToolbar()
{
}

void MainWindow::openSourceFile()
{
    QWidget* pageWidget = new QWidget;

    SourceTextEdit* srcTextEdit = new SourceTextEdit(pageWidget);

    if(auto fileName = srcTextEdit->loadFile(); fileName.has_value())
    {
        QHBoxLayout* srcEditLayout = new QHBoxLayout;
        srcEditLayout->addWidget(srcTextEdit);

        pageWidget->setLayout(srcEditLayout);

        mainTabWidget_->addTab(pageWidget, fileName.value());
    }
}

void MainWindow::compileSourceFile()
{
    QTabBar* tabBar = mainTabWidget_->tabBar();
    QVariant data = tabBar->tabData(0);

    std::vector<std::string> inputFilenames;
    inputFilenames.emplace_back((char *)data.data());

    CodeGenerator codeGen;
    codeGen.setInputFilenames(inputFilenames);
    codeGen.build();
}

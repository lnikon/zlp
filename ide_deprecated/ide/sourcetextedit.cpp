#include "sourcetextedit.h"
#include "ui_sourcetextedit.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QString>

SourceTextEdit::SourceTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sourceTextEdit)
{
    ui->setupUi(this);

    statusBar_ = new QStatusBar;
    ui->verticalLayout->addWidget(statusBar_);
}

SourceTextEdit::~SourceTextEdit()
{
    delete ui;
    delete statusBar_;
}

std::optional<QString> SourceTextEdit::loadFile()
{
    QFileDialog dlg;
    fileName_ = dlg.getOpenFileName();

    if(fileName_.isEmpty())
    {
        return std::nullopt;
    }

    loadFile(fileName_);

    return std::make_optional(fileName_);
}

void SourceTextEdit::clear()
{
    ui->sourceText_plainTextEdit->clear();
}

void SourceTextEdit::reload()
{
    clear();
    loadFile(fileName_);
}

void SourceTextEdit::save()
{
    QFile file(fileName_);
    if(!file.open(QIODevice::ReadWrite))
    {
        return;
    }

    QTextStream stream(&file);
    stream.flush();

    stream << ui->sourceText_plainTextEdit->toPlainText();
}

QString SourceTextEdit::fileName() const
{
    return fileName_;
}

void SourceTextEdit::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite))
    {
        return;
    }

    QTextStream stream(&file);

    ui->sourceText_plainTextEdit->setPlainText(stream.readAll());

    statusBar_->showMessage("File " + fileName_ + " loaded");
}

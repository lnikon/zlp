/********************************************************************************
** Form generated from reading UI file 'sourcetextedit.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOURCETEXTEDIT_H
#define UI_SOURCETEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sourceTextEdit
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *sourceText_plainTextEdit;

    void setupUi(QWidget *sourceTextEdit)
    {
        if (sourceTextEdit->objectName().isEmpty())
            sourceTextEdit->setObjectName(QString::fromUtf8("sourceTextEdit"));
        sourceTextEdit->resize(740, 510);
        verticalLayout = new QVBoxLayout(sourceTextEdit);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        sourceText_plainTextEdit = new QPlainTextEdit(sourceTextEdit);
        sourceText_plainTextEdit->setObjectName(QString::fromUtf8("sourceText_plainTextEdit"));

        verticalLayout->addWidget(sourceText_plainTextEdit);


        retranslateUi(sourceTextEdit);

        QMetaObject::connectSlotsByName(sourceTextEdit);
    } // setupUi

    void retranslateUi(QWidget *sourceTextEdit)
    {
        sourceTextEdit->setWindowTitle(QCoreApplication::translate("sourceTextEdit", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sourceTextEdit: public Ui_sourceTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOURCETEXTEDIT_H

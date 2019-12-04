#-------------------------------------------------
#
# Project created by QtCreator 2019-09-22T00:17:08
#
#-------------------------------------------------

QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ide
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        sourcetextedit.cpp

HEADERS += \
        mainwindow.h \
        sourcetextedit.h

INCLUDEPATH += $$PWD/../../runtime/src/vm

RESOURCES += \
    icons.qrc

FORMS += \
        mainwindow.ui \
        sourcetextedit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx|win32: LIBS += -L$$PWD/../../out/build/x64-Debug/compilation/src/backend/zlpcodegen/ -lzlpcodegen

INCLUDEPATH += $$PWD/../../compilation/src/backend/zlpcodegen
DEPENDPATH += $$PWD/../../compilation/src/backend/zlpcodegen

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../out/build/x64-Debug/compilation/src/backend/zlpcodegen/zlpcodegen.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../out/build/x64-Debug/compilation/src/backend/zlpcodegen/libzlpcodegen.a

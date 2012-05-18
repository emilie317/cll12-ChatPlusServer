#-------------------------------------------------
#
# Project created by QtCreator 2012-05-07T22:04:36
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = ChatPlusServer
TEMPLATE = app


SOURCES += main.cpp\
        chatplusserver.cpp \
    cclient.cpp \
    cserveur.cpp

HEADERS  += cclient.h \
    chatplusserver.h \
    CConstante.h \
    CEnum.h \
    cserveur.h

FORMS    += chatplusserver.ui











#include "chatplusserver.h"
#include "ui_chatplusserver.h"
#include <QtGui>

ChatPlusServer::ChatPlusServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatPlusServer)
{
    ui->setupUi(this);
}

ChatPlusServer::~ChatPlusServer()
{
    delete ui;
}

void ChatPlusServer::on_btnPhoto_clicked()
{

}

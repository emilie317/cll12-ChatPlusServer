#include "chatplusserver.h"
#include "ui_chatplusserver.h"

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

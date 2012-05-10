#ifndef CHATPLUSSERVER_H
#define CHATPLUSSERVER_H

#include <QMainWindow>
#include <QList>
#include "cclient.h"
#include "cserveur.h"
#include <QtNetwork/QTcpServer>

namespace Ui {
class ChatPlusServer;
}

class ChatPlusServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatPlusServer(QWidget *parent = 0);
    ~ChatPlusServer();

    CServeur       *m_Serveur;

private slots:
    void on_btnDemarrer_clicked();
    void NouvelleConnexionAccepte(QString address);

private:
    Ui::ChatPlusServer *ui;

};

#endif // CHATPLUSSERVER_H

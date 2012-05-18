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
    void AfficheNomUsager(QString usager);
    void ClientDeconnecte(QString usager);
    void RafraichirListeUsager(QList<QString> lstUsager);
    void pingRecu(QString usager);

    void on_btnArreter_clicked();

private:
    Ui::ChatPlusServer *ui;
    void EcritLog(QString log);

};

#endif // CHATPLUSSERVER_H

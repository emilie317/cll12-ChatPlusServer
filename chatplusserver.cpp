#include "chatplusserver.h"
#include "ui_chatplusserver.h"
#include <QtNetwork/QTcpServer>
#include "cserveur.h"

#include "CConstante.h"

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

void ChatPlusServer::on_btnDemarrer_clicked()
{
    ui->txtActivites->setText("");

    //-- Ici l'astuce est de s'attacher sur le signal (événement) qui dès
    //-- qu'un client va se connecter va appeler la méthode connexion.
    //-- Cette méthode connexion sera donc utilisé par chaque client à leur
    //-- connexion.
    ui->txtActivites->append("Initialisation du serveur...");
    ui->txtActivites->append(QString("Ouverture du port: %1...").arg(SERVER_PORT));

    m_Serveur = new CServeur();
    if (!m_Serveur->listen(QHostAddress::Any, SERVER_PORT))
    {
        ui->txtActivites->append(QString("Erreur: Impossible d'ouvrir le port %1").arg(SERVER_PORT));
        return;
    }

    ui->txtActivites->append("Ouverture du port reussie");
    ui->txtActivites->append("Attente de connexion...");

    connect(m_Serveur, SIGNAL(clientConnected(QString)), this, SLOT(NouvelleConnexionAccepte(QString)));

}

void ChatPlusServer::NouvelleConnexionAccepte(QString address)
{
    ui->txtActivites->append(QString("Nouveau client connecte. Adresse : %1").arg(address));
}

#include "chatplusserver.h"
#include "ui_chatplusserver.h"
#include <QtNetwork/QTcpServer>
#include <QStringListModel>
#include <QDateTime>
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
    EcritLog("Initialisation du serveur...");
    EcritLog(QString("Ouverture du port: %1...").arg(SERVER_PORT));

    m_Serveur = new CServeur();
    if (!m_Serveur->listen(QHostAddress::Any, SERVER_PORT))
    {
        EcritLog(QString("Erreur: Impossible d'ouvrir le port %1").arg(SERVER_PORT));
        return;
    }

    EcritLog("Ouverture du port reussie");
    EcritLog("Attente de connexion...");

    connect(m_Serveur, SIGNAL(clientConnected(QString)), this, SLOT(NouvelleConnexionAccepte(QString)));
    connect(m_Serveur, SIGNAL(resignalClientDisconnected(QString)), this, SLOT(ClientDeconnecte(QString)));
    connect(m_Serveur, SIGNAL(resignalUserName(QString)), this, SLOT(AfficheNomUsager(QString)));
    connect(m_Serveur, SIGNAL(refreshUserList(QList<QString>)), this, SLOT(RafraichirListeUsager(QList<QString>)));
    connect(m_Serveur, SIGNAL(reTransmetPingRecu(QString)), this, SLOT(pingRecu(QString)));

    ui->btnArreter->setEnabled(true);
    ui->btnDemarrer->setEnabled(false);
}

void ChatPlusServer::NouvelleConnexionAccepte(QString address)
{
    EcritLog(QString("Nouveau client connecte. Adresse : %1").arg(address));
}

void ChatPlusServer::AfficheNomUsager(QString usager)
{
    EcritLog(QString("    Le nom du nouveau client est : %1").arg(usager));
}

void ChatPlusServer::ClientDeconnecte(QString usager)
{
    EcritLog(QString("%1 vient de se deconnecte").arg(usager));
}

void ChatPlusServer::RafraichirListeUsager(QList<QString> lstUsager)
{
    ui->lsvClients->setModel(new QStringListModel(lstUsager));
    ui->lsvClients->reset();
}

void ChatPlusServer::EcritLog(QString log)
{
    ui->txtActivites->append(QString("%1 - %2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), log));
}

void ChatPlusServer::on_btnArreter_clicked()
{
    m_Serveur->disconnect();
    m_Serveur->close();

    ui->lsvClients->setModel(new QStringListModel());
    ui->lsvClients->reset();

    ui->btnArreter->setEnabled(false);
    ui->btnDemarrer->setEnabled(true);

    EcritLog("Fermeture du serveur");
}

void ChatPlusServer::pingRecu(QString usager)
{
    EcritLog(QString("Ping recu de : %1").arg(usager));
}

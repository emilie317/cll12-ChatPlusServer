#include "cserveur.h"

#include <QtNetwork/QTcpSocket>

CServeur::CServeur(QObject *parent) : QTcpServer(parent)
{
}

void CServeur::incomingConnection(int socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    //-- On envoie le signal à notre UI qui affichera l'addresse du client connecté
    emit clientConnected(socket->peerAddress().toString());

    CClient *c = new CClient(socket);

    connect(socket, SIGNAL(readyRead()), c, SLOT(readyRead()));

    m_ListeClients.append(c);
}

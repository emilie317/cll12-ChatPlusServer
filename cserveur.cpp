#include "cserveur.h"

#include <QtNetwork/QTcpSocket>

CServeur::CServeur(QObject *parent) : QTcpServer(parent)
{
}

void CServeur::incomingConnection(int socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    CClient *c = new CClient(socket);
    c->m_IP = socket->peerAddress().toString();

    m_ListeClients.append(c);

    //-- On envoie le signal à notre UI qui affichera l'addresse du client connecté
    emit clientConnected(c->m_IP);

    connect(socket, SIGNAL(readyRead()), c, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), c, SLOT(disconnected()));

    connect(c, SIGNAL(signalUserName(QString)), this, SLOT(signalUserName(QString)));
    connect(c, SIGNAL(clientDisconnected(QString)), this, SLOT(clientDisconnected(QString)));
    connect(c, SIGNAL(demandeEnvoiListeClients()), this, SLOT(envoiListeClients()));
    connect(c, SIGNAL(transmetMessage(QString,QString,QString)), this, SLOT(transmetMessage(QString,QString,QString)));
    connect(c, SIGNAL(transmetFichier(QString,QString,QString,QString,QString,QByteArray)), this, SLOT(transmetFichier(QString,QString,QString,QString,QString,QByteArray)));
    connect(c, SIGNAL(pingRecu(QString)), this, SLOT(pingRecu(QString)));
}

void CServeur::signalUserName(QString name)
{
    emit resignalUserName(name);
    emit refreshUserList(BuildUserList());
}

void CServeur::clientDisconnected(QString name)
{
    int posToRemove = -1;
    for (int i=0; i<m_ListeClients.count(); i++)
    {
        if (m_ListeClients[i]->m_Surnom == name)
            posToRemove = i;
    }
    if (posToRemove > -1)
        m_ListeClients.removeAt(posToRemove);

    emit resignalClientDisconnected(name);
    emit refreshUserList(BuildUserList());
}

QList<QString> CServeur::BuildUserList()
{
    QList<QString> lstUser;

    for(int i=0; i<m_ListeClients.count(); i++)
        lstUser.append(m_ListeClients[i]->m_Surnom);

    return lstUser;
}

void CServeur::envoiListeClients()
{
    QList<QString> lstClients = BuildUserList();

    for (int c=0; c<m_ListeClients.count(); c++)
    {
        QByteArray bClients;
        bClients.append(QString("%LISTECLIENTS"));
        for (int i=0; i<lstClients.count(); i++)
        {
            if (lstClients[i] != m_ListeClients[c]->GetNomClient())
                bClients.append(QString("|%1").arg(lstClients[i]));
        }

        m_ListeClients[c]->m_socket->write(bClients);
        m_ListeClients[c]->m_socket->waitForBytesWritten();
    }
}

void CServeur::transmetMessage(QString source, QString destinataire, QString message)
{
    for (int i=0; i<m_ListeClients.count(); i++)
    {
        if (m_ListeClients[i]->GetNomClient() == destinataire)
        {
            QString newMessage = QString("%MESSAGE|%1|%2|%3").arg(source, destinataire, message);
            QByteArray b;
            b.append(newMessage);

            m_ListeClients[i]->m_socket->write(b);
            m_ListeClients[i]->m_socket->waitForBytesWritten();
        }
    }
}

void CServeur::transmetFichier(QString source, QString destinataire, QString byteEcrit, QString byteTotal, QString fichier, QByteArray data)
{
    for (int i=0; i<m_ListeClients.count(); i++)
    {
        if (m_ListeClients[i]->GetNomClient() == destinataire)
        {
            QString newMessage = QString("%FICHIER|%1|%2|%3|%4|%5").arg(source, destinataire, byteEcrit, byteTotal, fichier);
            data.insert(0, newMessage);

            m_ListeClients[i]->m_socket->write(data);
            m_ListeClients[i]->m_socket->waitForBytesWritten();
        }
    }
}

void CServeur::pingRecu(QString name)
{
    emit reTransmetPingRecu(name);
}

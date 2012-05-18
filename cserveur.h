#ifndef CSERVEUR_H
#define CSERVEUR_H

#include <QtNetwork/QTcpServer>
#include <QList>
#include "cclient.h"

class CServeur : public QTcpServer
{
    Q_OBJECT

public:
    explicit CServeur(QObject *parent = 0);
    QList<CClient *> m_ListeClients;

protected:
    void incomingConnection(int socketDescriptor);

signals:
    void clientConnected(QString address);
    void resignalUserName(QString name);
    void resignalClientDisconnected(QString name);
    void refreshUserList(QList<QString> lstUsagers);
    void reTransmetPingRecu(QString name);

private slots:
    void signalUserName(QString name);
    void clientDisconnected(QString name);
    void envoiListeClients();
    void transmetMessage(QString source, QString destinataire, QString message);
    void transmetFichier(QString source, QString destinataire, QString byteEcrit, QString byteTotal, QString fichier, QByteArray data);
    void pingRecu(QString name);

private:
    QList<QString> BuildUserList();

};

#endif // CSERVEUR_H

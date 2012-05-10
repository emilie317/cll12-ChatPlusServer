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

};

#endif // CSERVEUR_H

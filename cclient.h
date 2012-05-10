#ifndef CCLIENT_H
#define CCLIENT_H

#include <QString>
#include <QtNetwork/QTcpSocket>


class CClient : public QObject
{
    Q_OBJECT

public:
    CClient(QTcpSocket *socket);

private:
    QTcpSocket *m_socket;

private slots:
    void readyRead();

};

#endif // CCLIENT_H

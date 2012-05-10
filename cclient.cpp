#include "cclient.h"
#include <QMessageBox>
#include <QtNetwork/QTcpSocket>

CClient::CClient(QTcpSocket *socket)
{
    m_socket = socket;
}

void CClient::readyRead()
{
    QTcpSocket *socket = m_socket;

    while(true)
    {
        QString ligne = QString::fromUtf8(socket->readLine()).trimmed();

        if (ligne.length() > 0)
            QMessageBox::information(0, "", ligne);

        sleep(100);
    }
}

#include "cclient.h"
#include "CConstante.h"
#include <QMessageBox>
#include <QtNetwork/QTcpSocket>

CClient::CClient(QTcpSocket *socket)
{
    m_socket = socket;
}

void CClient::readyRead()
{
    QTcpSocket *socket = m_socket;

    QByteArray data = socket->readAll(); //-- QINT64
    QByteArray code = data.left(500); //-- On prend un échantillon pour voir le code
    QString ligne = QString(code);

    if (ligne.length() > 0)
    {
        //-- On analyse ce qu'on a reçu à savoir si c'est un code de commande
        if (ligne.at(0) == COMMAND_CODE)
        {
            QStringList lst = ligne.split('|');

            if (lst[0] == "%SURNOM")
            {
                ligne = QString(data);
                lst = ligne.split('|');

                m_Surnom = lst[1];
                emit signalUserName(GetNomClient());

                //-- On répond pour dire que nous avons reçu la commande
                QByteArray bOK;
                bOK.append(QString("%OK"));
                socket->write(bOK);
                socket->waitForBytesWritten();

                sleep(1);

                emit demandeEnvoiListeClients();
            }

            if (lst[0] == "%MESSAGE")
            {
                ligne = QString(data);
                lst = ligne.split('|');

                emit transmetMessage(lst[1], lst[2], lst[3]);
            }

            if (lst[0] == "%FICHIER")
            {               
                //-- %1 - Source
                //-- %2 - Destinataire
                //-- %3 - Nb bytes ecrit
                //-- %4 - Nb bytes total
                //-- %5 - Nom fichier
                //-- %6 - Data

                //QMessageBox::information(0, "", QString("%1|%2|%3|%4|%5").arg(lst[1], lst[2], lst[3], lst[4], lst[5]));
                int posDepartImage = 7 + lst[1].length() + lst[2].length() + lst[3].length() + lst[4].length() + lst[5].length();

                emit transmetFichier(lst[1], lst[2], lst[3], lst[4], lst[5], data.right(data.count() - posDepartImage));
            }

            if (lst[0] == "%PING")
            {
                emit pingRecu(GetNomClient());
            }
        }
    }
}

void CClient::disconnected()
{
    emit clientDisconnected(GetNomClient());
}

QString CClient::GetNomClient()
{
    return m_Surnom;
}

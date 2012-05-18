#ifndef CCLIENT_H
#define CCLIENT_H

#include <QString>
#include <QtNetwork/QTcpSocket>

class CClient : public QObject
{
    Q_OBJECT

public:
    CClient(QTcpSocket *socket);

    QString m_Surnom;
    QString m_IP;
    QTcpSocket *m_socket;

    QString GetNomClient();

private:
    QString GetClientAdress();

private slots:
    void readyRead();
    void disconnected();

signals:
    void signalUserName(QString name);
    void clientDisconnected(QString name);
    void demandeEnvoiListeClients();
    void transmetMessage(QString source, QString destinataire, QString message);
    void transmetFichier(QString source, QString destinataire, QString byteEcrit, QString byteTotal, QString fichier, QByteArray data);
    void pingRecu(QString name);

};

#endif // CCLIENT_H

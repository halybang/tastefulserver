
#include <QCryptographicHash>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QSslSocket>
#include <QSslCertificate>
#include <QSslKey>

#include <tastefulserver/MqttsSocket.h>
#include <tastefulserver/MqttSocketHandler.h>

namespace tastefulserver {



MqttsSocket::MqttsSocket(MqttSocketHandler * handler, const QSslCertificate & certificate, const QSslKey & privateKey)
: MqttSocket(handler)
, m_certificate(certificate)
, m_privateKey(privateKey)
{ 
}

QAbstractSocket * MqttsSocket::createSocket(qintptr socketDescriptor)
{
    QSslSocket * socket = new QSslSocket();

    socket->setSocketDescriptor(socketDescriptor);

    socket->setLocalCertificate(m_certificate);
    socket->setPrivateKey(m_privateKey);

    socket->startServerEncryption();
}

} // namespace tastefulserver

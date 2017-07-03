#include <tastefulserver/WebsSocket.h>

#include <tastefulserver/WebSocketHandler.h>
#include <tastefulserver/HttpsSocket.h>

#include <QCryptographicHash>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QSslSocket>

namespace tastefulserver {


WebsSocket::WebsSocket(WebSocketHandler * handler, const QSslCertificate & certificate, const QSslKey & privateKey)
: WebSocket(handler)
, m_certificate(certificate)
, m_privateKey(privateKey)
{    
}

QAbstractSocket * WebsSocket::createSocket(qintptr socketDescriptor)
{
    QSslSocket * socket = new QSslSocket();

    socket->setSocketDescriptor(socketDescriptor);

    socket->setLocalCertificate(m_certificate);
    socket->setPrivateKey(m_privateKey);

    socket->startServerEncryption();
}

} // namespace tastefulserver

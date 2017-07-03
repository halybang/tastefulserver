#include <tastefulserver/MqttsSocketServer.h>
#include <tastefulserver/MqttsSocket.h>

namespace tastefulserver {

MqttsSocketServer::MqttsSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey)
: TcpServer()
, m_certificate(certificate)
, m_privateKey(privateKey)
{
}

MqttsSocketServer::~MqttsSocketServer()
{
}

AbstractSocket * MqttsSocketServer::createSocket()
{
    return new MqttsSocket(this, m_certificate, m_privateKey);
}

} // namespace tastefulserver

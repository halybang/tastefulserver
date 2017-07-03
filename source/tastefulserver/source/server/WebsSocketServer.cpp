#include <tastefulserver/WebsSocketServer.h>

#include <tastefulserver/WebsSocket.h>

namespace tastefulserver {

WebsSocketServer::WebsSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey)
    : TcpServer()
    , m_certificate(certificate)
    , m_privateKey(privateKey)
{
}

WebsSocketServer::~WebsSocketServer()
{
}

AbstractSocket * WebsSocketServer::createSocket()
{
    return new WebsSocket(this, m_certificate, m_privateKey);
}

} // namespace tastefulserver

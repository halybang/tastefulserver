#include <tastefulserver/HttpsCallbackServer.h>

namespace tastefulserver {

HttpsCallbackServer::HttpsCallbackServer(const QSslCertificate & certificate, const QSslKey & privateKey, const RequestCallback & callback)
: HttpsServer(certificate, privateKey)
, m_callback(callback)
{
}

HttpsCallbackServer::~HttpsCallbackServer()
{
}

bool HttpsCallbackServer::handleRequest(HttpSocket * socket, const HttpRequest & request)
{
    socket->send(m_callback(request));
    return true;
}

} // namespace tastefulserver

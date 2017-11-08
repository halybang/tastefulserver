#include <tastefulserver/HttpsWebSocketServer.h>

#include <tastefulserver/HttpsSocket.h>
#include <tastefulserver/WebsSocket.h>

#include <QTimer>

namespace tastefulserver {

HttpsWebSocketServer::HttpsWebSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey)
: HttpsServer(certificate, privateKey)
{
}

HttpsWebSocketServer::~HttpsWebSocketServer()
{
}
bool HttpsWebSocketServer::handleRequest(HttpSocket * socket, const HttpRequest & request)
{
    // Do lookup controller, then parse param to controller

    if (request.hasHeader(http::Upgrade))
    {
        if (handleUpgrade(socket, request))
            return false;
    }
    socket->send(HttpResponse(http::NotImplemented));
    return true;
    //return HttpSocketHandler::handleRequest();
}

bool HttpsWebSocketServer::handleUpgrade(HttpSocket * socket, const HttpRequest & request)
{
    if (request.getHeader(http::Upgrade).getValue() == "websocket")
    {
        WebsSocket * websocket = new WebsSocket(this, m_certificate, m_privateKey);

        websocket->upgrade(socket, request);

        return true;
    }

    return HttpSocketHandler::handleUpgrade(socket, request);
}

} // namespace tastefulserver

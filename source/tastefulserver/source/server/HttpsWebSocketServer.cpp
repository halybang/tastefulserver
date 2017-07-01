#include <tastefulserver/HttpsWebSocketServer.h>

#include <tastefulserver/HttpsSocket.h>
#include <tastefulserver/WebSocket.h>

#include <QTimer>

namespace tastefulserver {

HttpsWebSocketServer::HttpsWebSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey, const RequestCallback & callback)
    :HttpsCallbackServer(certificate, privateKey, callback)
{
}

HttpsWebSocketServer::~HttpsWebSocketServer()
{
}

bool HttpsWebSocketServer::handleUpgrade(HttpSocket * socket, const HttpRequest & request)
{
    if (request.getHeader(http::Upgrade).getValue() == "websocket")
    {
        WebSocket * websocket = new WebSocket(this);

        websocket->upgrade(socket, request);

        return true;
    }

    return HttpSocketHandler::handleUpgrade(socket, request);
}

} // namespace tastefulserver

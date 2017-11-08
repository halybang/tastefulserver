#include <tastefulserver/HttpWebSocketServer.h>

#include <tastefulserver/HttpSocket.h>
#include <tastefulserver/WebSocket.h>

#include <QTimer>

namespace tastefulserver {

HttpWebSocketServer::HttpWebSocketServer(int numThreads)
    :HttpServer(numThreads)
{
}

HttpWebSocketServer::~HttpWebSocketServer()
{
}

void HttpWebSocketServer::registeHandler(const QString &path, WebSocketHandler *handler)
{
    auto it = handlers.find(path);
    if (it == handlers.end()) {
        handlers[path] = handler;
    }
}

bool HttpWebSocketServer::handleRequest(HttpSocket * socket, const HttpRequest & request)
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

bool HttpWebSocketServer::handleUpgrade(HttpSocket * socket, const HttpRequest & request)
{
    if (request.getHeader(http::Upgrade).getValue() == "websocket")
    {
        WebSocketHandler *handler = this;
        auto it = handlers.find(request.getRequestUri());
        if (it != handlers.end()) {\
            handler = it->second;
        }
        //WebSocket * websocket = new WebSocket(this);
        WebSocket * websocket = new WebSocket(handler);

        websocket->upgrade(socket, request);

        return true;
    }

    return HttpSocketHandler::handleUpgrade(socket, request);
}

} // namespace tastefulserver

#pragma once

#include <tastefulserver/tastefulserver_api.h>
#include <tastefulserver/TcpServer.h>
#include <tastefulserver/HttpSocketHandler.h>
#include <tastefulserver/HttpCallbackServer.h>
#include <tastefulserver/WebSocketHandler.h>

namespace tastefulserver {

class TASTEFULSERVER_API HttpWebSocketServer : public HttpCallbackServer, WebSocketHandler
{
public:
    HttpWebSocketServer(const RequestCallback & callback, int numThreads = 1);
    virtual ~HttpWebSocketServer();

protected:
    //virtual AbstractSocket * createSocket() override;

    // --- handling ---

    virtual bool handleUpgrade(HttpSocket * socket, const HttpRequest & request) override;
    //virtual void handleRequest(HttpSocket * socket, const HttpRequest & request) override;

    //virtual void handleText(WebSocket * socket, const QByteArray & text) override;
    //virtual void handleBinary(WebSocket * socket, const QByteArray & binary) override;
    //virtual void connectionEstablished(WebSocket * socket, const HttpRequest & request) override;
};

} // namespace tastefulserver

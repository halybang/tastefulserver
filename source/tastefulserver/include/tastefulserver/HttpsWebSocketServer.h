#pragma once

#include <tastefulserver/tastefulserver_api.h>
#include <tastefulserver/HttpsCallbackServer.h>
#include <tastefulserver/WebSocketHandler.h>

namespace tastefulserver {

class TASTEFULSERVER_API HttpsWebSocketServer : HttpsCallbackServer, public WebSocketHandler
{
public:
    HttpsWebSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey, const RequestCallback & callback);
    virtual ~HttpsWebSocketServer();

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
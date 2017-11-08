#pragma once

#include <tastefulserver/tastefulserver_api.h>
#include <tastefulserver/HttpsCallbackServer.h>
#include <tastefulserver/WebSocketHandler.h>

namespace tastefulserver {

class TASTEFULSERVER_API HttpsWebSocketServer : public HttpsServer, WebSocketHandler
{
public:
    HttpsWebSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey);
    virtual ~HttpsWebSocketServer();

protected:
    //virtual AbstractSocket * createSocket() override;
    // --- handling ---

    // TODO: Verify upgrade function
    virtual bool handleUpgrade(HttpSocket * socket, const HttpRequest & request) override;
    virtual bool handleRequest(HttpSocket * socket, const HttpRequest & request) override;

    //virtual void handleText(WebSocket * socket, const QByteArray & text) override;
    //virtual void handleBinary(WebSocket * socket, const QByteArray & binary) override;
    //virtual void connectionEstablished(WebSocket * socket, const HttpRequest & request) override;
};

} // namespace tastefulserver

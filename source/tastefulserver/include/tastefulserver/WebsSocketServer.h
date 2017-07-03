#pragma once

#include <functional>
#include <QSslCertificate>
#include <QSslKey>

#include <tastefulserver/tastefulserver_api.h>

#include <tastefulserver/TcpServer.h>
#include <tastefulserver/AbstractSocket.h>
#include <tastefulserver/WebSocketHandler.h>

namespace tastefulserver {

class TASTEFULSERVER_API WebsSocketServer : public TcpServer, WebSocketHandler
{
public:
    WebsSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey);
    ~WebsSocketServer();

protected:
    virtual AbstractSocket * createSocket() override;

    // --- handling ---

    //virtual void handleText(WebSocket * socket, const QByteArray & text) override;
    //virtual void handleBinary(WebSocket * socket, const QByteArray & binary) override;
    //virtual void connectionEstablished(WebSocket * socket) override;
    //virtual void connectionClosed(WebSocket * socket) override;
private:
    QSslCertificate m_certificate;
    QSslKey m_privateKey;
};

} // namespace tastefulserver

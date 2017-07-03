#pragma once

#include <functional>

#include <tastefulserver/tastefulserver_api.h>

#include <QSslCertificate>
#include <QSslKey>

#include <tastefulserver/TcpServer.h>
#include <tastefulserver/AbstractSocket.h>
#include <tastefulserver/MqttSocketHandler.h>

namespace tastefulserver {

class TASTEFULSERVER_API MqttsSocketServer : public TcpServer, public MqttSocketHandler
{
public:
    MqttsSocketServer(const QSslCertificate & certificate, const QSslKey & privateKey);
    ~MqttsSocketServer();

protected:
    virtual AbstractSocket * createSocket() override;

    // --- handling ---

    //virtual void handleText(WebSocket * socket, const QByteArray & text) override;
    //virtual void handleBinary(WebSocket * socket, const QByteArray & binary) override;
    //virtual void connectionEstablished(const HttpRequest & request, WebSocket * socket) override;
    //virtual void connectionClosed(const HttpRequest & request, WebSocket * socket) override;
    QSslCertificate m_certificate;
    QSslKey m_privateKey;
};

} // namespace tastefulserver

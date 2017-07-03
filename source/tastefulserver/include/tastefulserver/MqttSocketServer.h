#pragma once

#include <functional>

#include <tastefulserver/tastefulserver_api.h>

#include <tastefulserver/TcpServer.h>
#include <tastefulserver/AbstractSocket.h>
#include <tastefulserver/MqttSocketHandler.h>

namespace tastefulserver {

class TASTEFULSERVER_API MqttSocketServer : public TcpServer, public MqttSocketHandler
{
public:
    MqttSocketServer();
    ~MqttSocketServer();

protected:
    virtual AbstractSocket * createSocket() override;

    // --- handling ---

    //virtual void handleText(WebSocket * socket, const QByteArray & text) override;
    //virtual void handleBinary(WebSocket * socket, const QByteArray & binary) override;
    //virtual void connectionEstablished(const HttpRequest & request, WebSocket * socket) override;
    //virtual void connectionClosed(const HttpRequest & request, WebSocket * socket) override;
};

} // namespace tastefulserver

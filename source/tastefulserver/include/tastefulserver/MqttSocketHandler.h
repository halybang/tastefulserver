#pragma once

#include <tastefulserver/tastefulserver_api.h>

#include <tastefulserver/MqttSocket.h>

namespace tastefulserver {

class TASTEFULSERVER_API MqttSocketHandler
{
public:

    virtual void connectionEstablished(MqttSocket * socket);
    virtual void connectionClosed(MqttSocket * socket);
#if 0
    virtual void handleText(WebSocket * socket, const QByteArray & text) = 0;
    virtual void handleBinary(WebSocket * socket, const QByteArray & binary) = 0;
#endif
};

} // namespace tastefulserver

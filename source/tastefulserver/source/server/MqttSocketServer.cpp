#include <tastefulserver/MqttSocketServer.h>

#include <tastefulserver/MqttSocket.h>

namespace tastefulserver {

MqttSocketServer::MqttSocketServer()
{
}

MqttSocketServer::~MqttSocketServer()
{
}

AbstractSocket * MqttSocketServer::createSocket()
{
    return new MqttSocket(this);
}

} // namespace tastefulserver

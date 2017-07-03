#pragma once

#include <tastefulserver/tastefulserver_api.h>

#include <tastefulserver/AbstractSocket.h>
#include <tastefulserver/MqttSocketFrame.h>
#include <tastefulserver/MqttSocketFrameParser.h>

namespace tastefulserver {

class MqttSocketHandler;


class TASTEFULSERVER_API MqttSocket : public AbstractSocket
{
    Q_OBJECT
public:
    MqttSocket(MqttSocketHandler * handler);
#if 0
    void upgrade(HttpSocket * socket, const HttpRequest & request);

    void performHandshake(const HttpRequest & request);

    void sendText(const QByteArray & text);
    void sendBinary(const QByteArray & binary);
    void sendPing();
#endif
    void closeConnection();

protected:

    QAbstractSocket * createSocket(qintptr socketDescriptor);

    virtual void receiveData(const QByteArray & data) override;

    void sendFrame(const MqttSocketFrame & frame);
    void sendPong();

    MqttSocketHandler * m_handler;
    MqttSocketFrameParser m_parser;
    MqttSocketFrame m_fragmentedMessage;

protected slots:
    void badFrame();
    void connectionClosed();
};

} // namespace tastefulserver

#pragma once

#include <tastefulserver/tastefulserver_api.h>
#include <QSslCertificate>
#include <QSslKey>

#include <tastefulserver/AbstractSocket.h>
#include <tastefulserver/MqttSocketFrame.h>
#include <tastefulserver/MqttSocketFrameParser.h>
#include <tastefulserver/MqttSocket.h>

namespace tastefulserver {

class MqttSocketHandler;


class TASTEFULSERVER_API MqttsSocket : public MqttSocket
{
    Q_OBJECT
public:
    MqttsSocket(MqttSocketHandler * handler, const QSslCertificate & certificate, const QSslKey & privateKey);
#if 0
    void upgrade(HttpSocket * socket, const HttpRequest & request);

    void performHandshake(const HttpRequest & request);

    void sendText(const QByteArray & text);
    void sendBinary(const QByteArray & binary);
    void sendPing();

    void closeConnection();
#endif

protected:

    QAbstractSocket * createSocket(qintptr socketDescriptor);
    QSslCertificate m_certificate;
    QSslKey m_privateKey;

};

} // namespace tastefulserver

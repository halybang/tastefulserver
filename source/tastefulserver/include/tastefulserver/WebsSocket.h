#pragma once

#include <tastefulserver/tastefulserver_api.h>

#include <tastefulserver/AbstractSocket.h>
#include <tastefulserver/WebSocket.h>
#include <tastefulserver/WebSocketFrame.h>
#include <tastefulserver/WebSocketFrameParser.h>
#include <tastefulserver/http.h>

#include <QSslCertificate>
#include <QSslKey>

namespace tastefulserver {

class WebSocketHandler;

class TASTEFULSERVER_API WebsSocket : public WebSocket
{
    Q_OBJECT
public:
    WebsSocket(WebSocketHandler * handler, const QSslCertificate & certificate, const QSslKey & privateKey);

    //void upgrade(HttpsSocket * socket, const HttpRequest & request);

protected:

    virtual QAbstractSocket * createSocket(qintptr socketDescriptor) override;

    QSslCertificate m_certificate;
    QSslKey m_privateKey;

};

} // namespace tastefulserver

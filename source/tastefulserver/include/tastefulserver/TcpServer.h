#pragma once

#include <QTcpServer>

#include <tastefulserver/tastefulserver_api.h>
#include <tastefulserver/Connection.h>

namespace tastefulserver {

class ThreadPool;
class TcpServerPrivate;
class TASTEFULSERVER_API TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit TcpServer(int numThreads = 1, bool creatPool = false, QObject* parent = nullptr);
    virtual ~TcpServer();

    static void setNumThreads(int numThreads);

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

    virtual AbstractSocket * createSocket() = 0;

    static ThreadPool * s_threadPool;
    static int s_serverCount;
private:
    Q_DECLARE_PRIVATE(TcpServer)
    QScopedPointer<TcpServerPrivate> d_ptr;
};

} // namespace tastefulserver

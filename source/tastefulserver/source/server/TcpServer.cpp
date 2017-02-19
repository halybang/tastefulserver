#include <thread>
#include <tastefulserver/TcpServer.h>
#include <tastefulserver/Connection.h>
#include "../core/ThreadPool.h"

namespace tastefulserver {

ThreadPool * TcpServer::s_threadPool = new ThreadPool();
int TcpServer::s_serverCount = 0;

class TcpServer;
class TcpServerPrivate
{
    Q_DECLARE_PUBLIC(TcpServer)
public:
    explicit TcpServerPrivate(TcpServer *server): q_ptr(server) {

    }
    virtual ~TcpServerPrivate(){}
private:
    TcpServer *q_ptr = nullptr;
    bool ownPool = false;
    ThreadPool* threadPool = nullptr;
};

TcpServer::TcpServer(int numThreads, bool createPool, QObject* parent)
    :QTcpServer(parent), d_ptr(new TcpServerPrivate(this))
{
    Q_D(TcpServer);
    if (numThreads <= 0)
        numThreads = std::thread::hardware_concurrency();
    d->ownPool = createPool;
    if (createPool) {
        ThreadPool * threadPool = new ThreadPool();
        if (threadPool) {
            d->threadPool = threadPool;
            threadPool->setNumThreads(numThreads);
            threadPool->start();
        }
    } else {
        s_serverCount++;
        if (!s_threadPool->isStarted())
        {
            s_threadPool->setNumThreads(numThreads);
            s_threadPool->start();
        }
    }
}

TcpServer::~TcpServer()
{
    Q_D(TcpServer);
    if (d->ownPool) {
        d->threadPool->stop();
        d->threadPool = nullptr;
    } else {
        s_serverCount--;
        if (s_serverCount<=0)
        {
            s_threadPool->stop();
        }
    }
}

void TcpServer::setNumThreads(int numThreads)
{
    s_threadPool->setNumThreads(numThreads);
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    Q_D(TcpServer);
    AbstractSocket *socket = createSocket();
    if (socket == nullptr) {

        return;
    }
    Connection * connection = new Connection(socketDescriptor);
    connection->setSocket(socket);
    if (d->ownPool) {
        d->threadPool->addTask(connection);
    } else {
        s_threadPool->addTask(connection);
    }
}

} // namespace tastefulserver

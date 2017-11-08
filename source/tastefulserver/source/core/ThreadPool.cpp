#include <thread>
#include <QList>
#include "ThreadPool.h"

#include <tastefulserver/Task.h>

namespace tastefulserver {

class ThreadPool;

class ThreadPoolPrivate {
    Q_DECLARE_PUBLIC(ThreadPool)
public:
    explicit ThreadPoolPrivate(ThreadPool* pool):q_ptr(pool)
    {

    }
    virtual ~ThreadPoolPrivate()
    {

    }

private:
    ThreadPool* q_ptr = nullptr;
    bool m_started = false;
    int m_threadCount = 0;
    unsigned m_next = 0;
    QList<TaskThread *> m_threads;
};

ThreadPool::ThreadPool(int numThreads)
    : d_ptr(new ThreadPoolPrivate(this))
{
    if (numThreads <= 0)
        numThreads = std::thread::hardware_concurrency();
    setNumThreads(numThreads);
}

void ThreadPool::setNumThreads(int numThreads)
{
    Q_D(ThreadPool);
    if (d->m_started)
    {
        return;
    }

    if (numThreads<=0)
    {
        numThreads = QThread::idealThreadCount();
        if (numThreads<0)
        {
            numThreads = 1;
        }
    }
    d->m_threadCount = numThreads;
}

bool ThreadPool::isStarted() const
{
    Q_D(const ThreadPool);
    return d->m_started;
}

void ThreadPool::start()
{
    Q_D(ThreadPool);
    if (d->m_started)
    {
        return;
    }

    for (int i = 0;i<d->m_threadCount;++i)
    {
        TaskThread * thread = new TaskThread();
        d->m_threads << thread;
        thread->start();
    }
    d->m_started = true;
}

void ThreadPool::stop()
{
    Q_D(ThreadPool);
    if (!d->m_started)
    {
        return;
    }

    for (TaskThread * thread : d->m_threads)
    {
        //thread->terminate();
        thread->quit();
        //thread->deleteLater();
        thread->wait();
        delete thread;
    }
    d->m_started = false;
}

ThreadPool::~ThreadPool()
{
    Q_D(ThreadPool);
    if (d->m_started)
    {
        stop();
    }
}

void ThreadPool::addTask(Task * task)
{
    Q_D(ThreadPool);
    d->m_threads[d->m_next]->addTask(task);
    d->m_next = (d->m_next + 1) % d->m_threadCount;
}

} // namespace tastefulserver

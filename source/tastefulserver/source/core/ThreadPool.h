#pragma once
#include <QScopedPointer>


namespace tastefulserver {

class Task;
class TaskThread;
class ThreadPoolPrivate;
class ThreadPool
{
public:
    ThreadPool(int numThreads = -1);
    ~ThreadPool();

    void setNumThreads(int numThreads);
    bool isStarted() const;
    void start();
    void stop();

    void addTask(Task * task);

protected:

private:
    Q_DECLARE_PRIVATE(ThreadPool)
    QScopedPointer<ThreadPoolPrivate> d_ptr;

};

} // namespace tastefulserver

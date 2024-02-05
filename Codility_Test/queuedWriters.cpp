//Q8
//Implement read write lock with priority for waiting writers
#include <mutex>
#include <condition_variable>

class RWLock
{
    std::mutex mutex;
    std::condition_variable waitingReaders;
    std::condition_variable waitingWriters;
    int readers = 0;
    int queuedWriters = 0;
    bool writer = false;

public:
    void readLock()
    {
        std::unique_lock<std::mutex> lock(mutex);
        waitingReaders.wait(lock, [&](){ !writer &&queuedWriters == 0 });
        ++readers;
    }
    void readUnlock()
    {
        std::unique_lock<std::mutex> lock(mutex);
        --readers;
        if (readers == 0 && queuedWriters > 0)
        {
            lock.unlock();
            waitingWriters.notify_one();
        }
    }
    void writeLock()
    {
        std::unique_lock<std::mutex> lock(mutex);
        ++queuedWriters;
        waitingWriters.wait(lock, [&]()
                            { !writer &&readers == 0 });
        --queuedWriters;
        writer = true;
    }
    void writeUnlock()
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (queuedWriters > 0)
        {
            lock.unlock();
            waitingWriters.notify_one();
        }
        else
        {
            writer = false;
            lock.unlock();
            waitingReaders.notify_all();
        }
    }
};
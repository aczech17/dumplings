#ifndef MONITOR_H
#define MONITOR_H

#include <windows.h>

class Semaphore
{
    friend class Condition;
    friend class Monitor;
    HANDLE sem;
    Semaphore(int value)
    {
        sem = CreateSemaphore(NULL, value, 1, NULL);
    }
    ~Semaphore()
    {
        CloseHandle(sem);
    }
    void wait()
    {
        WaitForSingleObject(sem, INFINITE);
    }
    void signal()
    {
        ReleaseSemaphore(sem, 1, NULL);
    }

};

class Condition
{
    friend class Monitor;
    Semaphore sem;
    unsigned int waitingCount;
public:
    Condition() : sem(0), waitingCount(0) {}
    void wait()
    {
        sem.wait();
    }
    bool signal()
    {
        if(waitingCount == 0)
            return false;
        waitingCount--;
        sem.signal();
        return true;
    }
};

class Monitor
{
    Semaphore mutex;
public:
    Monitor() : mutex(1) {}
    void enter()
    {
        mutex.wait();
    }
    void leave()
    {
        mutex.signal();
    }
    void wait(Condition& cond)
    {
        cond.waitingCount++;
        leave();
        cond.wait();
    }
    void signal(Condition& cond)
    {
        if(cond.signal())
            enter();
    }
};


#endif //MONITOR_H

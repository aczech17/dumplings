#ifndef MONITOR_H
#define MONITOR_H

#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

class Semaphore
{
    friend class Condition;
    friend class Monitor;
    sem_t sem;
    Semaphore(int value)
    {
        sem_init(&sem, 0, value); //0 means threads
    }
    ~Semaphore()
    {
        sem_destroy(&sem);
    }
    void wait()
    {
        sem_wait(&sem);
    }
    void signal()
    {
        sem_post(&sem);
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

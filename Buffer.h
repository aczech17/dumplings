#ifndef BUFFER_H
#define BUFFER_H

#include <queue>

template <typename dataType>
class Buffer
{
    Condition notFull;
    Condition notEmpty;
    Monitor monitor;

    std::queue <dataType> buff;
    unsigned int capacity;
public:
    explicit Buffer(unsigned int capacity) : capacity(capacity) {}

    void put(dataType data)
    {
        monitor.enter();
        if(buff.size() == capacity)
            monitor.wait(notFull);

        buff.push(data);

        if(buff.size() == 1)
            monitor.signal(notEmpty);

        monitor.leave();
    }

    dataType get()
    {
        monitor.enter();
        if(buff.size() == 0)
            monitor.wait(notEmpty);

        auto result = buff.front();
        buff.pop();

        if(buff.size() == capacity - 1)
            monitor.signal(notFull);

        monitor.leave();
        return result;
    }

    bool tryToGet(dataType& data)
    {
        monitor.enter();
        if(buff.size() == 0)
        {
            monitor.leave();
            return false;
        }

        data = buff.front();
        buff.pop();

        if(buff.size() == capacity - 1)
            monitor.signal(notFull);

        monitor.leave();
        return true;
    }//tryToGet
};

#endif //BUFFER_H

#include "util.h"

static unsigned int doughsMade = 0, doughsCount, fillingsPerProducer, dumplingsMade = 0;


void doughProducer(Buffer <Product>& doughBuffer)
{
    while(doughsMade < doughsCount)
    {
        doughBuffer.put(Product(dough));
        dumplingsMade++;
    }
}

void fillingProducer(Type type, Buffer <Product>& buffer)
{
    unsigned int fillingsMade = 0;
    while(fillingsMade < fillingsPerProducer)
    {
        buffer.put(Product(type));
        fillingsMade++;
    }
}

void dumplingProducer(bufVec& buffers)
{
    while(dumplingsMade < doughsCount)
    {
        auto nextDough = buffers[dough].get();
        bool fillingAvailable = false;
        for(int i = 1; i < 4; i++)
        {
            Product nextFilling(none);
            if(buffers[i].tryToGet(nextFilling))
            {
                fillingAvailable = true;
                std::cout << "Zrobiono pieroga z " << typeToString(nextFilling.type);
                break;
            }
        }//for
        if(!fillingAvailable)
        {
            buffers[dough].put(nextDough);
        }
    }//while
}


void gowno(int x)
{
    std::cout<<"szmata";
}


int main(int argc, char** argv)
{
    unsigned int bufferSize, fillingProducerCount;
    unsigned int doughProducerCount;

    if(argc < 5)
    {
        std::cin >> bufferSize >> doughProducerCount >> fillingProducerCount >> fillingsPerProducer;
    }
    else
    {
        bufferSize = atoi(argv[1]);
        doughProducerCount = atoi(argv[2]);
        fillingProducerCount = atoi(argv[3]);
        fillingsPerProducer = atoi(argv[4]);
    }
    doughsCount = fillingsPerProducer * fillingProducerCount;

    bufVec buffers;
    for(int i = 0; i < 4; i++)
        buffers.emplace_back(Buffer<Product>(bufferSize));

    for(unsigned int i = 0; i < doughProducerCount; i++)
    {
        std::thread doughThread(doughProducer, std::ref(buffers[dough]));
        doughThread.join();
    }

    for(unsigned int i = 0; i < fillingProducerCount; i++)
    {
        Type type = randomType();
        std::thread fillingThread(fillingProducer, type, std::ref(buffers[type]));
        fillingThread.join();
    }

}

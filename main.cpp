#include <iostream>
#include "Monitor.h"
#include "Buffer.h"
#include <vector>

static unsigned int doughsMade = 0, doughsCount, fillingsPerProducer, dumplingsMade = 0;

enum Type
{
    dough, meat, cheese, cole, none
};

std::string typeToString(Type& type)
{
    switch(type)
    {
        case dough:
            return "dough";
        case meat:
            return "meat";
        case cheese:
            return "cheese";
        case cole:
            return "cole";
        default:
            return "";
    }
}

struct Product
{
    Type type;
public:
    explicit Product(Type type) : type(type) {}
    Product(Product& product) = default;
};

typedef std::vector<Buffer<Product>> bufVec;

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


}

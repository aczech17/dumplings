#include <iostream>
#include "Monitor.h"
#include "Buffer.h"


static unsigned int dumplingsCount, fillingsPerProducer, doughsMade = 0, dumplingsMade = 0;

enum Type
{
    dough, meat, cheese, cole
};

class Product
{
    Type type;
public:
    Product(Type type) : type(type) {}
    Product(Product& product) : type(product.type) {}
};

void doughProducer(Buffer <Product>& doughBuffer)
{
    while(dumplingsMade < dumplingsCount)
    {
        doughBuffer.put(Product(dough));
        dumplingsMade++;
    }
}

int main(int argc, char** argv)
{
    unsigned int bufferSize, fillingProducerCount;
    unsigned int doughProducerCount;

    bufferSize = atoi(argv[1]);
    doughProducerCount = atoi(argv[2]);
    fillingProducerCount = atoi(argv[3]);
    fillingsPerProducer = atoi(argv[4]);

    dumplingsCount = fillingsPerProducer * fillingProducerCount;
}

#ifndef DUMPLINGS_UTIL_H
#define DUMPLINGS_UTIL_H

#include <iostream>
#include "Monitor.h"
#include "Buffer.h"
#include <vector>
#include <cstdlib>
#include <thread>
#include <random>

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
};

typedef std::vector<Buffer<Product>> bufVec;

Type randomType()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1, 3);

    Type result = (Type)distribution(rng);
    return result;
}
#endif //DUMPLINGS_UTIL_H

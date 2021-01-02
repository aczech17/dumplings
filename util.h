#ifndef DUMPLINGS_UTIL_H
#define DUMPLINGS_UTIL_H

#include <iostream>
#include "Monitor.h"
#include "Buffer.h"
#include <vector>
#include <cstdlib>
#include <thread>

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
#endif //DUMPLINGS_UTIL_H

#ifndef DUMPLINGS_UTIL_H
#define DUMPLINGS_UTIL_H

#include <iostream>
#include "Monitor.h"
#include "Buffer.h"
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <random>
#include <fstream>

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
            return "INVALID";
    }
}

struct Product
{
    Type type;
public:
    explicit Product(Type type) : type(type) {}
};

typedef std::vector<Buffer<Product>> bufVec;
typedef std::vector<pthread_t> threadVec;

template <typename randomType>
randomType getRandom()
{
	std::ifstream randomFile("/dev/urandom");
	randomType result = 0;
	char buff;
	for(size_t i = 0; i < sizeof(randomType); i++)
	{
		randomFile.get(buff);
		result |= (buff << (8*(sizeof(randomType) - i - 1)));
	}
	randomFile.close();
	return result;
}

#endif //DUMPLINGS_UTIL_H

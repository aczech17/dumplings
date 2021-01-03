#include "util.h"
#include <memory>

unsigned int doughsMade = 0, doughsCount, fillingsPerProducer, dumplingsMade = 0;


void doughProducer(Buffer <Product>& doughBuffer)
{
	std::cout << "Dough producer start\n";
    while(doughsMade < doughsCount)
    {
		std::cout << "Trying to make dough\n";
        doughBuffer.put(Product(dough));
        doughsMade++;
        std::cout << doughsMade << " doughs made\n";
    }
    std::cout << "Dough producer end\n";
}

void fillingProducer(Type type, Buffer <Product>& buffer)
{
	std::cout << typeToString(type) << " producer start\n";
    unsigned int fillingsMade = 0;
    while(fillingsMade < fillingsPerProducer)
    {
        buffer.put(Product(type));
        fillingsMade++;
        std::cout << fillingsMade << " " << typeToString(type) << " made\n";
    }
}

void dumplingProducer(bufVec& buffers)
{
	std::cout << "Dumpling producer start\n";
    while(dumplingsMade < doughsMade)
    {
		std::cout << "Trying to get dough\n";
        auto nextDough = buffers[dough].get();
        std::cout << "Got dough\n";
        
        bool fillingAvailable = false;
        for(int i = 1; i < 4 && !fillingAvailable; i++)
        {
			Product nextFilling(none);
			if(buffers[i].tryToGet(nextFilling))
			{
				fillingAvailable = true;
				dumplingsMade++;
				Type type = (Type)i;
				std::cout << "Made dumpling with " << typeToString(type) << ". ";
				std::cout << dumplingsMade << " dumplings made.\n";
			}
		}
		if(!fillingAvailable)
		{
			buffers[dough].put(nextDough);
			std::cout << "Dough returned\n";
		}
    }//while
    std::cout << "Dumpling producer end\n";
}


void* doughProducerT(void * doughBuffer)
{
	Buffer <Product>& buffer = *(Buffer<Product>*)doughBuffer;
	doughProducer(buffer);
	
	return NULL;
}

void* fillingProducerT(void * args)
{
	auto args_pair = *(std::pair<Type, Buffer<Product>&>*)args;
	auto type = args_pair.first;
	auto& buffer = args_pair.second;
	fillingProducer(type, buffer);
	
	return NULL;
}

void* dumplingProducerT(void * buffersArg)
{
	bufVec buffers = *(bufVec*)buffersArg;
	dumplingProducer(buffers);
	
	return NULL;
}

int main(int argc, char** argv)
{
    unsigned int bufferSize, fillingProducerCount;
    unsigned int doughProducerCount, dumplingProducerCount;

    if(argc < 6)
    {
        std::cin >> bufferSize;
        std::cin >> doughProducerCount;
        std::cin >> fillingProducerCount;
        std::cin >> fillingsPerProducer;
        std::cin >> dumplingProducerCount;
    }
    else
    {
        bufferSize = atoi(argv[1]);
        doughProducerCount = atoi(argv[2]);
        fillingProducerCount = atoi(argv[3]);
        fillingsPerProducer = atoi(argv[4]);
        dumplingProducerCount = atoi(argv[5]);
        
    }
    doughsCount = fillingsPerProducer * fillingProducerCount;
    
    std::cout << doughsCount << " dumplings to be made\n";

    bufVec buffers;
    for(int i = 0; i < 4; i++)
        buffers.emplace_back(Buffer<Product>(bufferSize));

	
    threadVec doughThreads, fillingThreads, dumplingThreads;
    for(unsigned i = 0; i < doughProducerCount; i++)
    {
		auto thread = std::make_shared<pthread_t>();
		doughThreads.push_back(*thread);
		pthread_create(&doughThreads[i], NULL, doughProducerT, (void *)(&buffers[dough]));
	}
	
	for(unsigned i = 0; i < fillingProducerCount; i++)
	{
		Type type = (Type)(getRandom<unsigned int>() % 3 + 1);
		auto args = std::pair<Type, Buffer<Product>&>(type, buffers[type]);
		auto thread = std::make_shared<pthread_t>();
		fillingThreads.push_back(*thread);
		pthread_create(&fillingThreads[i], NULL, fillingProducerT, (void*)(&args));
	}
	
	for(unsigned i = 0; i < dumplingProducerCount; i++)
	{
		auto thread = std::make_shared<pthread_t>();
		dumplingThreads.push_back(*thread);
		pthread_create(&dumplingThreads[i], NULL, dumplingProducerT, (void*)(&buffers));
	}
	
	for(unsigned i = 0; i < doughProducerCount; i++)
		pthread_join(doughThreads[i], NULL);
		
	for(unsigned i = 0; i < fillingProducerCount; i++)
		pthread_join(fillingThreads[i], NULL);
		
	for(unsigned i = 0; i < doughProducerCount; i++)
		pthread_join(dumplingThreads[i], NULL);
		
}

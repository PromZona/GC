// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "GC.h"

using namespace GarbageCollector;

GC::~GC()
{

}

size_t GC::GetMaxSize()
{
    return maxSize;
}

void GC::DeAlloc(IPtr p)
{
    for (std::vector<IPtr>::iterator it = allocs.begin(); it != allocs.end(); it++)
    {
        if (it->object == p.object)
        {
            std::cout << "hit\n";
            delete p.object;
            currentSize -= it->size;
            it = allocs.erase(it);
        }
    }
}

void GC::PrintMemAllocs()
{
    std::cout << "\tALLOCS\n";
    std::cout << "\tcurrent size - " << currentSize << "; objects - " << allocs.size() << std::endl;
    for (int i = 0; i < allocs.size(); i++)
    {
        std::cout << "\t" << allocs[i].object << ": " << allocs[i].size << " byte; parent: ";
        if (allocs[i].parent != nullptr)
        {
            std::cout << allocs[i].parent->object << std::endl;
        }
        else
        {
            std::cout << " nullptr\n";
        }
    }
}

size_t GC::GetCurrentSize()
{
    return currentSize;
}

void GC::init()
{
    currentSize = 0;
}

void GC::Collect()
{
    Mark();
    Sweep();
}

void GC::Mark()
{
    for (auto it : allocs)
    {
        it.flag = false;
    }

    for (auto it : allocs)
    {
        if (it.parent != &gcnull || it.parent == &root)
        {
            it.flag = true;
        }
    }

    std::cout << "marks: \n";
    for (auto it : allocs)
    {
        int a = 0;
        if (it.flag) a = 1;
        std::cout << it.object << ": " << a << std::endl;
    }
}
void GC::Sweep()
{

}
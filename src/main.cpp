// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "GC.h"

using namespace GarbageCollector;

class B
{
public:
    double value;
    ptr<B> object;
};

class A
{
public:
    int value;
    ptr<B> object1;
    ptr<B> object2;
};


int main()
{
    GC gc;
    gc.init();

    gc.PrintMemAllocs();

    ptr<A> p;
    gc.Alloc<A>(&p);
    p->value = 100;
    gc.Alloc<B>(&(p->object1), &p);
    gc.Alloc<B>(&(p->object2), &p);
    gc.Alloc<B>(&(p->object1->object), &(p->object1));

    std::cout << p->value << std::endl;
    std::cout << p->object1 << std::endl;

    p->object1 = nullptr;

    gc.PrintMemAllocs();

    gc.Collect();

    /* 
    std::vector<ptr<A>> datas;
    datas.reserve(20);
    for (int i = 0; i < 20; i++)
    {
        ptr<A> p;
        A* str = (A*)gc.Alloc(sizeof(A));
        p.object = (void*)str;
        str->a = 1;
        str->b = 2;
        str->c = 3;
        str->d = 4;
        datas.push_back(p);
    }
    gc.PrintMemAllocs();
    
    std::vector<ptr<A>>::iterator it = datas.begin() + 10;
    ptr<A> p1 = datas.at(10);
    std::vector<ptr<A>>::iterator it1 = datas.erase(it);
    gc.PrintMemAllocs();

    for (auto d : datas)
    {
        ((A*)d.object)->print();
    }
    */

    return 0;
}
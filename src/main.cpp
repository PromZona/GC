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

    void print()
    {
        std::cout << "value: " << value << std::endl;
    }
};


int main()
{
    /* ----------------------
        Инициализация
    -------------------------*/
    GC gc;
    gc.init();


    /* ----------------------
        Объявление
    -------------------------*/
    ptr<int> testInt;
    ptr<double> testDouble;
    gc.Alloc(&testInt);
    gc.Alloc(&testDouble);
    *testInt = 42; // Good number
    *testDouble = 43; // Just number
    std::cout << "testInt = " << *testInt << std::endl;
    std::cout << "testDouble = " << *testDouble<< std::endl;


    /* ----------------------
        Информация о выделенной памяти
    -------------------------*/
    gc.PrintMemAllocs();

    
    /* ----------------------
        Пример с контейнерами
    -------------------------*/
    /**/
    std::vector<ptr<A>> datas;
    datas.reserve(20);
    for (int i = 0; i < 20; i++)
    {
        ptr<A> n;
        gc.Alloc<A>(&n);
        n->value = i;
        datas.push_back(n);
    }
    gc.PrintMemAllocs();

    for (auto d : datas)
    {
        ((A*)d.object)->print();
    }
    
    

    /* ----------------------
        Самое интересное
        вложенные указатели
    -------------------------*/
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


    return 0;
}
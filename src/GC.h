// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#pragma once

#include <vector>
#include <iostream>

namespace GarbageCollector
{
    class GC;

    class IPtr
    {
    public:
        void* object;
        IPtr* parent;
        GC* gc;
        int size{ 0 };
        bool flag = false;
    };

    static IPtr* root;
    static IPtr* gcnull;

    template<class T>
    class ptr : public  IPtr
    {
    public:

        ptr()
        {
            object = nullptr;
            parent = nullptr;
        }

        ptr(void* parentP, void* obj) : parent(parentP), object(obj)
        {
        }

        ~ptr()
        {
        }

        operator T* ()
        {
            return (T*)object;
        }

        T* operator->()
        {
            return (T*)object;
        }

        T& operator*()
        {
            return *(T*)object;
        }

        const T& operator*() const
        {
            return *(T*)object;
        }

        ptr<T>& operator=(const ptr<T>& other)
        {
            return *this;
        }

        ptr<T>& operator=(T* other)
        {
            if (other == nullptr)
            {
                parent = gcnull;
                // (*this).parent = &gcnull;
                return *this;
            }
            object = other;
            return *this;
        }
    };

    class GC
    {
    public:
        GC(size_t max) : maxSize(max), currentSize(0) {}
        GC() : GC::GC(50000) {}
        ~GC();

        size_t GetMaxSize();
        size_t GetCurrentSize();

        template<class T>
        void Alloc(ptr<T>* pointer);

        template<class T, class G>
        void Alloc(ptr<T>* pointer, ptr<G>* parent);

        void DeAlloc(IPtr p);
        void PrintMemAllocs();

        void init();

        void Collect();
    private:

        void Mark();
        void Sweep();
        size_t maxSize; // bytes
        size_t currentSize; // bytes
        // std::vector<IPtr> allocs;
        std::vector<IPtr*> allocs;
    };

    template<class T>
    void GC::Alloc(ptr<T>* pointer)
    {
        size_t size = sizeof(T);
        void* mem = ::operator new(size);

        pointer->object = (T*)mem;
        pointer->size = size;

        pointer->gc = this;

        pointer->parent = root;

        // allocs.push_back((IPtr)*pointer);
        allocs.push_back((IPtr*)pointer);
        currentSize += size;
        return;
    }

    template<class T, class G>
    void GC::Alloc(ptr<T>* pointer, ptr<G>* parent)
    {
        size_t size = sizeof(T);
        void* mem = ::operator new(size);

        pointer->object = (T*)mem;
        pointer->size = size;

        pointer->gc = this;

        pointer->parent = parent;

        // allocs.push_back((IPtr)*pointer);
        allocs.push_back((IPtr*)pointer);
        currentSize += size;
        return;
    }
}
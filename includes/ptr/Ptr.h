#ifndef PTR_H
#define PTR_H

#include "../globals/globals.h"

template<typename T>
class Ptr
{
public:
    Ptr<T>(){}

    Ptr<T>(int index, int num) : _index(index), _num(num) {}

    void _new(int num = 1)
    {
        _index = _memory.allocate(num * sizeof(T));
        _num = num;
    }
    
    void _delete(bool brackets = false)
    {
        if (!brackets) _memory.deallocate(_index, sizeof(T));
        else _memory.deallocate(_index, _num * sizeof(T));
        _index = -1;
        _num = 0;
    }

    // prefix increment
    Ptr<T>& operator++()
    {
        _index += sizeof(T);
        return *this;
    }

    // postfix increment
    Ptr<T> operator++(int)
    {
        Ptr<T> ptr(_index, _num);
        _index += sizeof(T);
        return ptr;
    }

    T& operator*()
    {
        return *(T*)_memory.get_index(_index);
    }

    T const operator*() const
    {
        return *(T*)_memory.get_index(_index);
    }
    
    int operator&() const
    {
        return _index;
    }

    void operator=(const Ptr<T> &rhs)
    {
        _index = rhs._index;
        _num = rhs._num;
    }

    bool null() const
    {
        return _index == -1;
    }

    void set_null()
    {
        _index = -1;
        _num = 0;
    }

    bool operator!() const
    {
        return null();
    }

    T* operator->() const
    {
        return (T*)_memory.get_index(_index);
    }

    friend ostream& operator<<(ostream& os, Ptr<T> const& ptr)
    {
        os << ptr._index;
        return os;
    }
    
    friend bool operator==(Ptr<T> const &lhs, Ptr<T> const &rhs)
    {
        return lhs._index == rhs._index;
    }

    friend Ptr<T> operator+(Ptr<T> const& ptr, int const& steps)
    {
        Ptr<T> temp(ptr._index + sizeof(T) * steps, ptr._num);
        return temp;
    }

    friend Ptr<T> operator-(Ptr<T> const& ptr, int const& steps)
    {
        Ptr<T> temp(ptr._index - sizeof(T) * steps, ptr._num);
        return temp;
    }

private:
    int _index = -1;        // starting index    
    int _num = 0;           // num of T if an array
};

#endif // PTR_H
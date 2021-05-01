#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <array>
#include <cassert>
#include <string>
#include "../constants/Constants.h"
#include "../serialize/serialize.h"
using namespace std;
using byte = unsigned char;

class Memory
{
public:
    // PURPOSE: constructor
    Memory();
    // PURPOSE: allocate from start for bytes, return new start
    int allocate(int bytes); 
    // PURPOSE: deallocate from start for bytes
    void deallocate(int start, int bytes);
    // PURPOSE: store byte array from start
    template<typename T> 
    void store(const int start, T object)
    {
        array<byte, sizeof(T)> bytes = serialize(object);
        int index = 0;
        for (int i = start; i < start + sizeof(T); i++)
        {
            assert(!_allocated[i] && "Attempting to store in unallocated space!");
            _memory[i] = bytes[index++];
        }
    }
    // PURPOSE: retrieve byte array
    template<typename T>
    void retrieve(int start, T& object)
    {
        array<byte, sizeof(T)> bytes;
        for (int i = start; i < start + sizeof(T); i++)
            bytes[i - start] = _memory[i];
        deserialize(bytes, object);
    }
    // PURPOSE: print memory and allocated
    void print(int start, int bytes);
    // PURPOSE: print all ALLOCATED memory within given space
    void print_allocated(int start = 0, int bytes = CAPACITY);
    // PURPOSE: reset memory
    void reset();
    // PURPOSE: get array spot at index
    byte* get_index(int index);
private:
    // PURPOSE: the next free index in memory
    int _index = 0;
    // PURPOSE: memory
    byte _memory[CAPACITY];
    // PURPOSE: indicates if memory is allocated at index i
    bool _allocated[CAPACITY] = {false};
    // PURPOSE: toggle allocated array to value
    void set_allocated(int start, int spaces, bool value);
    // PURPOSE: find next unallocated index that can hold space_needed
    int next_free_index(int index, int space_needed);
    // PURPOSE: find next unallocated index
    int next_free_index(int index);
    // PURPOSE: has enough memory at _free_index
    bool has_space(int index, int spaces);
    // PURPOSE: clear memory from start to start + bytes
    void clear(int start, int bytes);
};

#endif // MEMORY_H
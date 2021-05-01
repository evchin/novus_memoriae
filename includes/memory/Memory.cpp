#include "Memory.h"

// PURPOSE: constructor
Memory::Memory(){}

// PURPOSE: allocate from start for max_size * num_ptrs, return new start
int Memory::allocate(int bytes)
{
    int start = next_free_index(_index, bytes);     // get next free index
    set_allocated(start, bytes, true);              // set allocated[] 
    _index = next_free_index(start + bytes);        // set _index to free index
    return start;
}

// PURPOSE: deallocate from start for max_size * num_ptrs
void Memory::deallocate(int start, int bytes)
{
    set_allocated(start, bytes, false);     // set allocated array to 0
    clear(start, bytes);      // clear memory of deallocated
}

// PURPOSE: find next unallocated index
int Memory::next_free_index(int index, int space_needed)
{
    int new_index = index;
    int crossed_capacity = 0;
    while (!has_space(new_index, space_needed) && crossed_capacity < 2)
    {
        new_index += space_needed;
        if (new_index >= CAPACITY)
        {
            crossed_capacity++;
            new_index %= CAPACITY;
        }
        new_index = next_free_index(new_index);
    }
    if (crossed_capacity > 1) assert(false && "Out of memory.");
    return new_index;
}

// PURPOSE: find next unallocated index
int Memory::next_free_index(int index)
{
    int new_index = index;
    for (int i = new_index; i < new_index + CAPACITY; i++)
    {
        if (!_allocated[i % CAPACITY])
        {
            new_index = i % CAPACITY;
            return new_index;
        }
    }
    assert(false && "Out of memory.");
    return -1;
}

// PURPOSE: has enough memory at index
bool Memory::has_space(int index, int spaces)
{
    int availables = 0;
    for (int i = index; i < CAPACITY; i++)
    {
        if (_allocated[i]) return availables >= spaces;
        availables++;
        if (availables >= spaces) return true;
    }
    assert(false && "You have run out of space.");
    return false;
}

// PURPOSE: set allocated array
void Memory::set_allocated(int start, int spaces, bool value)
{
    for (int i = start; i < start + spaces; i++)
        _allocated[i] = value;
}

// PURPOSE: print memory and allocated
void Memory::print(int start, int bytes)
{
    cout << "Address\t\tMemory\t\tAllocated" << endl;
    for (int i = start; i < start + bytes; i++)
        cout << i << ":\t\t" << _memory[i] << "\t\t" << _allocated[i] << endl;
    cout << endl << "Next Free Index: " << _index << endl << endl;
}

// PURPOSE: print all ALLOCATED memory within given space
void Memory::print_allocated(int start, int bytes)
{
    if (bytes == CAPACITY) bytes = _index;
    cout << "Address\t\tMemory\t\tAllocated" << endl;
    for (int i = start; i < start + bytes; i++)
        if (_allocated[i])
            cout << i << ":\t\t" << _memory[i] << "\t\t" << _allocated[i] << endl;
    cout << endl << "Next Free Index: " << _index << endl << endl;
}

// PURPOSE: reset memory
void Memory::reset()
{
    set_allocated(0, CAPACITY, false);
    clear(0, CAPACITY);
    _index = 0;
}

// PURPOSE: clear memory from start to start + size
void Memory::clear(int start, int bytes)
{
    for (int i = start; i < start + bytes; i++) _memory[i] = ' ';
}

// PURPOSE: get array spot at index
byte* Memory::get_index(int index)
{
    return _memory + index;
}
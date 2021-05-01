#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <iostream>
#include <array>
using namespace std;
using byte = unsigned char;

template<typename T>
array<byte, sizeof(T)> serialize(const T& object)
{
    array<byte, sizeof(T)> bytes;   // initialize byte array
    const byte* begin = reinterpret_cast<const byte*>(addressof(object)); // get beginning address
    const byte* end = begin + sizeof(T);    // get end address
    copy(begin, end, begin(bytes));         // copy into byte array
    return bytes;
}

template<typename T>
T& deserialize(const array<byte, sizeof(T)>& bytes, T& object)
{
    // ensure is trivially copyable
    static_assert(is_trivially_copyable<T>::value, "not a TriviallyCopyable type");
    byte* begin_object = reinterpret_cast<byte*>(addressof(object));    // get beginning of out object
    copy(begin(bytes), end(bytes), begin_object);       // copy into out object
    return object;
}

// template<typename T>
// array<byte, sizeof(Ptr<T>)> serialize(const Ptr<T>& object);
// template<typename T>
// Ptr<T>& deserialize(const array<byte, sizeof(Ptr<T>)>& bytes, Ptr<T>& object);

// template<typename T>
// array<byte, sizeof(tree_node<T>)> serialize(const tree_node<T>& object);
// template<typename T>
// tree_node<T>& deserialize(const array<byte, sizeof(tree_node<T>)>& bytes, tree_node<T>& object);

#endif // SERIALIZE_H
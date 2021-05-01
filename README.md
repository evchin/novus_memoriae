# **Novus Memoriae**

## About

Novus Memoriae is a library that redefines the infamous C++ pointer into an entirely new class. The `Ptr` operates in the same way as the original C++ pointer (besides some syntax differences). However, instead of within the RAM, all memory is saved in a byte array, within the `Memory` class; this makes memory portable. See detailed usage and class structure below.

Thank you to Professor Barkeshli for the project idea and structural guidance. :)  

## Features

<h3>Fundamental Classes</h3>
<ul>
    <li><code>Constants</code> stores the capacity of our memory.</li>
    <li><code>Globals</code> initiates our memory array as a global variable.
        <ul>
            <li><code>array<byte, sizeof(T)> serialize(const T& object)</code> serializes a given templated object into a byte array.</li>
            <li><code>T& deserialize(const array<byte, sizeof(T)>& bytes, T& object)</code> deserializes a given byte array into an objectdeserializes byte array into an object.</li>
        </ul>
    </li>
    <li><code>Serialize</code> is a collection of functions for serialization and deserialization of objects.</li>
</ul>
<h3>Secondary Classes</h3>
<ul>
    <li><code>Memory</code> manipulates our "memory" directly. It gets its hands dirty in all of the array indexing and data navigation.
        <ul>
            <li>Memory Variables</li>
            <ul>
                <li><code>int _index</code> is the next free index in memory.</li>
                <li><code>byte _memory[CAPACITY]</code> acts as the memory itself.</li>
                <li><code>bool _allocated[CAPACITY]</code> indicates if memory is allocated at index i of <code>_memory</code>.</li>
            </ul>
        </ul>
        <ul>
            <li>Public Methods</li>
            <ul>
                <li><code>int allocate(int bytes)</code> allocates memory with a size of <code>bytes</code>, returning the starting index of the object.</li>
                <li><code>void deallocate(int start, int bytes)</code> deallocates memory from <code>start</code> for a size of <code>bytes</code>.</li>
                <li><code>void store(const int start, T object)</code> stores <code>object</code> in memory starting from index <code>start</code>.</li>
                <li><code>void retrieve(int start, T& object)</code> retrieves a byte array from index <code>start</code> and stores it in <code>object</code>.</li>
                <li><code>void print(int start, int size)</code> prints the <code>_memory</code> and <code>_allocated</code> arrays.</li>
                <li><code>void print_allocated(int start = 0, int bytes = CAPACITY)</code> prints the <code>_allocated</code> array only.</li>
                <li><code>void reset()</code> resets <code>_memory</code> and <code>_allocated</code> such that nothing is stored.</li>
                <li><code>byte* get_index(int index)</code> returns the index of an array at <code>index</code>.</li>
            </ul>
        </ul>
        <ul>
            <li>Private Methods</li>
            <ul>
                <li><code>int next_free_index(int index, int space_needed)</code> finds the next unallocated index that can hold <code>space_needed</code>.</li>
                <li><code>int next_free_index(int index)</code> finds the next unallocated index.</li>
                <li><code>bool has_space(int index, int spaces)</code> returns true if there are at least <code>spaces</code> that are unallocated at <code>_free_index</code>.</li>
                <li><code>void set_allocated(int start, int spaces, bool value)</code> sets the spots from <code>start</code> to <code>start + spaces</code> in <code>_allocated</code> to <code>value</code>.</li>
                <li><code>void clear(int start, int spaces)</code> clears the memory from <code>start</code> to <code>start + size</code></li>
            </ul>
        </ul>
    </li>
    <li><code>Ptr</code> is our substitute for the C++ pointer.
        <ul>
            <li>Member Variables</li>
            <ul>
                <li><code>int _index</code> is the index of a pointer in the memory array.</li>
                <li><code>int _num</code> is the number of T objects there are if the pointer is the beginning of an array.</li>
            </ul>
        </ul>
        <ul>
            <li>Public Methods</li>
            <ul>
                <li><code>void _new(int num = 1)</code> allocates a number <code>num</code> of object Ts in memory.</li>
                <li><code>void _delete(bool brackets = false)</code> deallocates objects in memory, where brackets represents the syntax <code>delete [] object;</code></li>
                <li><code>Ptr<T>& operator++()</code> overloads the prefix increment.</li>
                <li><code>Ptr<T> operator++(int)</code> overloads the postfix increment.</li>
                <li><code>T& operator*()</code> overloads the dereferencing operator that returns the item by reference.</li>
                <li><code>T const operator*() const</code> overloads the dereferencing operator that returns the item by value.</li>
                <li><code>int operator&()</code> returns the Ptr's address. Normally, this would be a memory address, but in our case, it is an array index.</li>
                <li><code>void operator=(const Ptr<T> &rhs)</code> overloads the assignment operator.</li>
                <li><code>bool null() const</code> returns true if the Ptr is considered a "nullptr".</li>
                <li><code>bool operator! ()</code> returns true if the Ptr is considered a "nullptr".</li>
                <li><code>void set_null()</code> sets the Ptr to a "nullptr" (equivalent to <code>ptr = nullptr;</code>)</li>
                <li><code>T* operator->()</code> overloads the right arrow operator.</li>
                <li><code>friend Ptr<T> operator+(Ptr<T> const& ptr, int const& steps)</code> performs pointer arithmetic and returns the resultant pointer.</li>
                <li><code>friend ostream& operator<<(ostream& os, Ptr<T> const& ptr)</code> prints the array index as the "memory address".</li>
                <li><code>friend bool operator==(Ptr<T> const &lhs, Ptr<T> const &rhs)</code> overloads the == operator.</li>
            </ul>
        </ul>
    </li>
</ul>

**Files for Testing Purposes**: 

- `BST`: Binary Search Tree Class
- `BST Functions`: BST functions that support BST class

# **output**

## Pointer Class Driver Program:
```cpp
struct item
{
  item(int a) : _a(a) {}
  int _a = 0;
  friend ostream& operator<<(ostream& os, item const& i)
  {
    os << "A Printed Item.";
    return os;
  }
};

int main()
{
  // create pointers
  Ptr<int> p1;
  Ptr<int> array;
  Ptr<item> itemPtr;

  // allocate memory
  p1._new();                      // allocates one spot
  array._new(5);                  // allocates five spots
  itemPtr._new();                 // allocates one spot
  cout << "Allocated Pointers." << endl;
  cout << "P1:\t\tAddress: " << p1 << "\tItem: " << *p1 << endl;
  cout << "Array:\t\tAddress: " << array << "\tItem: " << *array << endl;
  cout << "ItemPtr:\tAddress: " << itemPtr << "\tItem: " << *itemPtr << endl << endl;

  *p1 = -12367890;                // assign p1's value as -1234567890
  *array = 123;                   // assign first value of array
  *(array + 1) = 1;               // assign index 1 of 'array' to 1
  *(++array) = 1;                 // assign index 1 of 'array' to 1 (again)
  *(array++) = 1;                 // assign index 1 of 'array' to 1 (again)
  array = array - 2;              // return array to original index
  *(array + 2) = 2;               // assign index 2 of 'array' to 2
  *(array + 3) = 3;               // assign index 3 of 'array' to 3
  *itemPtr = item(5);             // assign itemPtr value to a

  cout << "Assigned Pointers." << endl;
  cout << "P1:\t\tAddress: " << p1 << "\tItem: " << *p1 << endl;
  cout << "Array:\n";
  for (int i = 0; i < 5; i++)
    cout << "Index: " << i << "\t\tAddress: " << array + i << "\tItem: " << *(array + i) << endl;
  cout << "ItemPtr:\tAddress: " << itemPtr << "\tItem: " << *itemPtr << endl;
  cout << "Item's I using arrow operator: " << itemPtr->_a << endl << endl;
  _memory.print_allocated();

  // deallocate all
  bool brackets = true;
  p1._delete();                       // deallocates space for p1
  array._delete(brackets);            // deallocates space for ENTIRE array
  itemPtr._delete();                  // deallocates space for itemPtr
  _memory.print_allocated();
  
  return 0;
}
```

## Output:
```
Allocated Pointers.
P1:             Address: 0      Item: 0
Array:          Address: 4      Item: 0
ItemPtr:        Address: 24     Item: A Printed Item.

Assigned Pointers.
P1:             Address: 0      Item: -12367890
Array:
Index: 0                Address: 4      Item: 123
Index: 1                Address: 8      Item: 1
Index: 2                Address: 12     Item: 2
Index: 3                Address: 16     Item: 3
Index: 4                Address: 20     Item: 0
ItemPtr:        Address: 24     Item: A Printed Item.
Item's I using arrow operator: 5

Address         Memory          Allocated
0:              ε               1
1:              G               1
2:              C               1
3:                              1
4:              {               1
5:                              1
6:                              1
7:                              1
8:              ☺               1
9:                              1
10:                             1
11:                             1
12:             ☻               1
13:                             1
14:                             1
15:                             1
16:             ♥               1
17:                             1
18:                             1
19:                             1
20:                             1
21:                             1
22:                             1
23:                             1
24:             ♣               1
25:                             1
26:                             1
27:                             1

Next Free Index: 28

Address         Memory          Allocated

Next Free Index: 28
```

## Basic Test Output:
```
----------running basic_test.cpp---------


[==========] Running 2 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from TEST_RANDOM
[ RUN      ] TEST_RANDOM.TestRandom


ROLLING:
  6  5  5  1  3
  6  4  6  3  1
  1  4  5  3  6
  1  1  5  2  1
  4  4  3  2  5


---- end test random --------
[       OK ] TEST_RANDOM.TestRandom (3 ms)
[----------] 1 test from TEST_RANDOM (3 ms total)

[----------] 1 test from TEST_BST
[ RUN      ] TEST_BST.TestBST
here is the tree:
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
       [13]
           [12]
               [11]
[10]
           [9]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]
           [1]
               [0]



insert():
               [48]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
       [13]
           [12]
               [11]
[10]
           [9]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]
           [1]
               [0]

----------------------------
               [48]
                   [45]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
       [13]
           [12]
               [11]
[10]
           [9]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]
           [1]
               [0]

----------------------------
               [48]
                   [45]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]
           [1]
               [0]

----------------------------
               [48]
                   [45]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
               [8]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]
           [1]
               [0]

----------------------------
               [48]
                   [45]
                       [38]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
               [8]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]
           [1]
               [0]

----------------------------


search:
ERASING 0
ERASING 0
ERASING 0
ERASING 0
ERASING 0
bst2 after erasing [0]
               [48]
                   [45]
                       [38]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
               [8]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]
           [1]

----------------------------
ERASING 1
ERASING 1
ERASING 1
ERASING 1
bst2 after erasing [1]
               [48]
                   [45]
                       [38]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
               [8]
       [8]
           [7]
               [6]
   [5]
           [4]
               [3]
       [2]

----------------------------
ERASING 2
ERASING 2
ERASING 2
bst2 after erasing [2]
               [48]
                   [45]
                       [38]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
               [8]
       [8]
           [7]
               [6]
   [5]
       [4]
           [3]

----------------------------
ERASING 3
ERASING 3
ERASING 3
ERASING 3
bst2 after erasing [3]
               [48]
                   [45]
                       [38]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
               [8]
       [8]
           [7]
               [6]
   [5]
       [4]

----------------------------
ERASING 4
ERASING 4
ERASING 4
bst2 after erasing [4]
               [48]
                   [45]
                       [38]
           [19]
       [18]
           [17]
               [16]
   [15]
           [14]
               [13]
       [13]
           [12]
               [11]
[10]
           [9]
               [8]
       [8]
           [7]
               [6]
   [5]

----------------------------


traversals(bst):
pre-order:  [10][5][2][1][0][4][3][8][7][6][9][8][15][13][12][11][14][13][18][17][16][19][48][45][38]
in-order:   [0][1][2][3][4][5][6][7][8][8][9][10][11][12][13][13][14][15][16][17][18][19][38][45][48]
post-order: [0][1][3][4][2][6][7][8][9][8][5][11][12][13][14][13][16][17][38][45][48][19][18][15][10]


BST::operator+=( )

bst += bst2 (because why not!):
bst after add:                    [48]
               [48]
                       [45]
                   [45]
                           [38]
                       [38]
                           [19]
           [19]
               [18]
       [18]
               [17]
           [17]
                   [16]
               [16]
                   [15]
   [15]
               [14]
           [14]
                       [13]
                   [13]
               [13]
       [13]
               [12]
           [12]
                   [11]
               [11]
                   [10]
[10]
               [9]
           [9]
                       [8]
                   [8]
               [8]
       [8]
               [7]
           [7]
                   [6]
               [6]
                   [5]
   [5]
           [4]
               [3]
       [2]
           [1]
               [0]



clear bst2:
[       OK ] TEST_BST.TestBST (583 ms)
[----------] 1 test from TEST_BST (583 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 2 test suites ran. (589 ms total)
[  PASSED  ] 2 tests.
```

## TestB Output:
```
----------running testB.cpp---------


[==========] Running 17 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 9 tests from TEST_BST_FUNCTIONS
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeInsert
[       OK ] TEST_BST_FUNCTIONS.TestTreeInsert (0 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeSearch
[       OK ] TEST_BST_FUNCTIONS.TestTreeSearch (0 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreePrint
Print Null Tree:
Debug Print Null Tree:
Print One Node Tree:
[5]
Debug Print One Node Tree:
[5:0 (0)]
Print Full Tree:
                       [10]
                   [9]
               [8]
           [7]
       [6]
   [5]
[5]
                   [4]
               [3]
           [2]
       [1]
   [0]
Debug Print Full Tree:
                                                           [10:0 (0)]
                                                 [9:1 (-1)]
                                       [8:2 (-2)]
                             [7:3 (-3)]
                   [6:4 (-4)]
         [5:5 (-5)]
[5:6 (-1)]
                                                 [4:0 (0)]
                                       [3:1 (-1)]
                             [2:2 (-2)]
                   [1:3 (-3)]
         [0:4 (-4)]
[       OK ] TEST_BST_FUNCTIONS.TestTreePrint (33 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeClear
[       OK ] TEST_BST_FUNCTIONS.TestTreeClear (0 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeErase
Before erasing from null tree.
ERASING 101
Erased from null tree.
Before erasing nexist from one node tree.
[5:0 (0)]
ERASING 101
ERASING 101
Erased nexist from one node tree.
[5:0 (0)]
Before erasing exist from one node tree.
[5:0 (0)]
ERASING 5
Erased exist from one node tree.
Before erasing nexist from full tree.
                                                                                                   [10:0 (0)]
                                                                                         [9:1 (-1)]
                                                                               [8:2 (-2)]
                                                                     [7:3 (-3)]
                                                           [6:4 (-4)]
                                                 [5:5 (-5)]
                                       [4:6 (-6)]
                             [3:7 (-7)]
                   [2:8 (-8)]
         [1:9 (-9)]
[0:10 (-10)]
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
ERASING 101
Erased nexist from full tree.
                                                                                                   [10:0 (0)]
                                                                                         [9:1 (-1)]
                                                                               [8:2 (-2)]
                                                                     [7:3 (-3)]
                                                           [6:4 (-4)]
                                                 [5:5 (-5)]
                                       [4:6 (-6)]
                             [3:7 (-7)]
                   [2:8 (-8)]
         [1:9 (-9)]
[0:10 (-10)]
ERASING 0
Erased 0
                                                                                         [10:0 (0)]
                                                                               [9:1 (-1)]
                                                                     [8:2 (-2)]
                                                           [7:3 (-3)]
                                                 [6:4 (-4)]
                                       [5:5 (-5)]
                             [4:6 (-6)]
                   [3:7 (-7)]
         [2:8 (-8)]
[1:9 (-9)]
ERASING 1
Erased 1
                                                                               [10:0 (0)]
                                                                     [9:1 (-1)]
                                                           [8:2 (-2)]
                                                 [7:3 (-3)]
                                       [6:4 (-4)]
                             [5:5 (-5)]
                   [4:6 (-6)]
         [3:7 (-7)]
[2:8 (-8)]
ERASING 2
Erased 2
                                                                     [10:0 (0)]
                                                           [9:1 (-1)]
                                                 [8:2 (-2)]
                                       [7:3 (-3)]
                             [6:4 (-4)]
                   [5:5 (-5)]
         [4:6 (-6)]
[3:7 (-7)]
ERASING 3
Erased 3
                                                           [10:0 (0)]
                                                 [9:1 (-1)]
                                       [8:2 (-2)]
                             [7:3 (-3)]
                   [6:4 (-4)]
         [5:5 (-5)]
[4:6 (-6)]
ERASING 4
Erased 4
                                                 [10:0 (0)]
                                       [9:1 (-1)]
                             [8:2 (-2)]
                   [7:3 (-3)]
         [6:4 (-4)]
[5:5 (-5)]
ERASING 5
Erased 5
                                       [10:0 (0)]
                             [9:1 (-1)]
                   [8:2 (-2)]
         [7:3 (-3)]
[6:4 (-4)]
ERASING 6
Erased 6
                             [10:0 (0)]
                   [9:1 (-1)]
         [8:2 (-2)]
[7:3 (-3)]
ERASING 7
Erased 7
                   [10:0 (0)]
         [9:1 (-1)]
[8:2 (-2)]
ERASING 8
Erased 8
         [10:0 (0)]
[9:1 (-1)]
ERASING 9
Erased 9
[10:0 (0)]
ERASING 10
Erased 10
Node with both subtrees:
                   [205:0 (0)]
         [200:1 (0)]
                   [195:0 (0)]
[100:2 (0)]
                   [5:0 (0)]
         [0:1 (0)]
                   [-5:0 (0)]
Erasing nexists...
ERASING 101
ERASING 101
ERASING 101
ERASING 101
Erasing center...
ERASING 100
ROOT HAS A LEFT SUBTREE
TREE REMOVE MAX HAS BEEN CALLED
THERE IS A RIGHT SUBTREE
TREE REMOVE MAX HAS BEEN CALLED
THERE IS NO RIGHT SUBTREE
THERE IS NO LEFT SUBTREE
REMOVED MAX
Erased center node from node with both subtrees:
                   [205:0 (0)]
         [200:1 (0)]
                   [195:0 (0)]
[5:2 (0)]
         [0:1 (1)]
                   [-5:0 (0)]
Node with left subtree:
[100:2 (2)]
                   [5:0 (0)]
         [0:1 (0)]
                   [-5:0 (0)]
Erasing nexists...
ERASING 101
ERASING 101
Erasing center...
ERASING 100
ROOT HAS A LEFT SUBTREE
TREE REMOVE MAX HAS BEEN CALLED
THERE IS A RIGHT SUBTREE
TREE REMOVE MAX HAS BEEN CALLED
THERE IS NO RIGHT SUBTREE
THERE IS NO LEFT SUBTREE
REMOVED MAX
Erased center node from node with left subtree only:
[5:2 (2)]
         [0:1 (1)]
                   [-5:0 (0)]
Node with right subtree:
                   [205:0 (0)]
         [200:1 (0)]
                   [195:0 (0)]
[100:2 (-2)]
Erasing nexists...
ERASING 101
ERASING 101
ERASING 101
ERASING 101
Erasing center...
ERASING 100
Erased center node from node with right subtree only:
         [205:0 (0)]
[200:1 (0)]
         [195:0 (0)]
Node with no subtrees:
[100:0 (0)]
Erasing nexists...
ERASING 101
ERASING 101
Erasing center...
ERASING 100
Erased center node from node without subtrees only:
Node with right subtree:
[97:5 (5)]
                   [95:3 (3)]
                                       [81:1 (1)]
                                                 [60:0 (0)]
                             [46:2 (-2)]
         [44:4 (-3)]
                   [40:0 (0)]
ERASING 95
ERASING 95
ERASING 95
ROOT HAS A LEFT SUBTREE
TREE REMOVE MAX HAS BEEN CALLED
THERE IS A RIGHT SUBTREE
TREE REMOVE MAX HAS BEEN CALLED
THERE IS NO RIGHT SUBTREE
THERE IS A LEFT SUBTREE
60
REMOVED MAX
[97:5 (5)]
                   [81:3 (3)]
                                       [60:0 (0)]
                             [46:2 (-1)]
         [44:4 (-3)]
                   [40:0 (0)]
[       OK ] TEST_BST_FUNCTIONS.TestTreeErase (540 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeFromSortedList
[       OK ] TEST_BST_FUNCTIONS.TestTreeFromSortedList (0 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeTraversals
IN ORDER:
[0]
0
PRE ORDER:
[0]
0
POST ORDER:
[0]
0

IN ORDER:
[0][1]
0 1
PRE ORDER:
[1][0]
1 0
POST ORDER:
[0][1]
0 1

IN ORDER:
[0][1][2]
0 1 2
PRE ORDER:
[1][0][2]
1 0 2
POST ORDER:
[0][2][1]
0 2 1

IN ORDER:
[0][1][2][3]
0 1 2 3
PRE ORDER:
[2][1][0][3]
2 1 0 3
POST ORDER:
[0][1][3][2]
0 1 3 2

IN ORDER:
[0][1][2][3][4]
0 1 2 3 4
PRE ORDER:
[2][1][0][4][3]
2 1 0 4 3
POST ORDER:
[0][1][3][4][2]
0 1 3 4 2

IN ORDER:
[0][1][2][3][4][5]
0 1 2 3 4 5
PRE ORDER:
[3][1][0][2][5][4]
3 1 0 2 5 4
POST ORDER:
[0][2][1][4][5][3]
0 2 1 4 5 3

IN ORDER:
[0][1][2][3][4][5][6]
0 1 2 3 4 5 6
PRE ORDER:
[3][1][0][2][5][4][6]
3 1 0 2 5 4 6
POST ORDER:
[0][2][1][4][6][5][3]
0 2 1 4 6 5 3

IN ORDER:
[0][1][2][3][4][5][6][7]
0 1 2 3 4 5 6 7
PRE ORDER:
[4][2][1][0][3][6][5][7]
4 2 1 0 3 6 5 7
POST ORDER:
[0][1][3][2][5][7][6][4]
0 1 3 2 5 7 6 4

IN ORDER:
[0][1][2][3][4][5][6][7][8]
0 1 2 3 4 5 6 7 8
PRE ORDER:
[4][2][1][0][3][7][6][5][8]
4 2 1 0 3 7 6 5 8
POST ORDER:
[0][1][3][2][5][6][8][7][4]
0 1 3 2 5 6 8 7 4

[       OK ] TEST_BST_FUNCTIONS.TestTreeTraversals (95 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeCopy
[       OK ] TEST_BST_FUNCTIONS.TestTreeCopy (0 ms)
[ RUN      ] TEST_BST_FUNCTIONS.TestTreeAdd
[       OK ] TEST_BST_FUNCTIONS.TestTreeAdd (0 ms)
[----------] 9 tests from TEST_BST_FUNCTIONS (688 ms total)

[----------] 8 tests from TEST_BST
[ RUN      ] TEST_BST.TestBigThree
[       OK ] TEST_BST.TestBigThree (0 ms)
[ RUN      ] TEST_BST.TestInsert
[       OK ] TEST_BST.TestInsert (0 ms)
[ RUN      ] TEST_BST.TestSearchContains
[       OK ] TEST_BST.TestSearchContains (0 ms)
[ RUN      ] TEST_BST.TestErase
ERASING 0
ERASING 0
ERASING 0
ERASING 0
ERASING 1
ERASING 1
ERASING 1
ERASING 2
ERASING 2
ERASING 3
ERASING 3
ERASING 3
ERASING 4
ERASING 4
ERASING 5
ERASING 6
ERASING 6
ERASING 6
ERASING 7
ERASING 7
ERASING 8
ERASING 9
ROOT HAS A LEFT SUBTREE
TREE REMOVE MAX HAS BEEN CALLED
THERE IS NO RIGHT SUBTREE
THERE IS NO LEFT SUBTREE
REMOVED MAX
[       OK ] TEST_BST.TestErase (27 ms)
[ RUN      ] TEST_BST.TestClearAll
[       OK ] TEST_BST.TestClearAll (0 ms)
[ RUN      ] TEST_BST.TestEmpty
[       OK ] TEST_BST.TestEmpty (0 ms)
[ RUN      ] TEST_BST.TestAddEqual
[       OK ] TEST_BST.TestAddEqual (0 ms)
[ RUN      ] TEST_BST.TestTraversals
[       OK ] TEST_BST.TestTraversals (0 ms)
[----------] 8 tests from TEST_BST (37 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 2 test suites ran. (728 ms total)
[  PASSED  ] 17 tests.
```

## BST Driver Program:
```cpp
int main()
{
  int num = 3;

  cout << "---------------------CREATING BST 1---------------------\n";
  BST<int> bst;
  for (int i = 0; i < num; i++)
    bst.insert(i);
  cout << "BST 1:\n" << bst;
  _memory.print_allocated();

  cout << "---------------------CREATING BST 2---------------------\n";
  BST<int> bst2;
  bst2 = bst;
  cout << "Copying BST 1 into BST 2...\n";
  cout << "BST 2:\n" << bst2;
  _memory.print_allocated();

  cout << "---------------------CLEARING BST 1---------------------\n";
  bst.clear_all();
  cout << "Cleared BST 1:\n";
  cout << "BST 1:\n" << bst;
  cout << "BST 2:\n" << bst2;
  cout << "BST is empty? " << bst.empty() << endl;
  cout << "BST2 is empty? " << bst2.empty() << endl;
  _memory.print_allocated();

  Ptr<tree_node<int> > found_ptr;
  for (int i = 0; i < num; i++)
  {
    cout << i << " in BST: " << bst.search(i, found_ptr) << endl;
    cout << i << " in BST: " << bst.contains(i) << endl; 
    cout << i << " in BST2: " << bst2.search(i, found_ptr) << endl; 
    cout << i << " in BST2: " << bst2.contains(i) << endl; 
  }

  cout << "---------------------ERASING BST 2---------------------\n";
  for (int i = 0; i < num; i++)
  {
    bst2.erase(i);
    cout << "BST 2 now...\n" << bst2 << endl;
  }
  cout << "BST 1:\n" << bst;
  cout << "BST 2:\n" << bst2;
  _memory.print_allocated();

  cout << "---------------------FILLING BSTs AGAIN---------------------\n";
  for (int i = 0; i < num; i++)
    bst.insert(i);
  for (int i = 2 * num - 1; i >= num; i--)
    bst2.insert(i);
  cout << "BST 1:\n" << bst;
  cout << "BST 2:\n" << bst2;
  _memory.print_allocated();

  cout << "---------------------ADDING BST 2 to BST 1---------------------\n";
  bst += bst2;
  cout << "BST 1:\n" << bst;
  cout << "BST 2:\n" << bst2;
  _memory.print_allocated();

  cout << "---------------------CONCLUSION---------------------\n";
  cout << "BST 1: " << endl;
  cout << "Pre Order String: " << bst.pre_order() << endl;
  cout << "In Order String: " << bst.in_order() << endl;
  cout << "Post Order String: " << bst.post_order() << endl;
  cout << "BST 2: " << endl;
  cout << "Pre Order String: " << bst2.pre_order() << endl;
  cout << "In Order String: " << bst2.in_order() << endl;
  cout << "Post Order String: " << bst2.post_order() << endl;
  
  return 0;
}
```

## BST Output:
```
---------------------CREATING BST 1---------------------
BST 1:
       [2]
   [1]
[0]
Address         Memory          Allocated
0:                              1
1:                              1
2:                              1
3:                              1
4:                              1
5:                              1
6:                              1
7:                              1
8:                              1
9:                              1
10:                             1
11:                             1
12:             ↑               1
13:                             1
14:                             1
15:                             1
16:             ☺               1
17:                             1
18:                             1
19:                             1
20:             ☻               1
21:                             1
22:                             1
23:                             1
24:             ☺               1
25:                             1
26:                             1
27:                             1
28:                             1
29:                             1
30:                             1
31:                             1
32:                             1
33:                             1
34:                             1
35:                             1
36:             0               1
37:                             1
38:                             1
39:                             1
40:             ☺               1
41:                             1
42:                             1
43:                             1
44:             ☺               1
45:                             1
46:                             1
47:                             1
48:             ☻               1
49:                             1
50:                             1
51:                             1
52:                             1
53:                             1
54:                             1
55:                             1
56:                             1
57:                             1
58:                             1
59:                             1
60:                             1
61:                             1
62:                             1
63:                             1
64:                             1
65:                             1
66:                             1
67:                             1
68:                             1
69:                             1
70:                             1
71:                             1

Next Free Index: 72

---------------------CREATING BST 2---------------------
Copying BST 1 into BST 2...
BST 2:
       [2]
   [1]
[0]
Address         Memory          Allocated
0:                              1
1:                              1
2:                              1
3:                              1
4:                              1
5:                              1
6:                              1
7:                              1
8:                              1
9:                              1
10:                             1
11:                             1
12:             ↑               1
13:                             1
14:                             1
15:                             1
16:             ☺               1
17:                             1
18:                             1
19:                             1
20:             ☻               1
21:                             1
22:                             1
23:                             1
24:             ☺               1
25:                             1
26:                             1
27:                             1
28:                             1
29:                             1
30:                             1
31:                             1
32:                             1
33:                             1
34:                             1
35:                             1
36:             0               1
37:                             1
38:                             1
39:                             1
40:             ☺               1
41:                             1
42:                             1
43:                             1
44:             ☺               1
45:                             1
46:                             1
47:                             1
48:             ☻               1
49:                             1
50:                             1
51:                             1
52:                             1
53:                             1
54:                             1
55:                             1
56:                             1
57:                             1
58:                             1
59:                             1
60:                             1
61:                             1
62:                             1
63:                             1
64:                             1
65:                             1
66:                             1
67:                             1
68:                             1
69:                             1
70:                             1
71:                             1
72:                             1
73:                             1
74:                             1
75:                             1
76:                             1
77:                             1
78:                             1
79:                             1
80:                             1
81:                             1
82:                             1
83:                             1
84:             `               1
85:                             1
86:                             1
87:                             1
88:             ☺               1
89:                             1
90:                             1
91:                             1
92:             ☻               1
93:                             1
94:                             1
95:                             1
96:             ☺               1
97:                             1
98:                             1
99:                             1
100:                            1
101:                            1
102:                            1
103:                            1
104:                            1
105:                            1
106:                            1
107:                            1
108:            x               1
109:                            1
110:                            1
111:                            1
112:            ☺               1
113:                            1
114:                            1
115:                            1
116:            ☺               1
117:                            1
118:                            1
119:                            1
120:            ☻               1
121:                            1
122:                            1
123:                            1
124:                            1
125:                            1
126:                            1
127:                            1
128:                            1
129:                            1
130:                            1
131:                            1
132:                            1
133:                            1
134:                            1
135:                            1
136:                            1
137:                            1
138:                            1
139:                            1
140:                            1
141:                            1
142:                            1
143:                            1

Next Free Index: 144

---------------------CLEARING BST 1---------------------
Cleared BST 1:
BST 1:
BST 2:
       [2]
   [1]
[0]
BST is empty? 1
BST2 is empty? 0
Address         Memory          Allocated
72:                             1
73:                             1
74:                             1
75:                             1
76:                             1
77:                             1
78:                             1
79:                             1
80:                             1
81:                             1
82:                             1
83:                             1
84:             `               1
85:                             1
86:                             1
87:                             1
88:             ☺               1
89:                             1
90:                             1
91:                             1
92:             ☻               1
93:                             1
94:                             1
95:                             1
96:             ☺               1
97:                             1
98:                             1
99:                             1
100:                            1
101:                            1
102:                            1
103:                            1
104:                            1
105:                            1
106:                            1
107:                            1
108:            x               1
109:                            1
110:                            1
111:                            1
112:            ☺               1
113:                            1
114:                            1
115:                            1
116:            ☺               1
117:                            1
118:                            1
119:                            1
120:            ☻               1
121:                            1
122:                            1
123:                            1
124:                            1
125:                            1
126:                            1
127:                            1
128:                            1
129:                            1
130:                            1
131:                            1
132:                            1
133:                            1
134:                            1
135:                            1
136:                            1
137:                            1
138:                            1
139:                            1
140:                            1
141:                            1
142:                            1
143:                            1

Next Free Index: 144

0 in BST: 0
0 in BST: 0
0 in BST2: 1
0 in BST2: 1
1 in BST: 0
1 in BST: 0
1 in BST2: 1
1 in BST2: 1
2 in BST: 0
2 in BST: 0
2 in BST2: 1
2 in BST2: 1
---------------------ERASING BST 2---------------------
ERASING 0
BST 2 now...
   [2]
[1]

ERASING 1
BST 2 now...
[2]

ERASING 2
BST 2 now...

BST 1:
BST 2:
Address         Memory          Allocated

Next Free Index: 144

---------------------FILLING BSTs AGAIN---------------------
BST 1:
       [2]
   [1]
[0]
BST 2:
[5]
   [4]
       [3]
Address         Memory          Allocated
144:                            1
145:                            1
146:                            1
147:                            1
148:                            1
149:                            1
150:                            1
151:                            1
152:                            1
153:                            1
154:                            1
155:                            1
156:            ¿               1
157:                            1
158:                            1
159:                            1
160:            ☺               1
161:                            1
162:                            1
163:                            1
164:            ☻               1
165:                            1
166:                            1
167:                            1
168:            ☺               1
169:                            1
170:                            1
171:                            1
172:                            1
173:                            1
174:                            1
175:                            1
176:                            1
177:                            1
178:                            1
179:                            1
180:            └               1
181:                            1
182:                            1
183:                            1
184:            ☺               1
185:                            1
186:                            1
187:                            1
188:            ☺               1
189:                            1
190:                            1
191:                            1
192:            ☻               1
193:                            1
194:                            1
195:                            1
196:                            1
197:                            1
198:                            1
199:                            1
200:                            1
201:                            1
202:                            1
203:                            1
204:                            1
205:                            1
206:                            1
207:                            1
208:                            1
209:                            1
210:                            1
211:                            1
212:                            1
213:                            1
214:                            1
215:                            1
216:            ♣               1
217:                            1
218:                            1
219:                            1
220:            ≡               1
221:                            1
222:                            1
223:                            1
224:            ☺               1
225:                            1
226:                            1
227:                            1
228:                            1
229:                            1
230:                            1
231:                            1
232:                            1
233:                            1
234:                            1
235:                            1
236:            ☻               1
237:                            1
238:                            1
239:                            1
240:            ♦               1
241:                            1
242:                            1
243:                            1
244:                    1
245:            ☺               1
246:                            1
247:                            1
248:            ☺               1
249:                            1
250:                            1
251:                            1
252:                            1
253:                            1
254:                            1
255:                            1
256:                            1
257:                            1
258:                            1
259:                            1
260:            ☺               1
261:                            1
262:                            1
263:                            1
264:            ♥               1
265:                            1
266:                            1
267:                            1
268:                            1
269:                            1
270:                            1
271:                            1
272:                            1
273:                            1
274:                            1
275:                            1
276:                            1
277:                            1
278:                            1
279:                            1
280:                            1
281:                            1
282:                            1
283:                            1
284:                            1
285:                            1
286:                            1
287:                            1

Next Free Index: 288

---------------------ADDING BST 2 to BST 1---------------------
BST 1:
           [5]
               [4]
                   [3]
       [2]
   [1]
[0]
BST 2:
[5]
   [4]
       [3]
Address         Memory          Allocated
144:                            1
145:                            1
146:                            1
147:                            1
148:                            1
149:                            1
150:                            1
151:                            1
152:                            1
153:                            1
154:                            1
155:                            1
156:            ¿               1
157:                            1
158:                            1
159:                            1
160:            ☺               1
161:                            1
162:                            1
163:                            1
164:            ♣               1
165:                            1
166:                            1
167:                            1
168:            ☺               1
169:                            1
170:                            1
171:                            1
172:                            1
173:                            1
174:                            1
175:                            1
176:                            1
177:                            1
178:                            1
179:                            1
180:            └               1
181:                            1
182:                            1
183:                            1
184:            ☺               1
185:                            1
186:                            1
187:                            1
188:            ♦               1
189:                            1
190:                            1
191:                            1
192:            ☻               1
193:                            1
194:                            1
195:                            1
196:                            1
197:                            1
198:                            1
199:                            1
200:                            1
201:                            1
202:                            1
203:                            1
204:                            1
205:            ☺               1
206:                            1
207:                            1
208:            ☺               1
209:                            1
210:                            1
211:                            1
212:            ♥               1
213:                            1
214:                            1
215:                            1
216:            ♣               1
217:                            1
218:                            1
219:                            1
220:            ≡               1
221:                            1
222:                            1
223:                            1
224:            ☺               1
225:                            1
226:                            1
227:                            1
228:                            1
229:                            1
230:                            1
231:                            1
232:                            1
233:                            1
234:                            1
235:                            1
236:            ☻               1
237:                            1
238:                            1
239:                            1
240:            ♦               1
241:                            1
242:                            1
243:                            1
244:                    1
245:            ☺               1
246:                            1
247:                            1
248:            ☺               1
249:                            1
250:                            1
251:                            1
252:                            1
253:                            1
254:                            1
255:                            1
256:                            1
257:                            1
258:                            1
259:                            1
260:            ☺               1
261:                            1
262:                            1
263:                            1
264:            ♥               1
265:                            1
266:                            1
267:                            1
268:                            1
269:                            1
270:                            1
271:                            1
272:                            1
273:                            1
274:                            1
275:                            1
276:                            1
277:                            1
278:                            1
279:                            1
280:                            1
281:                            1
282:                            1
283:                            1
284:                            1
285:                            1
286:                            1
287:                            1
288:            ♣               1
289:                            1
290:                            1
291:                            1
292:            8               1
293:            ☺               1
294:                            1
295:                            1
296:            ☺               1
297:                            1
298:                            1
299:                            1
300:                            1
301:                            1
302:                            1
303:                            1
304:                            1
305:                            1
306:                            1
307:                            1
308:            ☻               1
309:                            1
310:                            1
311:                            1
312:            ♦               1
313:                            1
314:                            1
315:                            1
316:            P               1
317:            ☺               1
318:                            1
319:                            1
320:            ☺               1
321:                            1
322:                            1
323:                            1
324:                            1
325:                            1
326:                            1
327:                            1
328:                            1
329:                            1
330:                            1
331:                            1
332:            ☺               1
333:                            1
334:                            1
335:                            1
336:            ♥               1
337:                            1
338:                            1
339:                            1
340:                            1
341:                            1
342:                            1
343:                            1
344:                            1
345:                            1
346:                            1
347:                            1
348:                            1
349:                            1
350:                            1
351:                            1
352:                            1
353:                            1
354:                            1
355:                            1
356:                            1
357:                            1
358:                            1
359:                            1

Next Free Index: 504

---------------------CONCLUSION---------------------
BST 1:
Pre Order String: [0][1][2][5][4][3]
In Order String: [0][1][2][3][4][5]
Post Order String: [3][4][5][2][1][0]
BST 2:
Pre Order String: [5][4][3]
In Order String: [3][4][5]
Post Order String: [3][4][5]
```

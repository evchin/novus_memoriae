#include "includes/bst/BST.h"

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
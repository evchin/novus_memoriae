/*
 * Author: Evelyn Chin
 * Project: BST
 * Project Purpose: Create a binary search tree of nodes. 
 * File Purpose: Implement the core bst functions that will support
 *               the main BST class, as well as the tree_node struct.
 */

#ifndef BST_FUNCTIONS_H
#define BST_FUNCTIONS_H

#include "../ptr/Ptr.h"
#include <iomanip>
#include <cassert>
#include <string>
using namespace std;

template <typename T>
struct tree_node
{
    T _item;
    Ptr<tree_node<T> > _left;
    Ptr<tree_node<T> > _right;
    int _height;

    // PURPOSE: tree node constructor
    tree_node(T item = T(), Ptr<tree_node<T> > left = Ptr<tree_node<T> >(),
            Ptr<tree_node<T> > right = Ptr<tree_node<T> >()):
            _item(item), _left(left), _right(right)
    {
        update_height();
    }

    // PURPOSE: get balance factor (right - left)
    int balance_factor()
    {
        int left, right;
        // get left height: if null, -1. else just _left->_height
        if (!_left) left = -1;
        else left = _left->_height;
        // get right height: if null, -1. else just _right->_height
        if (!_right) right = -1;
        else right = _right->_height;
        // return balance factor
        return left - right;
    }

    // PURPOSE: get height of node
    int height()
    {
        int left, right;
        // set left height: if null, -1. else recursive call on _left.
        if (!_left) left = -1;
        else left = _left->_height;
        // set right height: if null, -1. else recursive call on _right.
        if (!_right) right = -1;
        else right = _right->_height;
        // return 1 + max(left, right)
        return 1 + max(left, right);
    }

    // PURPOSE: Update _height 
    int update_height()
    {
        _height = height();
        return _height;
    }
    
    // PURPOSE: Print the tree node
    friend ostream& operator << (ostream& outs, const tree_node<T>& t_node)
    {
        outs << "|" << t_node._item << "|";
        return outs;
    }
};

template <typename T>
string to_string(const tree_node<T>& node){
    string s = "|" + to_string(node._item) + "|";
    return s;
}

// PURPOSE: insert a new node 'insert_me' into the tree 
template <typename T>
void tree_insert(Ptr<tree_node<T> > &root, const T& insert_me)
{
    // if root is null, set it equal to 'insert_me'
    if (!root)
    {
        root._new();
        tree_node<T> insert(insert_me);
        *root = insert;
    }
    // else if insert_me < root, recursive call to the left
    else if (insert_me < root->_item) tree_insert(root->_left, insert_me);
    // else if insert_me > root, recursive call to the right
    else tree_insert(root->_right, insert_me);
    // update _height
    root->update_height();
}

// PURPOSE: search the tree for a node with 'target'
template <typename T>
Ptr<tree_node<T> > tree_search(Ptr<tree_node<T> > root, const T& target)
{
    const bool debug = false;
    if (!root)
    {
        if (debug) cout << "tree_search: Not found. Root is NULL.\n";
        return root;
    }
    // if root == target
    if (root->_item == target)
    {
        if (debug) cout << "tree_search: Found target [" << root->_item << "]\n";
        return root;
    }
    // if target < root
    if (target < root->_item)
    {
        if (debug) cout << "tree_search: going left\n";
        return tree_search(root->_left, target);
    }
    // if target > root
    if (target > root->_item)
    {
        if (debug) cout << "tree_search: going right\n";
        return tree_search(root->_right, target);
    }
    assert(false && "Reached end of tree_search(root, target) function.");
    return root;
}

// PURPOSE: search the tree for a node with 'target'. return true if found
template <typename T>
bool tree_search(Ptr<tree_node<T> > root, const T& target, Ptr<tree_node<T> > &found_ptr)
{
    found_ptr = tree_search(root, target);
    if (!found_ptr) return false;
    return true;
}

// PURPOSE: print the tree
template<typename T>
void tree_print(Ptr<tree_node<T> > root, int depth=0, ostream& outs=cout)
{
    if (!root.null())
    {
        tree_print(root->_right, depth + 1);
        outs << setw(4 * depth) << "[" << root->_item << "]" << endl;
        tree_print(root->_left, depth + 1);
    }
}

// PURPOSE: print detailed info about each node
template<typename T> 
void tree_print_debug(Ptr<tree_node<T> > root, int depth=0, ostream& outs=cout)
{
    if (!root.null())
    {
        tree_print_debug(root->_right, depth + 1);
        outs << setw(10 * depth) << "[" << root->_item << ":" << root->_height;
        outs << " (" << root->balance_factor() << ")]" << endl;
        tree_print_debug(root->_left, depth + 1);
    }
}

// PURPOSE: clears the tree
template <typename T>
void tree_clear(Ptr<tree_node<T> > &root)
{
    if (!root.null())
    {
        tree_clear(root->_left);
        tree_clear(root->_right);
        root._delete();
    }
}

// PURPOSE: erase target from tree. if successfully erased, return true.
template <typename T>
bool tree_erase(Ptr<tree_node<T> >& root, const T& target)
{
    cout << "ERASING " << target << endl;
    bool erased;
    // if root is null
    if (!root) return false;
    // if target > root
    else if (target > root->_item) erased = tree_erase(root->_right, target);
    // if target < root
    else if (target < root->_item) erased = tree_erase(root->_left, target);
    // if root == target
    else if (root->_item == target)
    {
        // if no subtrees exist
        if (!(root->_left) && !(root->_right))
        {
            root._delete();
            root.set_null();
            return true;
        }
        // if root has no left subtree and a right subtree, connect right subtree
        else if (!(root->_left) && !root->_right.null())
        {
            root->_item = root->_right->_item;
            Ptr<tree_node<T> > temp = root->_right;
            root->_left = temp->_left;
            root->_right = temp->_right;
            root->update_height();
            temp._delete();
        }
        // else if root has a left subtree
        else
        {
            cout << "ROOT HAS A LEFT SUBTREE" << endl;
            T max_value;
            tree_remove_max(root->_left, max_value);
            cout << "REMOVED MAX" << endl;
            root->_item = max_value;
        }
        erased = true;
    }

    root->update_height();
    return erased;
}

// PURPOSE: erase rightmost node from the tree and store it in max_value
template <typename T>
void tree_remove_max(Ptr<tree_node<T> > &root, T& max_value)
{
    cout << "TREE REMOVE MAX HAS BEEN CALLED" << endl;
    // if there is no right subtree
    if (!(root->_right))
    {
        cout << "THERE IS NO RIGHT SUBTREE" << endl;
        max_value = root->_item;
        // if there is a left subtree, copy into root
        if (!root->_left.null())
        {
            cout << "THERE IS A LEFT SUBTREE" << endl;
            cout << root->_left->_item << endl;
            root->_item = root->_left->_item;
            Ptr<tree_node<T> > temp = root->_left;
            root->_left = temp->_left;
            root->_right = temp->_right;
            root->update_height();
            temp._delete();
        }

        // if there is not a left subtree
        else
        {
            cout << "THERE IS NO LEFT SUBTREE" << endl;
            root._delete();
            root.set_null();
        }
    }
    // if there is a right subtree, recursive call
    else 
    {
        cout << "THERE IS A RIGHT SUBTREE" << endl;
        tree_remove_max(root->_right, max_value);
    }
}

// PURPOSE: prints tree in order (left, root, right) 
template <typename T>
void in_order(Ptr<tree_node<T> > root, ostream& outs=cout)
{
    if (!root) return;
    in_order(root->_left, outs);
    outs << root->_item << " ";
    in_order(root->_right, outs);
}

// PURPOSE: prints tree in pre order (root, left, right) 
template <typename T>
void pre_order(Ptr<tree_node<T> > root,ostream& outs=cout)
{
    if (!root) return;
    outs << root->_item << " ";
    pre_order(root->_left, outs);
    pre_order(root->_right, outs);
}

// PURPOSE: prints tree in post order (left, right, root)
template <typename T>
void post_order(Ptr<tree_node<T> > root,ostream& outs=cout)
{
    if (!root) return;
    post_order(root->_left, outs);
    post_order(root->_right, outs);
    outs << root->_item << " ";
}

// PURPOSE: gets tree string in order (left, root, right) 
template <typename T> 
string in_order_string(Ptr<tree_node<T> > root)
{
    if (!root) return "";
    return in_order_string(root->_left)
            + "[" + to_string(root->_item) + "]" 
            + in_order_string(root->_right);
}

// PURPOSE: gets tree string in pre order (root, left, right) 
template <typename T>
string pre_order_string(Ptr<tree_node<T> > root)
{
    if (!root) return "";
    return "[" + to_string(root->_item) + "]" 
            + pre_order_string(root->_left) 
            + pre_order_string(root->_right);
}

// PURPOSE: gets tree string in post order (left, right, root)
template <typename T>
string post_order_string(Ptr<tree_node<T> > root)
{
    if (!root) return "";
    return post_order_string(root->_left) 
            + post_order_string(root->_right)
            + "[" + to_string(root->_item) + "]" ;
}

// PURPOSE: returns a copy of tree pointed to by root
template <typename T>
Ptr<tree_node<T> > tree_copy(Ptr<tree_node<T> > root)
{
    Ptr<tree_node<T> > ptr;
    if (!root) return ptr;
    ptr._new();
    *ptr = tree_node<T>(root->_item, tree_copy(root->_left), tree_copy(root->_right));
    return ptr;
}

// PURPOSE: Add tree src to dest
template <typename T>
void tree_add(Ptr<tree_node<T> > & dest, const Ptr<tree_node<T> > src)
{
    if (!src) return;
    tree_insert(dest, src->_item);
    tree_add(dest, src->_left);
    tree_add(dest, src->_right);
}

// PURPOSE: return new tree created from a sorted array
template <typename T>
Ptr<tree_node<T> > tree_from_sorted_list(const T* a, int size)
{
    if (size == 0) return Ptr<tree_node<T> >();
    int half = size/2;
    int right_size;
    if (size % 2 == 0) right_size = half - 1;
    else right_size = half;

    Ptr<tree_node<T> > ptr;
    ptr._new();
    tree_node<T> tree(a[half], tree_from_sorted_list(a, half), 
                    tree_from_sorted_list(a + half + 1, right_size));
    *ptr = tree;
    return ptr;
}

// PURPOSE: return new tree created from a sorted array
template <typename T>
Ptr<tree_node<T> > tree_from_sorted_list(const T* a)
{
    int size = 0;
    int index = 0;
    while (a[index++] >= 0) size++;
    return tree_from_sorted_list(a, size);
}

#endif // BST_FUNCTIONS_H
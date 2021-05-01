/*
 * Author: Evelyn Chin
 * Project: BST
 * Project Purpose: Create a binary search tree of nodes. 
 * File Purpose: Implement the BST class using the BST functions and
 *               tree_node struct. 
 */

#ifndef BST_H
#define BST_H

#include "../bst_functions/bst_functions.h"

template <typename T>
class BST
{
public:
    // PURPOSE: constructor
    BST(){}
    
    // PURPOSE: constructor from sorted list
    BST(const T *sorted_list, int size = -1)
    {
        if (size == -1) _root = tree_from_sorted_list(sorted_list);
        else _root = tree_from_sorted_list(sorted_list, size);
    }

    // PURPOSE: copy constructor
    BST(const BST<T> &copy_me)
    {
        _root = tree_copy(copy_me._root);
    }

    // PURPOSE: equal operator override
    BST<T>& operator=(const BST<T> &rhs)
    {
        tree_clear(_root);
        _root = tree_copy(rhs._root);
        return *this;
    }

    // PURPOSE: deconstructor
    ~BST()
    {
        tree_clear(_root);
    }

    // PURPOSE: insert a new node 'insert_me' into the tree
    void insert(const T &insert_me)
    {
        tree_insert(_root, insert_me);
    }
    
    // PURPOSE: search for 'target', set to 'found_ptr'. return true is found.
    bool search(const T& target, Ptr<tree_node<T> > &found_ptr)
    {
        found_ptr = tree_search(_root, target);
        if (!found_ptr) return false;
        return true;
    }
    
    // PURPOSE: erase target from tree
    void erase(const T &target)
    {
        tree_erase(_root, target);
    }
    
    // PURPOSE: return true if tree contains target
    bool contains(const T &target) const
    {
        Ptr<tree_node<T> > ptr;
        return tree_search(_root, target, ptr);
    }

    // PURPOSE: clear the tree
    void clear_all()
    {
        tree_clear(_root);
    }

    // PURPOSE: return true if tree is empty
    bool empty() const
    {
        return !_root;
    }

    // PURPOSE: print tree
    friend ostream &operator<<(ostream &outs, const BST<T> &tree)
    {
        const bool debug = false;
        if (debug)
        {
            cout<<"-------------------------------"<<endl;
            tree_print_debug(tree._root, 0, outs);
            cout<<". . . . . . . . . . . . . . . ."<<endl;
        }
        tree_print(tree._root, 0, outs);
        return outs;
    }

    // PURPOSE: add rhs to this tree
    BST<T> operator+=(const BST<T> &rhs)
    {
        tree_add(_root, rhs._root);
        return *this;
    }
    
    // PURPOSE: return pre order string
    string pre_order()
    {
        return pre_order_string(_root);
    }

    // PURPOSE: return in order string
    string in_order()
    {
        return in_order_string(_root);
    }

    // PURPOSE: return post order string
    string post_order()
    {
        return post_order_string(_root);
    }

private:
    Ptr<tree_node<T> > _root;
};

#endif // BST_H
/*
 * Author: Evelyn Chin
 * Project: BST
 * Project Purpose: Create a binary search tree of nodes. 
 * File Purpose: Test the BST functions and BST class. 
 */

#include "gtest/gtest.h"
#include "../../includes/bst/bst.h"
using namespace std;

bool test_tree_insert(bool debug = false)
{
  // build null tree
  Ptr<tree_node<int> > root;

  // insert into null tree
  int insert = 5;
  tree_insert(root, insert);
  if (debug) tree_print_debug(root);
  if (in_order_string(root) != "[5]")
  {
    if (debug) 
      cout << "In order is " << in_order_string(root) << " instead of [5]\n";
    return false;
  }

  // build out tree using inserts
  for (int i = 0; i <= 10; i++)
  {
    tree_insert(root, i);
    if (debug) tree_print_debug(root);
  }

  if (in_order_string(root) != "[0][1][2][3][4][5][5][6][7][8][9][10]")
  {
    if (debug) 
    {
      cout << "In order is " << in_order_string(root) << " instead of ";
      cout << "[0][1][2][3][4][5][5][6][7][8][9][10]" << endl;
    }
    return false;
  }
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeInsert) 
{
  EXPECT_EQ(1, test_tree_insert(false));
}

bool test_tree_search(bool debug = false)
{
  // build null tree
  Ptr<tree_node<int> > root;
  int exists = 5;
  int nexists = 100;

  // search null tree
  Ptr<tree_node<int> > temp = tree_search(root, nexists);
  if (!!temp) return false;
  bool found = tree_search(root, nexists, temp);
  if (found) return false;
  if (debug) cout << "Passed null tree search." << endl;

  // build one node tree
  int insert = 5;
  tree_insert(root, insert);
  if (debug) tree_print_debug(root);
  
  // search one node tree
  temp = tree_search(root, exists);
  if (!temp) return false;
  temp = tree_search(root, nexists);
  if (!!temp) return false;
  if (debug) cout << "Passed two arg search function." << endl;

  found = tree_search(root, exists, temp);
  if (!found) return false;
  found = tree_search(root, nexists, temp);
  if (found) return false;
  if (debug) cout << "Passed three arg search function." << endl;

  // build out tree using inserts
  for (int i = 0; i <= 10; i++)
    tree_insert(root, i);
  if (debug) tree_print_debug(root);

  // search full tree
  for (int i = 0; i <= 10; i++)
  {
    temp = tree_search(root, i);
    if (!temp) return false;
    found = tree_search(root, i, temp);
    if (!found) return false;
  }

  temp = tree_search(root, nexists);
  if (!!temp) return false;
  found = tree_search(root, nexists, temp);
  if (found) return false;
  
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeSearch) 
{
  EXPECT_EQ(1, test_tree_search(false));
}

bool test_tree_print(bool debug = false)
{
  // build null tree
  Ptr<tree_node<int> > root;

  // print null tree
  cout << "Print Null Tree: \n";
  tree_print(root);
  cout << "Debug Print Null Tree: \n";
  tree_print_debug(root);

  // build one node tree
  int insert = 5;
  tree_insert(root, insert);
  
  // print one node tree
  cout << "Print One Node Tree: \n";
  tree_print(root);
  cout << "Debug Print One Node Tree: \n";
  tree_print_debug(root);

  // build out tree using inserts
  for (int i = 0; i <= 10; i++)
    tree_insert(root, i);

  // print full tree
  cout << "Print Full Tree: \n";
  tree_print(root);
  cout << "Debug Print Full Tree: \n";
  tree_print_debug(root);
  
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreePrint) 
{
  EXPECT_EQ(1, test_tree_print(false));
}

bool test_tree_clear(bool debug = false)
{
  // build null tree
  Ptr<tree_node<int> > root;

  // clear null tree
  tree_clear(root);
  if (debug) tree_print_debug(root);
  if (!!root) return false;

  // build one node tree
  int insert = 5;
  tree_insert(root, insert);
  
  // clear one node tree
  tree_clear(root);
  if (debug) tree_print_debug(root);
  if (!!root) return false;

  // build out tree using inserts
  for (int i = 0; i <= 10; i++)
    tree_insert(root, i);

  // clear full tree
  tree_clear(root);
  if (debug) tree_print_debug(root);
  if (!!root) return false;
  
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeClear) 
{
  EXPECT_EQ(1, test_tree_clear(false));
}

bool test_tree_erase(bool debug = false)
{
  // build null tree
  Ptr<tree_node<int> > root;
  int exists = 5;
  int nexists = 101;

  // erase from null tree
  if (debug)
  {
    cout << "Before erasing from null tree." << endl;
    tree_print_debug(root);
  }
  bool erased = tree_erase(root, nexists);
  if (debug)
  {
    cout << "Erased from null tree." << endl;
    tree_print_debug(root);
  }
  if (!!root || erased) return false;

  // build one node tree
  tree_insert(root, exists);
  
  // attempt to erase nonexist from one node tree
  if (debug)
  {
    cout << "Before erasing nexist from one node tree." << endl;
    tree_print_debug(root);
  }
  erased = tree_erase(root, nexists);
  if (debug)
  {
    cout << "Erased nexist from one node tree." << endl;
    tree_print_debug(root);
  }
  if (erased) return false;

  // erase exist from one node tree
  if (debug)
  {
    cout << "Before erasing exist from one node tree." << endl;
    tree_print_debug(root);
  }
  erased = tree_erase(root, exists);
  if (debug)
  {
    cout << "Erased exist from one node tree." << endl;
    tree_print_debug(root);
  }
  if (!erased) 
  {
    if (debug) cout << "Erased is true when it should be false." << endl;
    return false;
  }
  if (!!root)
  {
    if (debug) cout << "Root is not null." << endl;
    return false;
  }

  // build out tree using inserts
  for (int i = 0; i <= 10; i++) tree_insert(root, i);

  // attempt to erase nonexist from tree
  if (debug)
  {
    cout << "Before erasing nexist from full tree." << endl;
    tree_print_debug(root);
  }
  erased = tree_erase(root, nexists);
  if (debug)
  {
    cout << "Erased nexist from full tree." << endl;
    tree_print_debug(root);
  }
  if (erased) return false;

  // clear tree using erase
  for (int i = 0; i <= 10; i++)
  {
    erased = tree_erase(root, i);
    if (debug)
    {
      cout << "Erased " << i << endl; 
      tree_print_debug(root);
    }
    if (!erased) return false;
  }

  // TESTING SPECIFIC CASES
  int center = 100;
  int left = 0;
  int left_left = -5;
  int left_right = 5;
  int right = 200;
  int right_left = 195;
  int right_right = 205;

  // CASE 1: node with left and right subtree
  tree_insert(root, center);
  tree_insert(root, left);
  tree_insert(root, left_left);
  tree_insert(root, left_right);
  tree_insert(root, right);
  tree_insert(root, right_left);
  tree_insert(root, right_right);
  if (debug)
  {
    cout << "Node with both subtrees:" << endl;
    tree_print_debug(root);
  }

  if (debug) cout << "Erasing nexists..." << endl;
  erased = tree_erase(root, nexists);
  if (erased)
  {
    cout << "Erased was true instead of false." << endl;
    return false;
  }
  if (debug) cout << "Erasing center..." << endl;
  erased = tree_erase(root, center);
  if (!erased)
  {
    cout << "Erased was false instead of true." << endl;
    return false;
  }
  if (debug)
  {
    cout << "Erased center node from node with both subtrees:" << endl;
    tree_print_debug(root);
  }
  if (in_order_string(root) != "[-5][0][5][195][200][205]")
  {
    if (debug) 
    {
      cout << "In order is " << in_order_string(root) << " instead of ";
      cout << "[-5][0][5][195][200][205]" << endl;
    }
    return false;
  }
  if (root->_item != left_right) return false;
  tree_clear(root);

  // CASE 2: node with left subtree only
  tree_insert(root, center);
  tree_insert(root, left);
  tree_insert(root, left_left);
  tree_insert(root, left_right);
  if (debug)
  {
    cout << "Node with left subtree:" << endl;
    tree_print_debug(root);
  }

  if (debug) cout << "Erasing nexists..." << endl;
  erased = tree_erase(root, nexists);
  if (erased)
  {
    cout << "Erased was true instead of false." << endl;
    return false;
  }
  if (debug) cout << "Erasing center..." << endl;
  erased = tree_erase(root, center);
  if (!erased)
  {
    cout << "Erased was false instead of true." << endl;
    return false;
  }
  if (debug)
  {
    cout << "Erased center node from node with left subtree only:" << endl;
    tree_print_debug(root);
  }
  if (in_order_string(root) != "[-5][0][5]")
  {
    if (debug) 
      cout << "In order is " << in_order_string(root) << " instead of [-5][0][5]\n";
    return false;
  }
  if (root->_item != left_right) return false;
  tree_clear(root);

  // CASE 3: node with right subtree only
  tree_insert(root, center);
  tree_insert(root, right);
  tree_insert(root, right_left);
  tree_insert(root, right_right);
  if (debug)
  {
    cout << "Node with right subtree:" << endl;
    tree_print_debug(root);
  }

  if (debug) cout << "Erasing nexists..." << endl;
  erased = tree_erase(root, nexists);
  if (erased)
  {
    cout << "Erased was true instead of false." << endl;
    return false;
  }
  if (debug) cout << "Erasing center..." << endl;
  erased = tree_erase(root, center);
  if (!erased)
  {
    cout << "Erased was false instead of true." << endl;
    return false;
  }
  if (debug)
  {
    cout << "Erased center node from node with right subtree only:" << endl;
    tree_print_debug(root);
  }
  if (in_order_string(root) != "[195][200][205]")
  {
    if (debug) cout << in_order_string(root) << " instead of [195][200][205]\n";
    return false;
  }
  if (root->_item != right) return false;
  tree_clear(root);

  // CASE 4: node with no subtrees
  tree_insert(root, center);
  if (debug)
  {
    cout << "Node with no subtrees:" << endl;
    tree_print_debug(root);
  }

  if (debug) cout << "Erasing nexists..." << endl;
  erased = tree_erase(root, nexists);
  if (erased)
  {
    cout << "Erased was true instead of false." << endl;
    return false;
  }
  if (debug) cout << "Erasing center..." << endl;
  erased = tree_erase(root, center);
  if (!erased)
  {
    cout << "Erased was false instead of true." << endl;
    return false;
  }
  if (debug)
  {
    cout << "Erased center node from node without subtrees only:" << endl;
    tree_print_debug(root);
  }
  if (in_order_string(root) != "")
  {
    if (debug) cout << in_order_string(root) << " instead of no output\n";
    return false;
  }
  if (!!root) return false;
  tree_clear(root);

  tree_insert(root, 97);
  tree_insert(root, 44);
  tree_insert(root, 95);
  tree_insert(root, 40);
  tree_insert(root, 46);
  tree_insert(root, 81);
  tree_insert(root, 60);
  if (debug)
  {
    cout << "Node with right subtree:" << endl;
    tree_print_debug(root);
  }

  tree_erase(root, 95);
  tree_print_debug(root);

  
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeErase) 
{
  EXPECT_EQ(1, test_tree_erase(true));
}

bool test_tree_from_sorted_list(bool debug = false)
{
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 1; i < 10; i++)
  {
    Ptr<tree_node<int> > root = tree_from_sorted_list(a, i);
    if (debug) 
    {
      cout << "Tree from list of size " << i+1 << endl;
      tree_print_debug(root);
    }
    tree_clear(root);
  }
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeFromSortedList) 
{
  EXPECT_EQ(1, test_tree_from_sorted_list(false));
}

bool test_tree_traversals(bool debug = false)
{
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 1; i < 10; i++)
  {
    Ptr<tree_node<int> > root = tree_from_sorted_list(a, i);
    if (debug) 
    {
      cout << "Tree from list of size " << i+1 << endl;
      tree_print_debug(root);
    }
    cout << "IN ORDER:" << endl;
    string s = in_order_string(root);
    cout << s << endl;
    in_order(root);
    cout << endl;

    cout << "PRE ORDER:" << endl;
    s = pre_order_string(root);
    cout << s << endl;
    pre_order(root);
    cout << endl;

    cout << "POST ORDER:" << endl;
    s = post_order_string(root);
    cout << s << endl;
    post_order(root);
    cout << endl << endl;

    tree_clear(root);
  }
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeTraversals)
{
  EXPECT_EQ(1, test_tree_traversals(false));
}

bool test_tree_copy(bool debug = false)
{
  // copy empty tree
  Ptr<tree_node<int> > root;
  Ptr<tree_node<int> > copy;
  copy = tree_copy(root);
  if (!!copy || !!root) return false;

  // copy full trees
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 1; i < 10; i++)
  {
    root = tree_from_sorted_list(a, i);
    if (debug) 
    {
      cout << "Tree from list of size " << i+1 << endl;
      tree_print_debug(root);
    }
    copy = tree_copy(root);
    if (debug) 
    {
      cout << "Copy of Tree from list of size " << i+1 << endl;
      tree_print_debug(copy);
    }

    if (post_order_string(root) != post_order_string(copy)
      || in_order_string(root) != in_order_string(copy)
      || pre_order_string(root) != pre_order_string(copy)
      || copy == root) return false;
    
    tree_clear(root);
  }
  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeCopy)
{
  EXPECT_EQ(1, test_tree_copy(false));
}

bool test_tree_add(bool debug = false)
{
  // add two empty trees
  Ptr<tree_node<int> > r1;
  Ptr<tree_node<int> > r2;
  if (debug)
  {
    cout << "TREE 1: \n";
    tree_print_debug(r1);
    cout << "TREE 2: \n";
    tree_print_debug(r2);
  }

  tree_add(r1, r2);
  if (debug)
  {
    cout << "Added trees." << endl;
    cout << "TREE 1: \n";
    tree_print_debug(r1);
    cout << "TREE 2: \n";
    tree_print_debug(r2);
  }

  if (!!r1 || !!r2) return false;

  // add empty tree to full tree
  int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 1; i < 10; i++)
  {
    r1 = tree_from_sorted_list(a, i);
    if (debug)
    {
      cout << "TREE 1: \n";
      tree_print_debug(r1);
      cout << "TREE 2: \n";
      tree_print_debug(r2);
    }

    string before_add = in_order_string(r1);

    tree_add(r1, r2);
    if (debug)
    {
      cout << "Added trees." << endl;
      cout << "TREE 1: \n";
      tree_print_debug(r1);
      cout << "TREE 2: \n";
      tree_print_debug(r2);
    }

    if (before_add != in_order_string(r1)) return false;
    tree_clear(r1);
  }

  // add a full tree to empty tree
  for (int i = 1; i < 10; i++)
  {
    r2 = tree_from_sorted_list(a, i);
    if (debug)
    {
      cout << "TREE 1: \n";
      tree_print_debug(r1);
      cout << "TREE 2: \n";
      tree_print_debug(r2);
    }

    tree_add(r1, r2);
    if (debug)
    {
      cout << "Added trees." << endl;
      cout << "TREE 1: \n";
      tree_print_debug(r1);
      cout << "TREE 2: \n";
      tree_print_debug(r2);
    }

    if (in_order_string(r1) != in_order_string(r2)) return false;
    tree_clear(r1);
    tree_clear(r2);
  }

  // add two full trees
  int b[10] = {-5, -4, -3, -2, -1, 10, 11, 12, 13, 14};
  for (int i = 1; i < 10; i++)
  {
    r1 = tree_from_sorted_list(a, i);
    r2 = tree_from_sorted_list(b, i);
    if (debug)
    {
      cout << "TREE 1: \n";
      tree_print_debug(r1);
      cout << "TREE 2: \n";
      tree_print_debug(r2);
    }

    tree_add(r1, r2);
    if (debug)
    {
      cout << "Added trees." << endl;
      cout << "TREE 1: \n";
      tree_print_debug(r1);
      cout << "TREE 2: \n";
      tree_print_debug(r2);
    }

    tree_clear(r1);
    tree_clear(r2);
  }

  return true;
}

TEST(TEST_BST_FUNCTIONS, TestTreeAdd)
{
  EXPECT_EQ(1, test_tree_add(false));
}

bool test_big_three(bool debug = false)
{
  int list[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  BST<int> a;
  if (!a.empty()) return false;

  BST<int> b(list, 10);
  BST<int> c(b);
  a = c;

  if (a.post_order() != b.post_order() || 
      a.post_order() != c.post_order() || 
      b.post_order() != c.post_order()) return false;

  return true;
}

TEST(TEST_BST, TestBigThree)
{
  EXPECT_EQ(1, test_big_three(false));
}

bool test_insert(bool debug = false)
{
  BST<int> a;
  for (int i = 0; i < 10; i++)
  {
    a.insert(i);
    if (debug) cout << "Inserted " << i << ".\n" << a;
    if (!a.contains(i)) return false;
  }
  return true;
}

TEST(TEST_BST, TestInsert)
{
  EXPECT_EQ(1, test_insert(false));
}

bool test_search_contains(bool debug = false)
{
  int list[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1};
  BST<int> a(list);
  for (int i = 0; i < 10; i++)
  {
    Ptr<tree_node<int> > ptr;
    if (!a.search(i, ptr) || !a.contains(i)) return false;
    if (debug) cout << "Ptr Found: " << *ptr << "\n";
    if (a.search(i + 20, ptr) || a.contains(i + 20)) return false;
    if (!!ptr) return false;
  }
  return true;
}

TEST(TEST_BST, TestSearchContains)
{
  EXPECT_EQ(1, test_search_contains(false));
}

bool test_erase(bool debug = false)
{
  int list[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
  BST<int> a(list, 11);
  if (debug) cout << a;

  for (int i = 0; i < 10; i++)
  {
    a.erase(i);
    if (debug) cout << "Erased " << i << ".\n" << a;
  }
  return true;
}

TEST(TEST_BST, TestErase)
{
  EXPECT_EQ(1, test_erase(false));
}

bool test_clear_all(bool debug = false)
{
  int list[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  BST<int> a(list, 10);
  if (debug) cout << a;

  a.clear_all();
  if (debug) cout << "After clearing...\n" << a;

  if (debug) cout << "Clearing null tree...\n";
  a.clear_all();
  if (debug) cout << a;
  
  return true;
}

TEST(TEST_BST, TestClearAll)
{
  EXPECT_EQ(1, test_clear_all(false));
}

bool test_empty(bool debug = false)
{
  int list[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  BST<int> a(list, 10);
  if (a.empty()) return false;

  BST<int> b;
  if (!b.empty()) return false;

  BST<int> c(list, 1);
  if (c.empty()) return false;
  
  return true;
}

TEST(TEST_BST, TestEmpty)
{
  EXPECT_EQ(1, test_empty(false));
}

bool test_add_equal(bool debug = false)
{
  int list[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  BST<int> a(list, 10);
  BST<int> b(list, 10);
  if (debug) cout << "TREE 1:\n" << a << endl << "TREE 2:\n" << b << endl;

  a += b;

  if (debug) cout << "TREE 1:\n" << a << endl << "TREE 2:\n" << b << endl;
  if (debug) cout << a.in_order() << endl;
  return true;
}

TEST(TEST_BST, TestAddEqual)
{
  EXPECT_EQ(1, test_add_equal(false));
}

bool test_traversals(bool debug = false)
{
  int list[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  BST<int> a(list, 10);
  BST<int> b(list, 10);

  if (debug)
  {
    cout << "TREE A:\n";
    cout << a;
    cout << "TREE B:\n";
    cout << b;

    cout << "PREORDER\na: " << a.pre_order() << endl;
    cout << "b: " << b.pre_order() << endl;
    cout << "INORDER\na: " << a.in_order() << endl;
    cout << "b: " << b.in_order() << endl;
    cout << "POSTORDER\na: " << a.post_order() << endl;
    cout << "b: " << b.post_order() << endl;
  }

  if (a.pre_order() != b.pre_order() || 
      a.in_order() != b.in_order() ||
      a.post_order() != b.post_order()) return false;
  
  return true;
}

TEST(TEST_BST, TestTraversals)
{
  EXPECT_EQ(1, test_traversals(false));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}


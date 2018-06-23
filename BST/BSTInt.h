#ifndef BST_INT_H
#define BST_INT_H

#include "BSTNodeInt.h"
#include <iostream>

/* Header file for a BST class that holds ints.  You are welcome to add methods and variables */
/* Author: Christine Alvarado 
 * Author: Abhinav Rana
 */

class BSTInt {

public:

    /** Default constructor.
      Initialize an empty BST.
      This definition is called an INLINE definition
      because it is not separate from the declaration.
      It's OK in this case because the method is trivial
      but normally you should AVOID inline definitions.
    */
    BSTInt() : root(0), isize(0), treeHeight(0) {}


    /** Default destructor.
      Delete every node in this BST.
    */
    ~BSTInt();

    /** Given a reference to a Data item, insert a copy of it in this BST.
    *  Return  true if the item was added to this BST
    *  as a result of this call to insert,
    *  false if an item equal to this one was already in this BST.
    *  Note: This function should use only the '<' operator when comparing
    *  Data items. (should not use ==, >, <=, >=)  For the reasoning
    *  behind this, see the assignment writeup.
    */
    bool insert(int item);


    /** Find a Data item in the BST.
    *  Return true if the item is in the BST or false otherwise
    *  Note: This function should use only the '<' operator when comparing
    *  Data items. (should not use ==, >, <=, >=).  For the reasoning
    *  behind this, see the assignment writeup.
    */
    bool find(int item) const;

  
    /** Return the number of items currently in the BST.
    */
    unsigned int size() const;


    /** Return the height of the BST.
      Height of tree with just root node is 0
    */
    unsigned int height() const;


    /** Return true if the BST is empty, else false. 
    */
    bool empty() const;

    /** Root of this tree
    */
    BSTNodeInt* root;

private:

    /** Pointer to the root of this BST, or 0 if the BST is empty */
    //BSTNodeInt* root;

    /** Number of Data items stored in this BST. 
    *  Cache this number for efficiency. */
    unsigned int isize;

    /**
    * This stores the height of the BST
    */
    unsigned int treeHeight;


    /** do a postorder traversal, deleting nodes
    * This is a helper for the destructor
    * This method is static because it acts on BSTNodeInts
    *   and not on the BSTInt object directly.
    */
    static void deleteAll(BSTNodeInt* n);
};


#endif //BST_INT_H

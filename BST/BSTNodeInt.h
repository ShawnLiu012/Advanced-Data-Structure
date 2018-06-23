#ifndef BSTNODE_INT_H
#define BSTNODE_INT_H

#include <iostream>

class BSTNodeInt {

public:

    BSTNodeInt* left;
    BSTNodeInt* right;
    BSTNodeInt* parent;
    const int data;

    /** Constructor.  Initialize a BSTNode with the given Data item,
    *  no parent, and no children.
    */
    BSTNodeInt(int d);  
}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
std::ostream & operator<<(std::ostream& stm, const BSTNodeInt & n);


#endif // BSTNODE_INT_H

#ifndef BSTNODE_INT_H
#define BSTNODE_INT_H

#include <iostream>

class BSTNodeInt {

public:
  // We'll make the instance variables public.
  // Arguably we should use getters and setters but there's a lot 
  //   to learn with this first assignment so let's keep the code a bit shorter for now
  BSTNodeInt* left;
  BSTNodeInt* right;
  BSTNodeInt* parent;
  const int data;   // the const int stored in this node.


  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNodeInt(int d);  
}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
std::ostream & operator<<(std::ostream& stm, const BSTNodeInt & n);


#endif // BSTNODE_INT_H

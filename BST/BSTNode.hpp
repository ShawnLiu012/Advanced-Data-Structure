#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:

  Data const data;   // the const Data in this node.
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;


  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d);


  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor(); 

}; 


template <typename Data>
BSTNode<Data>::BSTNode(const Data & d) : data(d), left(0), right(0), parent(0) {}

/* Return a pointer to the BSTNode that contains the item that is sequentially next 
 * in the tree */
template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor()
{
    BSTNode<Data>* next = this;

    if (next->right != NULL)
    {
        next = next->right; 
        while (next->left != NULL)
            next = next->left; 
        return next;
    }
    else if (next->parent != NULL && next->data < next->parent->data)
    {
        next = next->parent;
        return next;
    }
    else
    {
        while (next->parent != NULL && next->parent->data < next->data)
            next = next->parent; 

        if (next->parent == NULL)
            next = NULL; 
        else 
            next = next->parent; 

        return next;
    }

    return 0;
}

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
    stm << '[';
    stm << std::setw(10) << &n;                 // address of the BSTNode
    stm << "; p:" << std::setw(10) << n.parent; // address of its parent
    stm << "; l:" << std::setw(10) << n.left;   // address of its left child
    stm << "; r:" << std::setw(10) << n.right;  // address of its right child
    stm << "; d:" << n.data;                    // its data field
    stm << ']';
    return stm;
}

#endif // BSTNODE_HPP

#include "BSTInt.h"

/* Function definitions for a int-based BST class */


/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
    deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
    if (!root) 
    {  
        root = new BSTNodeInt(item); 
        isize++; 
        return true; 
    }

    BSTNodeInt* curr = root;
    bool added = false;
    unsigned int tempHeight = 0;

    while (true)
    {
        if (curr->data < item)
        {
            if (!curr->right)
            {
                curr->right = new BSTNodeInt(item);
                curr->right->parent = curr;
                isize++;
                tempHeight++;
                added = true;
                break;
            }
            else
            {
              curr = curr->right;
              tempHeight++;
            }
        }
        else if (item < curr->data)
        {
            if (!curr->left)
            {
                curr->left = new BSTNodeInt(item);
                curr->left->parent = curr;
                isize++;
                tempHeight++;
                added = true;
                break; 
            }
            else
            {
                curr = curr->left; 
                tempHeight++;
            }
        }
        else 
        {
            added = false;
            break;
        }
    }

    if (treeHeight < tempHeight)
        treeHeight = tempHeight;

    return added; 
}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
    BSTNodeInt* curr = root;

    while (curr)
    {
        if (curr->data < item) 
        {
          curr = curr->right;
        }
        else if (item < curr->data) 
        {
          curr = curr->left;
        }
        else 
        {
          return true; 
        }
    }
    return false; 
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
    return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
 */
unsigned int BSTInt::height() const
{
    return treeHeight;
}


/** Return true if the BST is empty, else false. 
 */
bool BSTInt::empty() const 
{
    return (isize == 0) ? true : false;  
}

/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt* n)
{
    if (n != NULL)  //only execute when N exists 
    {
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }
}

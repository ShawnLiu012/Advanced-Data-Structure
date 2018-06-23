#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include<fstream>
using namespace std;

int main() {
   
    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);

    // Create an instance of BST holding int 
    // BSTInt* b = new BSTInt();  
    // delete b;
    BSTInt b;

    // check for empty 
    if (b.empty())
        cout << "BST is empty the way it is supposed to be " << endl;
    else
    {
        cout << "BST is not empty" << endl;
        return -1;
    }

    // Could use: for(auto item : v) { instead of the line below
    // This only tests for items added, but not duplicated 
    for(int item : v) 
    { 
       if (b.insert(item))
            cout << "Correct bool value return when inserting " << item << endl;
       else 
        {
            cout << "Incorrect bool return value when inserting " << item << endl;
            return -1;
        }
    }

    //test size with basic one 
    
    if (b.size() != v.size())
        cout << "Not the correct size, should be " << v.size() << " not " << b.size() << endl;
    else 
        cout << "Vector size equals the BST Size: " << v.size() << endl;

    // test height with vector 
    
    if (b.height() != 2)
    {
        cout << "The height of the BST is not 2" << endl;
        return -1;
    }
    else
        cout << "Height of the BST is correct" << endl;


    //testing for duplicate 
    
    for (auto item: v)
    {
        if (!b.insert(item))
            cout << "Correctly did not add duplicate item: " << item << endl;
        else 
        {
            cout << "Incorrectly added duplicated item: " << item << endl;
            return -1;
        }
    }

    // testing find method 
    
    //testing find for elements in the BST
    for (auto item: v)
    {
        if (b.find(item))
            cout << "Correctly found " << item << endl;
        else
        {
            cout << "Did not find " << item << endl;
            return -1;
        }
    }

    //testing elements for items that are not in the BST
    for (int i = 101; i < 110; i++)
    {
        if (!b.find(i))
            cout << "Correctly did not find the item " << i << endl;
        else
        {
            cout << "Claims it found item " << i << " when that should't happen" << endl;
            return -1;
        }
    }

    //testing empty again 
    
    if (!b.empty())
        cout << "BST is not empty - which is correct " << endl;
    else
    {
        cout << "BST shows it is empty" << endl;
        return -1;
    }

    //checking for duplicates 
    for (int i = 0; i < 10; i++)
        b.insert(22);

    if(b.size() != v.size() + 1)
    {
        cout << "The size of the BST is " << b.size() << endl
             << "The size should be " << v.size() + 1 << endl
             << "Should not be adding duplicates!!!!!!!! " << endl;
        return -1;
    }

    if (b.height() == 3)
        cout << "Height is correct: 3 " << endl;
    else
    {
        cout << "Height should be 3 but shows " << b.height() << endl;
        return -1;
    }

    for (int i = 0; i < 10; i++)
        b.insert(42);

     if(b.size() != v.size() + 2)
    {
        cout << "The size of the BST is " << b.size() << endl
             << "The size should be " << v.size() + 1 << endl
             << "Should not be adding duplicates!!!!!!!! " << endl;
        return -1;
    }

    // checking the height   
    if (b.height() != 4)
    {
        cout << "Height of BST should be 4 but it is " << b.height() << endl;
        return -1;
    }

    else 
        cout << "Height of BST is correct " << endl;


    for (int i = 0; i < 10; i++)
        b.insert(178);

     if(b.size() != v.size() + 3)
    {
        cout << "The size of the BST is " << b.size() << endl
             << "The size should be " << v.size() + 1 << endl
             << "Should not be adding duplicates!!!!!!!! " << endl;
        return -1;
    }

    // checking the height     
    if (b.height() != 4)
    {
        cout << "Height of BST should be 4 but it is " << b.height() << endl;
        return -1;
    }

    else 
        cout << "Height of BST is correct " << endl;


    for (int i = 0; i < 10; i++)
        b.insert(20);

     if(b.size() != v.size() + 4)
    {
        cout << "The size of the BST is " << b.size() << endl
             << "The size should be " << v.size() + 1 << endl
             << "Should not be adding duplicates!!!!!!!! " << endl;
        return -1;
    }

    // checking the height  
    if (b.height() != 4)
    {
        cout << "Height of BST should be 4 but it is " << b.height() << endl;
        return -1;
    }

    else 
        cout << "Height of BST is correct " << endl;


    
    // Test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST..." << endl;
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;

    // ADD MORE TESTS HERE.  You might also want to change what is input
    // into the vector v.
    

    cout << "Attempting the SUPER TEST" << endl;

    ifstream in;
    string name;
    BST<string> unsortedTree;
    BST<string> sortedTree;
    vector<string> sortedVector;

    if (!unsortedTree.empty())
    {
        cout << "Unsorted BST is suppose to be empty" << endl;
        return -1;
    }

    if (!sortedTree.empty())
    {
        cout << "Unsorted BST is suppose to be empty" << endl;
        return -1;
    }
    cout << "Going to Create Sorted BST" << endl;
    in.open("actors_sorted.txt");

    //Check if input file was actually opened
    if(!in.is_open()) 
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }
    else            
        while (getline(in, name))
        {
            sortedVector.push_back(name); 
            sortedTree.insert(name);
        }     

    in.close();

    cout << "Done with creating sorted BST" << endl 
         << "Going to create UNSORTED BST " << endl;
    in.open("actors.txt");

    //Check if input file was actually opened
    if(!in.is_open()) 
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }
    else            
        while (getline(in, name))
            unsortedTree.insert(name);    

    cout << "Done creating the UNSORTED BST" << endl;


    // testing for duplicate
    
    for (auto item: sortedVector)
    {
        if (unsortedTree.insert(item).second)
        {
            cout << "Added duplicate: " << item << endl;
            return -1; 
        }

        if (sortedTree.insert(item).second)
        {
            cout << "Added duplicate: " << item << endl;
            return -1; 
        }
    }

     auto unsortedBeginIterator = unsortedTree.begin();
     auto unsortedEndIterator = unsortedTree.end();
     

     auto sortedBeginIterator = sortedTree.begin();
     auto sortedEndIterator = sortedTree.end();
     
     //checking for same in-order traversal
     for (auto item: sortedVector)
        {
            if (*sortedBeginIterator != item)
            {
                cout << "Error with Sorted BST elements in order " << endl;
                return -1;  
            }

            if (*unsortedBeginIterator != item)
            {
                cout << "Error with Un-Sorted BST elements in order " << endl;
                return -1;  
            }

            //cout << "Item found: " << item << endl;

            ++unsortedBeginIterator; //testing pre-increment
            sortedBeginIterator++; // testing post-increment 

            if (unsortedBeginIterator == unsortedEndIterator ||
                sortedBeginIterator == sortedEndIterator)
                break;

        }

        //checking for find item 
        for (auto item: sortedVector)
        {
            if (*unsortedTree.find(item) != item)
            {
                cout << "Item was not found in the unsorted BST " << endl;
                return -1;
            }

            if (*sortedTree.find(item) != item)
            {
                cout << "Item was not found in the sorted BST " << endl;
                return -1;
            }
        }

        
        // checking size and height for (un)sorted bst       
        if (unsortedTree.size() != 11794)
        {
            cout << "Not the correct size for unsorted bst " << endl;
            return -1;   
        }

        if (unsortedTree.height() != 32)
        {
            cout << "Not the correct height for unsorted bst " << endl;
            return -1;
        }

        if (sortedTree.size() != 11794)
        {
            cout << "Not the correct size for the sorted bst " << endl;
            return -1;
        }

        if (sortedTree.height() != 11793)
        {
            cout << "Not the correct height for the sorted bst " << endl; 
            return -1;
        }
        
    cout << "ALL TESTS PASSED" << endl;
return 0;
}

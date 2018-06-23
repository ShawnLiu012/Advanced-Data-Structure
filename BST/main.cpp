#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include<fstream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
    unsigned int size = 0;
    unsigned int height = 0;
    std::string name = "";
  
    //Check for Arguments
    if(argc != 2){
        cout << "Invalid number of arguments.\n" 
             << "Usage: ./main <input filename>.\n";
        return -1;
    }
  
    //Open file 
    ifstream in;
    in.open(argv[1]);    
  
    //Check if input file was actually opened
    if(!in.is_open()) 
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }
	else {	  
        // Follow the comments below to add code:

        BST<string> actorTree;
        
        while (getline(in, name))
            actorTree.insert(name);

        height = actorTree.height();
        size = actorTree.size();

        cout << "Size of tree: " << size << endl;
        cout << "Height of tree: " << height << endl;

        char prompt = 'y';
        while (prompt != 'n') {
            cout << "Enter actor/actress name: " << endl;
            getline(cin, name); 
            
            if (actorTree.find(name) != actorTree.end())
                cout << name << " found!" << endl;
            
            else 
                cout << name << " NOT found" << "\n";
            
            cout << "Search again? (y/n)" << endl;
            cin >> prompt;
            // Then ignore until newline
            cin.ignore( numeric_limits <streamsize> ::max(), '\n' );  
        }
        in.close();
    }
    
    return 0;

}

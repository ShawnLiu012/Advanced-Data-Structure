#include "ActorConnectionsGraph.hpp"

int main (int argc, char *argv[])
{
    if(argc != 5)
    {
        cout << "Invalid number of arguments. Should be 5 arguments" << endl;
        cout << "Usage: ./actorconnections <cast>.tsv <pair>.tsv <outFileName>.tsv bfs/ufind" << endl;
        return -1;
    }
    
    ActorConnectionsGraph o; //creates obhect of the actorconnectionsgraph
    
    o.loadFromFile(argv[1]); // loads the info from the file.
    
    string argFour = argv[4];
    if (argFour == "bfs")
    {
        o.loadPairsFromFile(argv[2]); //gets all the pairs from the file

        o.doBFSForEveryMovie();
        
        o.printOut(argv[3]);
        
        //cout << "BFS took: " << time << " milliseconds" << endl;

    }
   
    else
    {
        cout << "Disjoint not implemented" << endl;
    }
    
    
    
    return 0;
}

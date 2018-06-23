#ifndef ActorConnectionsGraph_hpp
#define ActorConnectionsGraph_hpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "Actor.hpp"
#include "MovieEdge.hpp"
#include "Movie.hpp"
#include <map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

class ActorComp
{
public:
    bool operator()(unordered_map<string, Actor>::iterator lhs, unordered_map<string, Actor>::iterator rhs) const
    {
        return lhs->second < rhs->second; //comparing actor objects
    }
};

class ActorConnectionsGraph
{
private:
    int bfs(string, string, int);
    unordered_map<string, Actor> setOfActors;
    typedef pair<int, string> movieKey;
    typedef map<movieKey, Movie> movieMap;
    movieMap setOfMovies;
    vector<pair<pair<string, string>, int>> pairs;
    
public:
    ActorConnectionsGraph(void);
    bool loadFromFile(const char*);
    bool loadPairsFromFile(const char*);
    void doBFSForEveryMovie();
    bool doDisjointSetsForEveryMovie(const char*, const char*);
    vector<string> outputVector;
    void printOut(const char*);
};

#endif /* ActorConnectionsGraph_hpp */

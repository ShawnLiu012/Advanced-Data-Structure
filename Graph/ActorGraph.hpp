#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
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

class ActorGraph
{
private:
    void bfs(string, string);
    void dijkstra(string, string);
    unordered_map<string, Actor> setOfActors;
    unordered_map<string, Movie> setOfMovies;
    
    
public:
    ActorGraph(void);
    bool loadFromFile(const char*);
    void outputPaths(const char*, bool);
    void connectActorsPathFinder(bool);
    vector<string> outputVector;
};

#endif // ACTORGRAPH_H

#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
#include "MovieEdge.hpp"
#include <unordered_map>
using namespace std;
class Actor
{
public:
    unordered_map<string, MovieEdge> edgeMap;
    Actor(string n ) : name(n) {}
    int distance = 0;
    int index;
    string name;
    string prevActor;
    bool visited;

    /** Less than test operator. */
    bool operator<(const Actor& other) const
    {
        if (distance != other.distance)
            return distance > other.distance;
        return name > other.name;
    }
};
#endif
		

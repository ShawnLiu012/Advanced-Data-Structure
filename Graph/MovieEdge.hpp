#ifndef MOVIEEDGE_H
#define MOVIEEDGE_H
#include <iostream>
#include <string>
using namespace std;
class Actor;
class MovieEdge
{
public:
    MovieEdge(string title, int y, int w, string n)
    {
        movieTitle = title;
        year = y;
        weight = w;
        edgeName = "--[" + movieTitle + "#@" + std::to_string(year) + "]-->";
        actorName = n;
    }
    int year;
    int weight;
    string edgeName;
    string actorName;
    string movieTitle;
};
#endif // ACTORGRAPH_H

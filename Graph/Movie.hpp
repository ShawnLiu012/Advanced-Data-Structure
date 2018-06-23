#ifndef MOVIE_H
#define MOVIE_H
#include <vector>
#include <string>
using namespace std;
class Movie
{
public:
    Movie(int y , string t) : movieYear(y), movieTitle(t) {};
    vector<string> actorVector;
    string movieTitle;
    int movieYear;    
};
#endif

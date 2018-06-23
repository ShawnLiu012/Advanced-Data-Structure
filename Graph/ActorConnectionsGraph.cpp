#include "ActorConnectionsGraph.hpp"

ActorConnectionsGraph::ActorConnectionsGraph(void) {}

bool ActorConnectionsGraph::loadFromFile(const char* in_filename)
{
    // Initialize the file stream
    ifstream infile(in_filename);
    
    bool have_header = false;
    
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
        
        // get the next line
        if (!getline( infile, s )) break;
        
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        
        istringstream ss( s );
        vector <string> record;
        
        while (ss) {
            string next;
            
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;
            
            record.push_back( next );
        }
        
        if (record.size() != 3)
            continue; //we should have exactly 3 columns
        
        string actorName(record[0]);
        string movieTitle(record[1]);
        int movieYear = stoi(record[2]);
        
        // we have an actor/movie relationship, now what?
        
        Movie tempMovie(movieYear, movieTitle); //creates an object of Movie with the name
        Actor tempActor(actorName); // create an object of actor with the name
        
        auto gotMovieIt = setOfMovies.find(movieKey(movieYear, movieTitle));
        auto gotActorIt = setOfActors.find(actorName);
        
        if (gotMovieIt == setOfMovies.end()) //movie does not exist
        {
            setOfMovies.insert(make_pair(movieKey(movieYear, movieTitle), tempMovie)); //insert movie object into map
            gotMovieIt = setOfMovies.find(movieKey(movieYear, movieTitle)); //get iterator to the movie in the map
            gotMovieIt->second.actorVector.push_back(actorName);
        }
        
        else //movie does exist
            gotMovieIt->second.actorVector.push_back(actorName);
        
        if (gotActorIt == setOfActors.end())
        {
            setOfActors.insert(std::make_pair(actorName, tempActor));
        }
    }
    
    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    
    infile.close();
    
    for (auto item : setOfMovies)
    {
        cout << item.first.first << item.first.second << endl;
        for (auto item : item.second.actorVector)
            cout << item << endl;
        cout << "............." << endl;
    }
    
    return true;
}

bool ActorConnectionsGraph::loadPairsFromFile(const char* in_filename)
{
    // Initialize the file stream
    ifstream infile(in_filename);
    
    bool have_header = false;
    
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
        
        // get the next line
        if (!getline( infile, s )) break;
        
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        
        istringstream ss( s );
        vector <string> record;
        
        while (ss) {
            string next;
            
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;
            
            record.push_back( next );
        }
        
        if (record.size() != 2)
            continue; //we should have exactly 2 columns
        
        string actorOne(record[0]);
        string actorTwo(record[1]);
    
        pairs.push_back(make_pair(make_pair(actorOne, actorTwo), 9999));
        
    }
    
    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    
    infile.close();
    
    return true;
}

void ActorConnectionsGraph::doBFSForEveryMovie()
{
    int weight;
    int nextWeight;
    auto pairsLeft = pairs.size();
    
    for (auto movie = setOfMovies.begin(); movie != setOfMovies.end(); movie++) //loops through all movies
    {
        weight = movie->first.first;
        auto movieNext = ++movie;
        movie--;
        nextWeight = movieNext->first.first;
        for (auto& actorOneString : movie->second.actorVector) //gets actor one string
        {
            auto actorOneIt = setOfActors.find(actorOneString); //actor one iterator
            for (auto& actorTwoString : movie->second.actorVector) //gets the string from the same movie
            {
                if (actorOneString != actorTwoString)
                {
                    MovieEdge tempEdge(movie->second.movieTitle,
                                       movie->second.movieYear, weight, actorTwoString);
                    if (actorOneIt->second.edgeMap.find(actorTwoString) == actorOneIt->second.edgeMap.end())
                        actorOneIt->second.edgeMap.insert(make_pair(actorTwoString, tempEdge));
                }
            }
        }
        
        if (weight < nextWeight || movieNext == setOfMovies.end())
        {
            for (auto& pair : pairs)
            {
                if (pair.second == 9999)
                {
                    pair.second = bfs(pair.first.first, pair.first.second, weight);
                    if (pair.second != 9999)
                        pairsLeft--;
                }
                
                if (pairsLeft == 0)
                    return;
            }
        }
    }
    
    //end timer
}

int ActorConnectionsGraph::bfs(string actorOne, string actorTwo, int year)
{
    queue<string> actorQueue;
    
    for (auto& actor : setOfActors) //update the distance and prevActor to infinity and empty string
    {
        actor.second.distance = numeric_limits<int>::max(); // set distance to infinity
        actor.second.prevActor = "";                        // sets the previous to  empty
    }
    
    auto currentActor = setOfActors.find(actorOne); //sets actorOne to the currentNode
    currentActor->second.distance = 0;
    actorQueue.push(currentActor->first); //push the curr to the queue
    
    while (!actorQueue.empty())
    {
        auto currentActorName = actorQueue.front(); //sets curr to the top of the queue
        currentActor = setOfActors.find(currentActorName);
        actorQueue.pop(); // deque curr node from the head of the queue
        
        for (auto& neighborEdge : currentActor->second.edgeMap) //for each of the curr's neighbor
        {
            auto neighborActor = setOfActors.find(neighborEdge.first);
            if (neighborActor->second.distance == numeric_limits<int>::max())
            {
                neighborActor->second.distance = currentActor->second.distance + 1;
                neighborActor->second.prevActor = currentActor->first;
                actorQueue.push(neighborActor->first);
            }
        }
    } // when we get here, we are done exploring from s
    
    if (setOfActors.find(actorTwo)->second.prevActor == "")
        return 9999;
    
    return year;
    
}

void ActorConnectionsGraph::printOut(const char* outFile)
{
    ofstream o (outFile);
    o << "Actor1" << "\t" << "Actor2" << "\t" << "Year" << endl;
    for (auto pair : pairs)
        o << pair.first.first << "\t" << pair.first.second << "\t" << pair.second << endl;
}








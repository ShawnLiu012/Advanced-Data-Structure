#include "ActorGraph.hpp"

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename)
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
        string movieKey = movieTitle + record[2]; //key is unique movie + year
        
        auto gotMovieIt = setOfMovies.find(movieKey); //okay finds movie+year based on string input
        auto gotActorIt = setOfActors.find(actorName); //finds actor based on string input
        
        if (gotMovieIt == setOfMovies.end()) //movie does not exist
        {
            setOfMovies.insert(std::make_pair(movieKey, tempMovie)); //insert movie object into map
            gotMovieIt = setOfMovies.find(movieKey); //get iterator to the movie in the map
            gotMovieIt->second.actorVector.push_back(actorName);
        }
        
        else //movie does exist
            gotMovieIt->second.actorVector.push_back(actorName);
        
        if (gotActorIt == setOfActors.end())
            setOfActors.insert(std::make_pair(actorName, tempActor));
    }
    
    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    
    return true;
}

//this method builds the connections with weighted edges or not
void ActorGraph::connectActorsPathFinder(bool w)
{
    int weight; //weight = 1 + (2015 - Y)
    for (auto& movie : setOfMovies) //loops through all movies
    {
        for (auto& actorOneString : movie.second.actorVector) //gets actor one string
        {
            auto actorOneIt = setOfActors.find(actorOneString); //actor one iterator
            for (auto& actorTwoString : movie.second.actorVector) //gets the string from the same movie
            {
                if (actorOneString != actorTwoString)
                {
                    // if use weights is true, then apply the formula, or else set weight to be 1
                    (w) ? weight = 1 + (2015 - movie.second.movieYear) : weight = 1;
                    MovieEdge tempEdge(movie.second.movieTitle,
                                       movie.second.movieYear, weight, actorTwoString);
                    if (actorOneIt->second.edgeMap.find(actorTwoString)
                        == actorOneIt->second.edgeMap.end()) // 2nd actor not found in edgeMap
                        actorOneIt->second.edgeMap.insert(make_pair(actorTwoString, tempEdge));
                    else if (tempEdge.weight <
                             actorOneIt->second.edgeMap.find(actorTwoString)->second.weight)
                    {
                        // the new edge between the two actors is less than the current edge
                        actorOneIt->second.edgeMap.erase(actorTwoString);
                        actorOneIt->second.edgeMap.insert(make_pair(actorTwoString, tempEdge));
                    }
                }
            }
        }
    }
}

void ActorGraph::outputPaths(const char* in_filename, bool weighted)
{
    // Initialize the file stream
    ifstream infile(in_filename);
    bool have_header = false;
    
    // keep reading lines until the end of file is reached
    while (infile)
    {
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
        
        while (ss)
        {
            string next;
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline(ss, next, '\t' )) break;
            record.push_back( next );
        }
        
        if (record.size() != 2)
            continue; // we should have exactly 2 columns
        
        string personOne(record[0]);
        string personTwo(record[1]);
        
        // we have actor1 and actor2, now what?
        
        (weighted) ? dijkstra(personOne, personTwo) : bfs(personOne, personTwo);
    }
    
    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return;
    }
    
    infile.close();
}

void ActorGraph::bfs(string actorOne, string actorTwo)
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
    
    stack<string> myStack;
    currentActor = setOfActors.find(actorTwo); //sets the current Actor to
    myStack.push("(" + currentActor->first + ")");
    while (currentActor->second.prevActor != "")
    {
        string edgeName = ((setOfActors.find(currentActor->second.prevActor))->second.edgeMap.find
                           (currentActor->first))->second.edgeName;
        myStack.push(edgeName);
        currentActor = setOfActors.find(currentActor->second.prevActor);
        myStack.push("(" + currentActor->first + ")");
    }
    
    string output;
    while (!myStack.empty())
    {
        output += myStack.top();
        myStack.pop();
    }
    
    outputVector.push_back(output);
}


  void ActorGraph::dijkstra(string actorOne, string actorTwo)
  {
    priority_queue<unordered_map<string, Actor>::iterator,
                   vector<unordered_map<string, Actor>::iterator>, ActorComp> minHeap;
    
    for (auto& actor : setOfActors) //update the distance and prevActor to infinity and empty string
    {
        actor.second.distance = numeric_limits<int>::max(); //set distance to infinity
        actor.second.prevActor = ""; //sets the previous to  empty
        actor.second.visited = false;
    }
    
      auto currentActor = setOfActors.find(actorOne);
      currentActor->second.distance = 0; //update the beginning Node to be 0 distance
      minHeap.push(currentActor);
      
      while (!minHeap.empty())
      {
          currentActor = minHeap.top(); 
          minHeap.pop();
          
          if (!currentActor->second.visited) //that means actor's neighbor distances haven't been calculated yet
            {
                if (currentActor->second.name == actorTwo)
                    break; // found the target Actor we wanted
                
                for (auto neighborEdge : currentActor->second.edgeMap)
                {
                    auto neighborActor = setOfActors.find(neighborEdge.first);
                    if (!neighborActor->second.visited) //if true, dont do this b/c already done
                    {
                        int weight = currentActor->second.distance + neighborEdge.second.weight;
                        if (neighborActor->second.distance > weight)
                        {
                            neighborActor->second.distance = weight;
                            neighborActor->second.prevActor = currentActor->first;
                            minHeap.push(neighborActor);
                        }
                    }
                }
                
                currentActor->second.visited = true; //that means all adjacent neighbor edges have been updated
            }
      }

      stack<string> myStack;
      myStack.push("(" + currentActor->first + ")");
      while (currentActor->second.prevActor != "")
      {
          string edgeName = ((setOfActors.find(currentActor->second.prevActor))->second.edgeMap.find
                             (currentActor->first))->second.edgeName;
          myStack.push(edgeName);
          currentActor = setOfActors.find(currentActor->second.prevActor);
          myStack.push("(" + currentActor->first + ")");
      }

      string output;
      while (!myStack.empty())
      {
        output += myStack.top();
        myStack.pop();
      }
              
      outputVector.push_back(output);

  }

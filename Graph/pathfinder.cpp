#include "ActorGraph.hpp"

int main (int argc, char *argv[])
{
   if(argc != 5)
   {
       cout << "Invalid number of arguments. Should be 5 arguments" << endl;
       cout << "Usage: ./pathfinder <cast>.tsv u/w <pair>.tsv <outFile>.tsv" << endl;
       return -1;
   }
   
   ActorGraph o;
   
   o.loadFromFile(argv[1]);
   
   string useWeight = argv[2];
   bool weighted;
   if (useWeight == "u")
       weighted = false;
   else
       weighted = true;
   
   o.connectActorsPathFinder(weighted);

   o.outputPaths(argv[3], weighted);
   
   ofstream out(argv[4]);
   out << "(actor)--[movie#@year]-->(actor)--..." << endl;
   for (auto item : o.outputVector)
      out << item << endl;
   out.close();
   
   return 0;
}

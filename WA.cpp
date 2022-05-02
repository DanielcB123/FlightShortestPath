/***********************************************************
  Synopsis: read from city.name and flight.txt
            store the graph in a adjacency matrix
***********************************************************/
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <climits>


using namespace std;



struct strCmp {
    bool operator()( const string s1, const string s2 ) const {
      return s1 <s2;
    }
  };
/*to map a city name with an unique integer */
map<const string, int, strCmp> city;

void add_edge(vector<int> adj2[], int src, int dest)
{
    adj2[src].push_back(dest);
}

void printElements(vector<int> adj2[], int n)
{
  
    // Traversing of vectors v to print
    // elements stored in it
    for (int i = 0; i < n; i++) {
  
        cout << "Elements at index "
             << i << ": ";
  
        // Displaying element at each column,

        for(int j=0;j<adj2[i].size();j++){
            cout << adj2[i][j]<<' ';
        }
        cout << endl;
    }
}
 
















bool BFS(vector<int> adj[], int src, int dest, int v, int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 

    /*


        CASE 1 <----------------------------------------------------------------------------


    */ 


// utility function to print the shortest distance
// between source vertex and destination vertex
void printShortestDistanceInRange(vector<int> adj[], int s,
                           int dest, int v, int conn)
{
    std::map<string,int,strCmp>::iterator it;
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        cout << "Given source and destination"
             << " are not connected";
        return;
    }
 
    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
    // distance from source is in distance array
    cout << "Shortest trip has "
         << dist[dest] << " flights";

    if(conn >= dist[dest]){
        cout <<"\nThis is within the amount requested\n";
    }else{
        cout <<"\nThis is more flights the amount requested\n";
    }
 
    // printing path from source to destination
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--){
        
        for (auto it = city.begin(); it != city.end(); ++it)
            if (it->second == path[i])
                cout << it->first << "---->";
    }
}



void printShortestDistance(vector<int> adj[], int s,
                           int dest, int v)
{
    std::map<string,int,strCmp>::iterator it;
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        cout << "Given source and destination"
             << " are not connected";
        return;
    }
 
    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
    // distance from source is in distance array
    cout << "Shortest trip has "
         << dist[dest] << " flights";
 
    // printing path from source to destination
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--){
        
        for (auto it = city.begin(); it != city.end(); ++it)
            if (it->second == path[i])
                cout << it->first << "---->";
    }
}


void clearVisitedAndDistance(bool visited[], int dist[], int pred[], int v){
        for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
}

    /*


        CASE 2 <----------------------------------------------------------------------------


    */


void ShortestViaIntermediateCities(vector<int> adj[], int start, int interm_A, int interm_B, int end, int v){
    int case1PathSize, case2PathSize;
    int pred[v], dist[v];

    vector<int> path1Case1, path2Case1, path3Case1;
    vector<int> path1Case2, path2Case2, path3Case2;


    if(BFS(adj, start, interm_A, v, pred, dist) && BFS(adj, start, interm_B, v, pred, dist) == false) {
        cout <<"\nNo route to the destination city via the intermediate cities.\n";

    }



    if(BFS(adj, start, interm_A, v, pred, dist) && BFS(adj, interm_A, interm_B, v, pred, dist) && BFS(adj, interm_B, end, v, pred, dist)){

    list<int> queue;
    bool visited[v];
    bool flag1=false,flag2=false,flag3=false;
 
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    clearVisitedAndDistance(visited, dist, pred, v);
 
    visited[start] = true;
    dist[start] = 0;
    queue.push_back(start);
 
    // standard BFS algorithm
    while (!queue.empty() || !flag1) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 

                if (adj[u][i] == interm_A){
                    // return true;
                    flag1=true;
                    break;
                }
            }
        }
    }


    int crawl = interm_A;
    path1Case1.push_back(crawl);
    while (pred[crawl] != -1) {
        path1Case1.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    clearVisitedAndDistance(visited, dist, pred, v);

    // FIND SHORTEST PATH1 TO INTERMEDIATE DESTINATION A FROM B ======================================================================

    queue.clear();


    clearVisitedAndDistance(visited, dist, pred, v);

    
    visited[interm_A] = true;
    dist[interm_A] = 0;
    queue.push_back(interm_A);
 
    
    while (!queue.empty() || !flag2) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 

                if (adj[u][i] == interm_B){
                    flag2=true;
                    break;
                }
            }
        }
    }

    
    crawl = interm_B;
    path2Case1.push_back(crawl);
    while (pred[crawl] != -1) {
        path2Case1.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
    clearVisitedAndDistance(visited, dist, pred, v);


    // // FIND SHORTEST PATH TO FINAL DESTINATION FROM A =======================================================================


    queue.clear();

 
    clearVisitedAndDistance(visited, dist, pred, v);
 
    visited[interm_B] = true;
    dist[interm_B] = 0;
    queue.push_back(interm_B);
 
    
    while (!queue.empty() || !flag3) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 

                if (adj[u][i] == end){
                    flag3=true;
                    break;
                }
            }
        }
    }


    crawl = end;
    path3Case1.push_back(crawl);
    while (pred[crawl] != -1) {
        path3Case1.push_back(pred[crawl]);
        crawl = pred[crawl];
    }


// ==============================================================================================================================================

    int case1PathSize = (path1Case1.size()-1) + (path2Case1.size()-1) + (path3Case1.size()-1);


    }


    if(BFS(adj, start, interm_B, v, pred, dist) && BFS(adj, interm_B, interm_A, v, pred, dist) && BFS(adj, interm_A, end, v, pred, dist)){
    // FIND SHORTEST PATH TO INTERMEDIATE DESTINATION B FROM START=======================================================================

    
    list<int> queue;
    bool visited[v];
    bool flag1Case2=false,flag2Case2=false,flag3Case2=false;
 
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    clearVisitedAndDistance(visited, dist, pred, v);
 
    visited[start] = true;
    dist[start] = 0;
    queue.push_back(start);
 
    
    while (!queue.empty() || !flag1Case2) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 

                if (adj[u][i] == interm_B){
                    flag1Case2=true;
                    break;
                }
            }
        }
    }







   
    int crawl = interm_B;
    path1Case2.push_back(crawl);
    while (pred[crawl] != -1) {
        path1Case2.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    clearVisitedAndDistance(visited, dist, pred, v);


    // FIND SHORTEST PATH1Case2 TO INTERMEDIATE DESTINATION A FROM B =======================================================================


    queue.clear();


    clearVisitedAndDistance(visited, dist, pred, v);

    
    visited[interm_B] = true;
    dist[interm_B] = 0;
    queue.push_back(interm_B);
 
    
    while (!queue.empty() || !flag2Case2) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 

                if (adj[u][i] == interm_A){
                    flag2Case2=true;
                    break;
                }
            }
        }
    }





    
    crawl = interm_A;
    path2Case2.push_back(crawl);
    while (pred[crawl] != -1) {
        path2Case2.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    clearVisitedAndDistance(visited, dist, pred, v);


    // // FIND SHORTEST PATH TO FINAL DESTINATION FROM A =======================================================================


    queue.clear();

 
    clearVisitedAndDistance(visited, dist, pred, v);
 
    visited[interm_A] = true;
    dist[interm_A] = 0;
    queue.push_back(interm_A);
 
    
    while (!queue.empty() || !flag3Case2) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 

                if (adj[u][i] == end){
                    flag3Case2=true;
                    break;
                }
            }
        }
    }



    crawl = end;
    path3Case2.push_back(crawl);
    while (pred[crawl] != -1) {
        path3Case2.push_back(pred[crawl]);
        crawl = pred[crawl];
    }


// ==============================================================================================================================================


    int case2PathSize = (path1Case2.size()-1) + (path2Case2.size()-1) + (path3Case2.size()-1);


    }
    if(case1PathSize<case2PathSize){
        cout << "\nPath is::\t";
        for (int i = path1Case1.size() - 1; i >= 0; i--){
            
            for (auto it = city.begin(); it != city.end(); ++it)
                if (it->second == path1Case1[i])
                    cout << it->first << "---->";
        }

        for (int i = path2Case1.size() - 2; i >= 0; i--){
            
            for (auto it = city.begin(); it != city.end(); ++it)
                if (it->second == path2Case1[i])
                    cout << it->first << "---->";
        }

        for (int i = path3Case1.size() - 2; i >= 0; i--){
            
            for (auto it = city.begin(); it != city.end(); ++it)
                if (it->second == path3Case1[i])
                    cout << it->first << "---->";
        }

        int case1PathSize = (path1Case1.size()-1) + (path2Case1.size()-1) + (path3Case1.size()-1);
        cout <<"\nThe trip has "<< case1PathSize<< " flights.\n";
    } else {
        cout << "\nPath is::\n";
        for (int i = path1Case2.size() - 1; i >= 0; i--){
            
            for (auto it = city.begin(); it != city.end(); ++it)
                if (it->second == path1Case2[i])
                    cout << it->first << "---->";
        }

        for (int i = path2Case2.size() - 2; i >= 0; i--){
            
            for (auto it = city.begin(); it != city.end(); ++it)
                if (it->second == path2Case2[i])
                    cout << it->first << "---->";
        }

        for (int i = path3Case2.size() - 2; i >= 0; i--){
            
            for (auto it = city.begin(); it != city.end(); ++it)
                if (it->second == path3Case2[i])
                    cout << it->first << "---->";
        }
    }

}




    /*


        CASE 3 <----------------------------------------------------------------------------


    */


int printShortestDistanceRoundTrip(vector<int> adj[], int s,
                           int dest, int v)
{
    std::map<string,int,strCmp>::iterator it;
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
    int connection = 0;
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        return 0;
    }
 
    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
 
    // printing path from source to destination
    cout << "\nPath is::\t";
    
    for (auto it = city.begin(); it != city.end(); ++it){
        if(it->second == dest){
            cout << it->first << "---->";
        }
    }
    
    
    for (int i = path.size() -1; i >= 0; i--){
        for (auto it = city.begin(); it != city.end(); ++it){
            if (it->second == path[i]){
                connection++;
                cout << it->first << "---->";
            }
        }
    }
    cout <<"\n\n";
    return connection;
}






void getAdjacent(int n, vector<int> adj[],int v){
    vector<int> connections;
    int lengthOfPath;
    for(int i=0; i<adj[n].size(); i++){
        lengthOfPath = printShortestDistanceRoundTrip(adj, adj[n][i], n, v);
        if(lengthOfPath>0){
            connections.push_back(lengthOfPath);
        }
    }

    if(connections.size() == 0){
                cout << "Given source and destination"
             << " are not connected";
    }else{
    cout    << "\nFrom the starting city, out off all the "
            <<      "round trip flights the shortest "
            <<      "flight had back as requested had "
            << *min_element(connections.begin(), connections.end()) 
            << " connections\n";
    }
}









int main(int argc, char *argv[]){
   int i,j, node1, node2,n;
   string line;
   

   cout << "Please enter the number of cities in your graph: " << endl;
   cin >> n; 

   vector<int> adj2[n];

 
   char lineChar[256];

   ifstream cityFile;
   cityFile.open("city.name", ios::in);

   for (i = 0; i < n; i++){
      cityFile.getline(lineChar,256);
      line = lineChar;
      city[line] = i;
   }


  /* initialize adjacent list*/

   ifstream flightFile;
   flightFile.open("flight.txt", ios::in);
   /* print the graph */
   cout << endl << "The graph generated can be represented by the following adjacent list : " << endl;
   cout << "-----------------------------------------------------------------------------------" << endl;

   while (flightFile.getline(lineChar, 256)){

      /* if line constains From: */
      line = lineChar;

      if (line.find("From:", 0) == 0 ){
          line.erase(0,7);
          node1 = city[line];
          //TESTING TO MAKE SURE THE ADJ2 had correct values
          cout << node1 << "--->" << line<< endl;
        
      } else {
          line.erase(0,7);
          node2 = city[line];
        //   graph.addEdge(node1,node2);
        cout <<"\t"<< node2<< "----->"<<line<<endl;
        add_edge(adj2,node1,node2);
      }
   }
   cout <<"================================================="<<endl;
   flightFile.close();


    int choice1 = 0, choice2 = 0, conn;

    while(true){
        cout <<"+-------------------------------------------------------------------+\n";
        cout <<"+              World Airlines                                       +\n";  
        cout <<"+                                                                   +\n"; 
        cout <<"+  1. Find Flight with x connections                                +\n"; 
        cout <<"+  2. Find Flight from city_A to city_D via city_B and city_C       +\n"; 
        cout <<"+  3. Shortest Round Trip                                           +\n";   
        cout <<"+  4. Exit                                                          +\n";      
        cout <<"+                                                                   +\n";             
        cout <<"+-------------------------------------------------------------------+\n";
        cin >> choice1;
        if(choice1 == 4){break;}
        if(choice1 == 1){
            cout <<"+-------------------------------------------+\n";
            cout <<"+              Shortest Flight              +\n";            
            cout <<"+-------------------------------------------+\n";
            string startCountry, startCity, endCountry, endCity, start, end, dummy;
            cout <<"Enter the starting country: "; 
            getline(cin, dummy);
            getline(cin, startCountry);
            cout <<"Enter the starting city: "; 
            getline(cin, startCity);
            cout <<"Enter the destination country: "; 
            getline(cin, endCountry);
            cout <<"Enter the destination city: "; 
            getline(cin, endCity);
            cout <<"Enter the number of connections: ";
            cin >> conn;

            start = startCity + ", " + startCountry;
            end = endCity + ", " + endCountry;


            int source = city[start], dest = city[end];
            cout <<"\n";
            printShortestDistanceInRange(adj2, source, dest, n,conn);
            cout <<"\n";
        }
        if(choice1==2){
            // here do the same for choice 1 but use conditional logic to route via the given intermediate cities
            string startCountry, startCity, endCountry, endCity, start, end, intermediateCity_A, intermediateCountry_A, intermediateCountry_B, intermediateCity_B, interm_A, interm_B, dummy;
            int convertedToIntStart, convertedToInt_IntermA, convertedToInt_IntermB, convertedToIntEnd;
            cout <<"Enter the starting country: "; 
            getline(cin, dummy);
            getline(cin, startCountry);
            cout <<"Enter the starting city: "; 
            getline(cin, startCity);
            cout <<"Enter the final destination country: "; 
            getline(cin, endCountry);
            cout <<"Enter the final destination city: "; 
            getline(cin, endCity);

            cout <<"Enter a country to fly through on the way to " +  endCity + ", " + endCountry + ": ";
            getline(cin, intermediateCountry_A);
            cout <<"Enter the city in " + intermediateCountry_A + " you will be traveling to on your way to " +  endCity + ", " + endCountry + ": ";
            getline(cin, intermediateCity_A);

            cout <<"Enter another country to fly through on the way to " +  endCity + ", " + endCountry + ": ";
            getline(cin, intermediateCountry_B);
            cout <<"Enter the city in " + intermediateCountry_B + " you will be traveling to on your way to " +  endCity + ", " + endCountry + ": ";
            getline(cin, intermediateCity_B);    

            start = startCity + ", " + startCountry;
            end = endCity + ", " + endCountry;
            interm_A = intermediateCity_A + ", " + intermediateCountry_A;
            interm_B = intermediateCity_B + ", " + intermediateCountry_B;
            cout <<interm_A<<endl;
            cout <<interm_B<<endl;
            convertedToIntStart = city[start];
            convertedToIntEnd = city[end];
            convertedToInt_IntermA = city[interm_A];
            convertedToInt_IntermB = city[interm_B];

            ShortestViaIntermediateCities(adj2, convertedToIntStart, convertedToInt_IntermA, convertedToInt_IntermB, convertedToIntEnd, n); 
        }
        if(choice1==3){
            string startCountry, startCity, start, dummy;
            int source;
            cout <<"Enter the starting country: "; 
            getline(cin, dummy);
            getline(cin, startCountry);
            cout <<"Enter the starting city: "; 
            getline(cin, startCity);
            start = startCity + ", " + startCountry;
            source = city[start];
            getAdjacent(source,adj2,n);
        }
    }
} 

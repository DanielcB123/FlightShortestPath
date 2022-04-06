/***********************************************************
  Synopsis: read from city.name and flight.txt
            store the graph in a adjacency matrix
***********************************************************/

#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <list>

using namespace std;



class Graph{
     public:
          Graph(int d);
          ~Graph(){};
          void print();
          void addEdge(int node1, int node2){ adj[node1][node2] = 1; };

     private: 
          int n;
          int adj[140][140]; // You may want to use adjacent list implementation for sparse graph instead
        //   vector<int> adj[140];
};

Graph::Graph(int d){
    for (int i=0; i < d; i++){
        for (int j=0; j < d; j++){
            adj[i][j] = 0;
        }
    }
    n = d;
};

void Graph::print(){
    for (int i=0; i < n; i++){
        cout << i << " -> ";
        for (int j=0; j < n; j++){
            if (adj[i][j]){
                cout << j << " ";
            }
        }
        cout << endl;
    }

};


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
    // adj2[dest].push_back(src);
    // cout <<"element--->"<<dest<<endl;
}

void printElements(vector<int> adj2[], int n)
{
  
    // Traversing of vectors v to print
    // elements stored in it
    for (int i = 0; i < n; i++) {
  
        cout << "Elements at index "
             << i << ": ";
  
        // Displaying element at each column,
        // begin() is the starting iterator,
        // end() is the ending iterator
        // for (auto it = adj2[i].begin();
        //      it != adj2[i].end(); it++) {
  
        //     // (*it) is used to get the
        //     // value at iterator is
        //     // pointing
        //     cout << *it << ' ';
        // }
        for(int j=0;j<adj2[i].size();j++){
            cout << adj2[i][j]<<' ';
        }
        cout << endl;
    }
}
 
















bool BFS(vector<int> adj[], int src, int dest, int v,
         int pred[], int dist[])
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
 
    // standard BFS algorithm
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
 
// utility function to print the shortest distance
// between source vertex and destination vertex
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
        // cout << path[i] << " ";
        for (auto it = city.begin(); it != city.end(); ++it)
            if (it->second == path[i])
                cout << it->first << "---->";
    }
}

























int main(int argc, char *argv[]){
   int i,j, node1, node2,n;
   string line;
   

   cout << "Please enter the number of cities in your graph: " << endl;
   cout << "---------------------------------------------------" << endl;
   cin >> n; 
   vector<int> adj2[n];

   Graph graph(n);
 
   char lineChar[256];

   ifstream cityFile;
   cityFile.open("city.name", ios::in);

   for (i = 0; i < n; i++){
      cityFile.getline(lineChar,256);
      line = lineChar;
      city[line] = i;
      cout << line << " is numbered as city " << city[line]<< endl;
    // auto it = city.find("Seattle, United States");
    //   cout << it->second << " is city as " <<it->first<< endl;
    //   cout <<"Seattle, United States"<<endl;
    //   cout << line<<endl;
   }


    cout <<"TESTINGTESTINGTESTING++++++  "<< city["Seattle, United States"] <<endl;
//     map<string, int>::iterator itr;
//     for (itr = city.begin(); itr != city.end(); ++itr) {
//         cout << '\t' << itr->first << '\t' << itr->second
//              << '\n';
//     }
//    cityFile.close();

  /* initialize adjacent matrix*/

   ifstream flightFile;
   flightFile.open("flight.txt", ios::in);
cout <<"================================================="<<endl;
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

   /* print the graph */
   cout << endl << "The graph generated can be represented by the following adjacent list : " << endl;
   cout << "-----------------------------------------------------------------------------------" << endl;
//    graph.print();
    // printElements(adj2,n);
    int choice1 = 0, choice2 = 0;
    string startCountry, startCity, endCountry, endCity, start, end, dummy;
    while(true){
    cout <<"+-------------------------------------------+\n";
    cout <<"+              World Airlines               +\n";  
    cout <<"+                                           +\n"; 
    cout <<"+  1. Find Flight with least connections    +\n"; 
    cout <<"+  2. Quit                                  +\n";     
    cout <<"+                                           +\n";             
    cout <<"+-------------------------------------------+\n";
    cin >> choice1;
    if(choice1 == 2){break;}
    if(choice1 == 1){
        cout <<"+-------------------------------------------+\n";
        cout <<"+              Shortest Flight              +\n";            
        cout <<"+-------------------------------------------+\n";
        cout <<"Enter the starting country: "; 
        getline(cin, dummy);
        getline(cin, startCountry);
        cout <<"Enter the starting city: "; 
        getline(cin, startCity);
        cout <<"Enter the destination country: "; 
        getline(cin, endCountry);
        cout <<"Enter the destination city: "; 
        getline(cin, endCity);
    }
    start = startCity + ", " + startCountry;
    end = endCity + ", " + endCountry;


    int source = city[start], dest = city[end];
    cout <<"\n";
    printShortestDistance(adj2, source, dest, n);
    cout <<"\n";
    }
} 
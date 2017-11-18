// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i
 
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
 
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
 
     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
 
       // Mark the picked vertex as processed
       sptSet[u] = true;
 
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)
 
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 
     // print the constructed distance array
     printSolution(dist, V);
}



      vector<int> dist(g.size(), INFINITO);
      set< pair<int,long> > frontier;
      pair<int,long> pair1(0,s);
      frontier.insert(pair1);

      while (!frontier.empty()) {
        pair<int,long> p = *frontier.begin();
        frontier.erase(frontier.begin());

        int d = p.first;
        int n = p.second;

        // this is our shortest path to n
        dist[n] = d;

        // now look at all edges out from n to update the frontier
        for (int i=0; i< g[n].size(); i++) {
          // update this node in the frontier if we have a shorter path
          if (dist[n]+g[n][i].cost < dist[g[n][i].head]) {
            if (dist[g[n][i].head] != INFINITO) {
              // we've seen this node before, so erase it from the set in order to update it
              pair<int,long> pair2(dist[g[n][i].head], g[n][i].head);
              frontier.erase(frontier.find(pair2));
            }
            pair<int,long> pair3(dist[n]+g[n][i].cost, g[n][i].head);
            frontier.insert(pair3);
            dist[g[n][i].head] = dist[n]+g[n][i].cost;
          }
        }
      }

      return dist;




          // vector<int> dist = vector<int>(g.size());     // The output array.  dist[i] will hold the shortest
    //                   // distance from src to i
 
    //  vector<bool> sptSet = vector<bool>(g.size()); // sptSet[i] will true if vertex i is included in shortest
    //                // path tree or shortest distance from src to i is finalized
  

    // printf("DIJKSTRA\n");
    //  // Initialize all distances as INFINITE and stpSet[] as false
    //  for (int i = 1; i < g.size(); i++){
    //     dist[i] = INFINITO;
    //     sptSet[i] = false;
    //   }
    //  // Distance of source vertex from itself is always 0
    //  dist[s] = 0;
 
    //  // Find shortest path for all vertices
    //  for (int count = 0; count < g.size(); count++)
    //  {
    //    // Pick the minimum distance vertex from the set of vertices not
    //    // yet processed. u is always equal to src in first iteration.
    //    int u = minDistance(dist, sptSet, g.size());
 
    //    // Mark the picked vertex as processed
    //    sptSet[u] = true;
    //    // Update dist value of the adjacent vertices of the picked vertex.
    //    for (int v = 0; v < g[u].size(); v++){
 
    //      // Update dist[v] only if is not in sptSet, there is an edge from 
    //      // u to v, and total weight of path from src to  v through u is 
    //      // smaller than current value of dist[v]
    //      if (!sptSet[v] && g[u][v].cost && dist[u] != INFINITO && dist[u]+g[u][v].cost < dist[v])
    //         dist[v] = dist[u] + g[u][v].cost;
    //         printf("%d\n", dist[v]);
    //   }
    //  }
    //   printf("SAIR DIJKSTRA\n");
    //  return dist;
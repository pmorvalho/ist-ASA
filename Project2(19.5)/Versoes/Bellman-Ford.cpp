// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
 
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
 
    printArr(dist, V);
 
    return;
}

    vector<int> dist = vector<int>(g.size());
    printf("ESTOU NO BELA MERDA\n");
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    dist[s] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges
    for (int i = 1; i < g.size(); i++)
    {
        for (int j = 0; j < g[i].size(); j++)
        {
            int u = i;
            int v = g[i][j].head;
            int weight = g[i][j].cost;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    printf("SAI DO BELA MERDA\n");
    return dist;





      vector< vector<int> > memo(g.size()+2, vector<int>(g.size(), INFINITO));

  // initialise base case
  memo[0][s] = 0;

  for (unsigned int  i = 1; i < memo.size(); i++) {
    // compute shortest paths from s to all vertices, with max hop-count i
    for (unsigned int  n = 0; n < g.size(); n++) {
      if (memo[i-1][n] < memo[i][n]) {
        memo[i][n] = memo[i-1][n];
      }
      for (unsigned int  j=0; j< g[n].size(); j++) {
        if (memo[i-1][n] != INFINITO) {
          if (memo[i-1][n] + g[n][j].cost < memo[i][g[n][j].head]) {
            memo[i][g[n][j].head] = memo[i-1][n] + g[n][j].cost;
          }
        }
      }
    }
  }
  return memo[g.size()];
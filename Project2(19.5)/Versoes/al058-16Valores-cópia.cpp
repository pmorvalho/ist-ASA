#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <exception>
#include <set>

using namespace std;

struct Edge {
  int head;
  int cost;
};

vector<int> bellmanford(vector< vector<Edge> > &g, int s) {

   vector<int> anteriores(g.size()+1, 0);
   vector<int> actuais(g.size()+1, 0);


  for (unsigned int  i = 1; i < actuais.size(); i++) {
    // compute shortest paths from s to all vertices, with max hop-count i
    for (unsigned int  n = 0; n < g.size(); n++) {
      if (anteriores[n] < actuais[n]) {
        actuais[n] = anteriores[n];
      }
      for (unsigned int  j=0; j< g[n].size(); j++) {
        if (anteriores[n] != INT_MAX) {
          if (anteriores[n] + g[n][j].cost < actuais[g[n][j].head]) {
            actuais[g[n][j].head] = anteriores[n] + g[n][j].cost;
          }
        }
      }
    }
    if(anteriores==actuais) break;
    anteriores=actuais;
  }
  return actuais;

}

int minDistance(vector<int> dist, vector<bool> sptSet, int V)
{
   // Initialize min value
   int min = INT_MAX, min_index=0;
 
   for (int v = 1; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
 
   return min_index;
}

vector<int> dijkstra(const vector< vector<Edge> >& g, int s) {

      vector<int> dist(g.size(), INT_MAX);
      set< pair<int,int> > frontier;
      pair<int,int> pair1(0,s);
      frontier.insert(pair1);

      while (!frontier.empty()) {
        pair<int,int> p = *frontier.begin();
        frontier.erase(frontier.begin());

        int d = p.first;
        int n = p.second;

        // this is our shortest path to n
        dist[n] = d;

        // now look at all edges out from n to update the frontier
        for (unsigned int  i=0; i< g[n].size(); i++) {
          // update this node in the frontier if we have a shorter path
          if (dist[n]+g[n][i].cost < dist[g[n][i].head]) {
            if (dist[g[n][i].head] != INT_MAX) {
              // we've seen this node before, so erase it from the set in order to update it
              pair<int,int> pair2(dist[g[n][i].head], g[n][i].head);
              frontier.erase(frontier.find(pair2));
            }
            pair<int,int> pair3(dist[n]+g[n][i].cost, g[n][i].head);
            frontier.insert(pair3);
            dist[g[n][i].head] = dist[n]+g[n][i].cost;
          }
        }
      }

      return dist;

}


int dijkstra_final(const vector< vector<Edge> >& g, int s, int local) {

      vector<int> dist(g.size(), INT_MAX);
      set< pair<int,int> > frontier;
      pair<int,int> pair1(0,s);
      frontier.insert(pair1);

      while (!frontier.empty()) {
        pair<int,int> p = *frontier.begin();
        frontier.erase(frontier.begin());

        int d = p.first;
        int n = p.second;

        // this is our shortest path to n
        dist[n] = d;


       if ( n==local){ return dist[n]; }
        // now look at all edges out from n to update the frontier
        for (unsigned int  i=0; i< g[n].size(); i++) {
          // update this node in the frontier if we have a shorter path
          if (dist[n]+g[n][i].cost < dist[g[n][i].head]) {
            if (dist[g[n][i].head] != INT_MAX) {
              // we've seen this node before, so erase it from the set in order to update it
              pair<int,int> pair2(dist[g[n][i].head], g[n][i].head);
              frontier.erase(frontier.find(pair2));
            }
            pair<int,int> pair3(dist[n]+g[n][i].cost, g[n][i].head);
            frontier.insert(pair3);
            dist[g[n][i].head] = dist[n]+g[n][i].cost;
          }
        }
      }
      return dist[local];
}

int johnson(vector< vector<Edge> > &g, vector<int> &filiais) {

  for (unsigned int  i = 1; i < g.size(); i++) {
    int j=i;
    Edge e = {j, 0};
    g[0].push_back(e);
  }
  /* corremos o algoritmo Bellman-Ford para ter o caminho mais curto de s para todos os vertices */
  vector<int> ssp;
    ssp = bellmanford(g, 0);
  /* fazemos com que deixem de existirem pesos negativos nos arcos */
  for (unsigned int  i=1; i < g.size(); i++) {
    for (unsigned int  j=0; j < g[i].size(); j++) {
      g[i][j].cost = g[i][j].cost + ssp[i] - ssp[g[i][j].head];
    }
  }
  /* com as repesagens dos arcos feitas agora conseguimos aplicar o algoritmo Dijkstra a todos os vertices do grafo */
  vector<int> caminhos_mais_curtos(g.size(), 0);
  vector<int> dij(g.size(), 0);
  for (unsigned int  i=0; i < filiais.size(); i++) {   
    dij = dijkstra(g, filiais[i]);
    for(unsigned int k=1; k < g.size(); k++){
      if(caminhos_mais_curtos[k]!=INT_MAX && dij[k]!=INT_MAX){
        dij[k] += ssp[k] - ssp[filiais[i]];
        caminhos_mais_curtos[k] += dij[k];
      }
      else{ caminhos_mais_curtos[k]=INT_MAX; }
  }
}

  int local_encontro = -1, shortest = INT_MAX;
  for (unsigned int i = 1; i < g.size(); i++) {
      if (caminhos_mais_curtos[i]!=INT_MAX && caminhos_mais_curtos[i] < shortest) {
        shortest = caminhos_mais_curtos[i];
        local_encontro = i;
      } 
  }
  if(local_encontro==-1)
  {
    return -1;
  }
  else{
    cout  << local_encontro << " " << shortest << endl;
    for (unsigned int  i=0; i < filiais.size(); i++) {   
     int custo = dijkstra_final(g, filiais[i], local_encontro);
     custo += ssp[local_encontro] - ssp[filiais[i]];
     printf("%d ", custo);
  }
    cout << endl;
    return 0;
  }
}


int main () {

  vector< vector<Edge> > g;
  vector<int> filiais;
  int fil, C, F, N;

  
  scanf("%d %d %d", &N, &F, &C);
  g.resize(N+1);
  filiais.resize(F);
    for(int i=0; i< F; i++) { /* le do input quais sao as localidades que tem filiais */
      scanf("%d ", &fil);
     filiais[i]=fil;
    }
    for(int i=0; i<C; i++) { /* vai ler do input todas as ligacoes dos diversos vertices do grafo */
      int v1, v2, w;
      scanf("%d %d %d", &v1, &v2, &w); /* vai ler do input uma localidade a respectiva localidade ligada pela aresta w */
        Edge e = {v2, w};
        g[v1].push_back(e);
    }

  /* algoritmo de johnson */
    int t = johnson(g, filiais);

    if( t==-1)     printf("N\n");

  return 0;

}
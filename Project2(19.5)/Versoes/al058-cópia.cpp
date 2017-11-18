/*       Grupo  58
 Pedro Orvalho    81151
 Antonio Lourenco 81796
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <set>

using namespace std;

struct Aresta {
  int origem;
  int destino;
  int custo;
};

const int INFINITO = INT_MAX;

vector<int> bellmanford(vector<Aresta> &arestas, vector< vector<Aresta> > &g, int s) {

  /* Criamos uma lista para verificar as alturas dos vertices */
   vector<int> actuais(g.size(), 0);

      for (unsigned int  k = 1; k < g.size(); k++) {

        for (unsigned int  j=0; j < arestas.size(); j++) {
          int t=j;
          Aresta a = arestas[t];
            if (actuais[a.origem] + a.custo < actuais[a.destino]) {
              /* calcula o caminho menor para o vertice desde a source */
              actuais[a.destino] = actuais[a.origem] + a.custo;
            }
        }

      }
  return actuais;
}

vector<int> dijkstra(vector< vector<Aresta> > &g, int s) {

      vector<int> distancias(g.size(), INFINITO);
      set< pair<int,int> > pilha_vertices;

      /* criamos a source e inserimo-la na pilha*/
      pair<int,int> pair1(0,s);
      pilha_vertices.insert(pair1);

      while(pilha_vertices.size() > 0) {

        pair<int,int> p = *pilha_vertices.begin();
        pilha_vertices.erase(pilha_vertices.begin());
        int d = p.first, n = p.second;

        distancias[n] = d; /* caminho mais curto para n */

        /* visitamos todas as arestas de n e fazemos update a pilha dos vertices */
        for (unsigned int i=0; i < g[n].size(); i++) {

          if (distancias[g[n][i].destino] > distancias[n]+g[n][i].custo) {

              if (distancias[g[n][i].destino] != INFINITO) {
                /* já visitamos o vertice antes, logo retiramo-lo da pilha*/
                pair<int,int> pair2(distancias[g[n][i].destino], g[n][i].destino);
                pilha_vertices.erase(pilha_vertices.find(pair2));
              }

              pair<int,int> pair3(distancias[n]+g[n][i].custo, g[n][i].destino);
              pilha_vertices.insert(pair3);
              distancias[g[n][i].destino] = distancias[n]+g[n][i].custo;
            }
          }
        }
      return distancias;
}

int main() {

  /* construimos o grafo*/
  int fil, C, F, N;

  /* le do input o numero de localidades(N), o numero de filiais(F) e o numero de ligacoes entre as localidades(C) */
  scanf("%d %d %d", &N, &F, &C);

  vector< vector<Aresta> > g = vector< vector< Aresta> >(N+1);
  vector<int> filiais= vector<int>(F);
  vector<Aresta> arestas=vector<Aresta>(C);

  for(int i=0; i< F; i++) { /* le do input quais sao as localidades que tem filiais */
    scanf("%d ", &fil);
    filiais[i]=fil;
  }
  for(int i=0; i<C; i++) { /* vai ler do input todas as ligacoes dos diversos vertices do grafo */
    int u, v, w;
      scanf("%d %d %d", &u, &v, &w); /* vai ler do input uma localidade(u) a respectiva localidade(v) ligada pela aresta com peso w */
      Aresta e = {u, v, w};
      g[u].push_back(e);
      arestas.push_back(e);
  }

/*  Johnson  */

    /* coloca a sorce do grafo (vertice 0) a distanciasancia 0 de todos os vertices */
    for (unsigned int  i = 1; i < g.size(); i++) {
      int j=i;
      Aresta e = {0, j, 0};
      g[0].push_back(e);
      arestas.push_back(e);
    }

    /* corremos o algoritmo Bellman-Ford para ter o caminho mais curto da source do grafo para todos os vertices */
    vector<int> valores_bellmanford = bellmanford(arestas, g, 0);


    /* repesagens dos arcos do grafo */
    for (unsigned int  i=1; i < g.size(); i++) {
      for (unsigned int  j=0; j < g[i].size(); j++) {
        g[i][j].custo = g[i][j].custo + valores_bellmanford[i] - valores_bellmanford[g[i][j].destino];
      }
    }


    /* com as repesagens dos arcos feitas agora conseguimos aplicar o algoritmo Dijkstra a todas as filiais do grafo */
    vector<int> caminhos_mais_curtos(g.size(), 0);
    vector<int> caminho_filial(g.size(), 0);

    for (unsigned int  i=0; i < filiais.size(); i++) {
      caminho_filial = dijkstra(g, filiais[i]);
      /*  repomos os pesos reais dos arcos para calcularmos o ponto de encontro */
      for(unsigned int k=1; k < g.size(); k++){
        if(caminhos_mais_curtos[k]!=INFINITO && caminho_filial[k]!=INFINITO){
          caminho_filial[k] += valores_bellmanford[k] - valores_bellmanford[filiais[i]];
          caminhos_mais_curtos[k] += caminho_filial[k];
        }
        else{ caminhos_mais_curtos[k]=INFINITO; }
      }

    }

    int local_encontro = -1, mais_curto = INFINITO;
    for (unsigned int i = 1; i < g.size(); i++) { /* vai ver qual e o ponto de encontro com caminho mais curto para as filiais */
        if (caminhos_mais_curtos[i]!=INFINITO && caminhos_mais_curtos[i] < mais_curto) {
          mais_curto = caminhos_mais_curtos[i];
          local_encontro = i;
        }
    }

    if(local_encontro==-1) { /* quando nao ha um ponto de encontro possivel (vertice isolado) */
      printf("N\n");
      return 0;

    } else { /* trata do output do custo das diferentes filiais para o local de encontro */
      cout  << local_encontro << " " << mais_curto << endl;

      for (unsigned int i=0; i < filiais.size(); i++) {
       caminho_filial = dijkstra(g, filiais[i]);
       caminho_filial[local_encontro] += valores_bellmanford[local_encontro] - valores_bellmanford[filiais[i]];
       printf("%d ", caminho_filial[local_encontro]);
      }

      cout << endl;
      return 0;
    }

}

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

vector<Aresta> grafo;
vector<int> filiais;
int N, C;

const int INFINITO = INT_MAX;

void criaGrafo(){

    int fil, F;

    /* le do input o numero de localidades(N), o numero de filiais(F) e o numero de ligacoes entre as localidades(C) */
    scanf("%d %d %d", &N, &F, &C);

    grafo = vector<Aresta>(C+1);
    filiais.resize(F);

    for(int i=0; i< F; i++) { /* le do input quais sao as localidades que tem filiais */
      scanf("%d ", &fil);
      filiais[i]=fil;
    }
    for(int i=0; i<C; i++) { /* vai ler do input todas as ligacoes dos diversos vertices do grafo */
      int u, v, w;
        scanf("%d %d %d", &u, &v, &w); /* vai ler do input uma localidade(u) a respectiva localidade(v) ligada pela aresta com peso w */
        Aresta e = {v, w};
        grafo.push_back(e);
    }

}


vector<int> bellmanford(int s) {

  /* Criamos duas listas para verificar os pesos das iteracoes actuais e anteriores*/
   vector<int> anteriores(N, INFINITO);
   vector<int> actuais(N, INFINITO);

   actuais[s]=0;
   anteriores[s]=0;
  for (int  t = 0; t < N; t++) {

        if (anteriores[t] < actuais[t]) {
          actuais[t] = anteriores[t];
        }

        for (int j=0; j < C ; j++) {
          if(anteriores[t]!=INFINITO && actuais[grafo[j].destino]!=INFINITO){
            if (anteriores[t] + grafo[j].custo < actuais[grafo[j].destino]) {
              /* calcula o caminho menor para o vertice desde a source */
              actuais[grafo[j].destino] = anteriores[t] + grafo[j].custo;
            }
          }

        }

      if(anteriores==actuais) { break; } /* o ponto de paragem do algoritmo Bellman-Ford */
      anteriores=actuais;
  }
  return actuais;

}

  // for (unsigned int  i = 1; i < memo.size(); i++) {
  //   // compute shortest paths from s to all vertices, with max hop-count i
  //   for (unsigned int  n = 0; n < g.size(); n++) {
  //     if (memo[i-1][n] < memo[i][n]) {
  //       memo[i][n] = memo[i-1][n];
  //     }
  //     for (unsigned int  j=0; j< g[n].size(); j++) {
  //       if (memo[i-1][n] != INFINITO) {
  //         if (memo[i-1][n] + g[n][j].cost < memo[i][g[n][j].head]) {
  //           memo[i][g[n][j].head] = memo[i-1][n] + g[n][j].cost;
  //         }
  //       }
  //     }
  //   }
  // }
  // return memo[g.size()];

int main() {

  criaGrafo();

  /* com as repesagens dos arcos feitas agora conseguimos aplicar o algoritmo Dijkstra a todas as filiais do grafo */
  vector<int> caminhos_mais_curtos(N, 0);
  vector<int> caminho_filial(N, 0);

  for (unsigned int  i=0; i < filiais.size(); i++) {
    caminho_filial = bellmanford(filiais[i]);;
    /*  repomos os pesos reais dos arcos para calcularmos o ponto de encontro */
    for(int k=1; k < N; k++){
      if(caminhos_mais_curtos[k]!=INFINITO && caminho_filial[k]!=INFINITO){
        caminhos_mais_curtos[k] += caminho_filial[k];
      }
      else{ caminhos_mais_curtos[k]=INFINITO; }
    }

  }

  int local_encontro = -1, mais_curto = INFINITO;
  for (int i = 1; i < N; i++) { /* vai ver qual e o ponto de encontro com caminho mais curto para as filiais */
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
     vector<int> distancias = bellmanford(filiais[i]);
     printf("%d ", distancias[local_encontro]);
    }

    cout << endl;
    return 0;
  }
}

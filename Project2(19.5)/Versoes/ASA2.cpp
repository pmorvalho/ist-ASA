#include <vector>
#include <string>
#include <stdio.h>
#include "iostream"
#include <set>
#include <climits>
#include <algorithm>

const int INF = INT_MAX;
using namespace std;



struct Aresta{

	int destino;
	int custo;
};

vector< vector<Aresta> > grafo;
vector <int> lista_filiais;



vector<int> bellmandford(int s) {

  /* Criamos duas listas para verificar os pesos das iteracoes actuais e anteriores*/
   vector<int> anteriores(grafo.size(), 0);
   vector<int> actuais(grafo.size(), 0);

  for (unsigned int  t = 1; t < actuais.size(); t++) {

      for (unsigned int  k = 0; k < grafo.size(); k++) {

          for (unsigned int  j=0; j< grafo[k].size(); j++) {
                  if (anteriores[k] + grafo[k][j].custo < actuais[grafo[k][j].destino]) {
                    /* calcula o caminho menor para o vertice desde a source */
                    actuais[grafo[k][j].destino] = anteriores[k] + grafo[k][j].custo;
                  }
          }
      }

      if(anteriores==actuais) { break; } /* o ponto de paragem do algoritmo Bellman-Ford */
      anteriores=actuais;
  }
  return actuais;

}



vector<int> dijkstra(vector< vector<Aresta> > grafo, int filial){

	set<pair<int, int> > fila;
  	fila.insert(pair<int, int> (0,filial));
  	vector <int> dist(grafo.size(),INF) ;

  while (!fila.empty()) {
    pair<int,int> p = *fila.begin();
    fila.erase(fila.begin());

    int d = p.first;
    int n = p.second;

    dist[n] = d;


  	for (unsigned int i = 0; i < grafo[n].size(); i++) {

      if (dist[n]+grafo[n][i].custo < dist[grafo[n][i].destino]) {

        if (dist[grafo[n][i].destino] != INF) {
          pair<int, int> pair2(dist[grafo[n][i].destino], grafo[n][i].destino);
          fila.erase(fila.find(pair2));
        }

        pair<int, int> pair3(dist[n]+grafo[n][i].custo, grafo[n][i].destino);
        fila.insert(pair3);
        dist[grafo[n][i].destino] = dist[n]+grafo[n][i].custo;
      }
   }
  }


  return dist;
}

int johnsson(){



	for(unsigned int i=1; i<grafo.size();i++){
		int b=i;
		Aresta a = {b, 0};
		grafo[0].push_back(a);
	}

  // bellmandford
    vector<int> lol = bellmandford(0);

  //repesagens
  for (unsigned int i = 1; i < grafo.size(); i++) {
    for (unsigned int n=0; n<grafo[i].size(); n++) {
      grafo[i][n].custo = grafo[i][n].custo + lol[i] - lol[grafo[i][n].destino];
    }
  }

  vector<int> caminhos(grafo.size(),0);
  vector<int> auxiliar(grafo.size(),0);

  //dijkstra
  for (unsigned int l = 0; l < lista_filiais.size(); l++) {
    caminhos = dijkstra(grafo, lista_filiais[l]);
    for(unsigned int c = 1; c < grafo.size();c++){
    	if (caminhos[c]!=INF && auxiliar[c]!=INF){
    		caminhos[c]+= lol[c] - lol[lista_filiais[l]];
    		auxiliar[c]+= caminhos[c];
    	}
    	else{
    		auxiliar[c]=INF;
    	}
    }
  }
  int j=-1;
  int d=INF;

  for(unsigned int i=1; i<auxiliar.size();i++){
  	if(auxiliar[i]!=INF && auxiliar[i] < d){
  		d=auxiliar[i];
  		j=i;
  	}
  }



  if (j==-1) printf("N\n");
  else{
  	  printf("%d %d\n", j, d);
  	for (unsigned int l=0; l<lista_filiais.size();l++){

  		caminhos = dijkstra(grafo,lista_filiais[l]);
  		caminhos[j]+=lol[j]-lol[lista_filiais[l]];
  		printf("%d ", caminhos[j]);
  	}
  	printf("\n");
  	}

  return 0;
}



int main(int argc, char *argv[]){





	int localidades, filiais, ligacoes;
	int i,x,y,z,cena;
	if(scanf("%d %d %d",&localidades, &filiais, &ligacoes)==-1) perror("Error");

	lista_filiais = vector<int>(filiais);

	for(i=0;i<filiais;i++){
		if(scanf("%d", &cena) ==-1) perror("Error");
		lista_filiais[i]=cena;
	}


	grafo = vector< vector <Aresta> >(localidades+1);
	for (i=0; i < ligacoes; i++){

		if(scanf("%d %d %d",&x, &y, &z)==-1) perror("Error");

		Aresta a = {y, z};
		grafo[x].push_back(a);
	}

	johnsson();


	return 0;

}

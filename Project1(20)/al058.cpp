//        Grupo  58
//  Pedro Orvalho    81151
//  Antonio Lourenco 81796

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>

int counter = 0, fundamentals = 0, lowest_bridge=-1, highest_bridge = -1;
//Da esquerda para a direita profundidade, pessoas essenciais a rede, o essencial com o indice mais pequeno e o essencial com o indice maior
std::vector<int> low; // vector de tempos mais baixos da arvore
std::vector<int> pre; // vector de tempos de descoberta dos diferentes vertices 
std::vector<bool> isFundamental; // vector para verificar se o vertice e essencial
std::vector< std::vector<int> > graph; 

void dfs(int u, int v) {  // algoritmo da DFS
    pre[v] = low[v] = counter++;
    int childcount = 0;
    for (unsigned int a = 0; a < graph[v].size() ; a++) {
	int w = graph[v][a];      
	  if (pre[w] == -1) {   // verifica se o vertice w ja foi visitado
	  	childcount ++;			
        dfs(v, w);        // chama a dfs para o vertice w, sendo o pai o vertice v
	    low[v] = (low[v]<low[w] ? low[v] : low[w]);
        
        if ((((low[w] >= pre[v]) && (u != -1)) || ((u == -1) && (childcount > 1))) && isFundamental[v]!=true){
   		// verifica se e a root da arvore, e se nao e verifica se o valor do low do filho e maior ou igual que o valor do pre do pai, verifica se ainda nao e uma articulacao
		isFundamental[v] = true;                                   // actualiza o vectores de vertices essenciais em como o vertice v e um vertice essencial
		fundamentals++;                                            // aumenta o numero de vertices essenciais 
		lowest_bridge = (lowest_bridge==-1 ? v : lowest_bridge);   // caso especial para o primeiro 
		lowest_bridge = (v<lowest_bridge ? v : lowest_bridge);     // verifca se e inferior ao actual inferior
		highest_bridge = (v>highest_bridge ? v : highest_bridge);  // verifica se e superior ao actual superior
      	}
      }
      else if (w != u) // verifica se o filho e o seu pai, caso dos nodes terminais
        low[v] = (low[v]<pre[w] ? low[v] : pre[w]);
    }
}

int main(int argc, char* argv[]){

	int e, v, e1, e2; 
	
	scanf ("%d %d",&v, &e);  // leitura do numero de vertices e numero de aresta

	low=std::vector<int>(v, -1);
	pre = std::vector<int>(v, -1);
	isFundamental = std::vector<bool>(v, false);
	graph = std::vector< std::vector<int> >(v);

	for(int a = 0; a<e; a++) { // adiciona as arestas aos respectivos vertices
		scanf ("%d %d",&e1, &e2);
		graph[e1-1].push_back(e2-1);
		graph[e2-1].push_back(e1-1);
	}

	dfs(-1, 0);  // DFS do grafo
	
	std::cout << fundamentals << std::endl;  // output do numero de vertices essenciais
	if(lowest_bridge != -1) { // caso existam vertices essenciais no grafo em estudo
	  std::cout << lowest_bridge+1 << " " << highest_bridge+1 <<std::endl;
	}
	else // caso nao haja pessoas essenciais
	  std::cout << lowest_bridge << " " << highest_bridge <<std::endl;
	return 0;
}

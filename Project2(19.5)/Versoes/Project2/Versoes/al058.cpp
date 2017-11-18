//        Grupo  58
//  Pedro Orvalho    81151
//  Antonio Lourenco 81796

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

class Path;
//Path::toString;

class Localidade;
//Localidade::addFilial;
//Localidade::addPath;
//Localidade::getId;

vector<Localidade> _localidades; 

class Localidade {
protected: 
	bool _filial;
	vector<Path*> _paths; 
public:
	Localidade() : _filial(false) {}
	void addFilial() {_filial = true;}
	void addPath(Path* path) {_paths.push_back(path);}
	bool getFilial() {return _filial;}
};

class Path {
protected:
	Localidade* _localidade;
	int _rcost;
	int _dcost;
public:
	Path(Localidade* localidade, int rcost, int dcost) : _localidade(localidade), _rcost(rcost), _dcost(dcost) {}
	void toString() {
		cout << "path to: " << _localidade << "  rcost: " << _rcost << "  dcost: " << _dcost << endl;
	}

};

int main(int argc, char* argv[]){

	int n, f, c; 
	//_localidades = vector<Localidade*>;

	scanf ("%d %d %d",&n, &f, &c);

	_localidades = vector<Localidade>(n);		

	for(int i=1; i <= f; i++) {
		scanf("%d", &n);
		_localidades[(n-1)].addFilial();
	}

	cout << _localidades[0].getFilial() << endl;
	cout << _localidades[1].getFilial() << endl;
	cout << _localidades[2].getFilial() << endl;



	return 0;
}

#include <iostream>
#include <vector>
using namespace std;

int capacidad;
int numero_pi;
int numero_su;
int numero_pl;
int numero_di;

struct Sector
{
	Sector()
	{
	}
};

struct Pista
{
	Pista()
	{
		vector<Sector> sectores(numero_pi);
	}
};

struct Superficie
{
	Superficie()
	{
		vector<Pista> pistas(numero_su);
	}
};

struct Plato
{
	Plato()
	{
		numero_pl = 2;
		vector<Superficie>superficies(numero_pl);
	}
};

struct Disk_Deque
{
	Disk_Deque()
	{
		vector<Plato>platos(numero_di);
	}
};

int main()
{
	cin >> numero_di >> numero_su >> numero_pi >> capacidad;
	Disk_Deque disco;
}
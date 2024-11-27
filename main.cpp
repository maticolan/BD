#include <iostream>
#include <vector>
using namespace std;

int capacidad;  // Capacidad global para todos los sectores
int numero_pi;
int numero_su = 2;
int numero_pl;
int numero_di;

struct Sector {
    int id;          // Identificador único del sector
    int capacidad;   // Capacidad del sector

    Sector(int id_, int capacidad_) : id(id_), capacidad(capacidad_) {}
};

struct Pista {
    vector<Sector> sectores;
    int id;  // Identificador único de la pista

    Pista(int id_) : id(id_) {
        for (int i = 0; i < numero_pi; i++) {
            sectores.emplace_back(i, capacidad);
        }
    }
};

struct Superficie {
    vector<Pista> pistas;
    int id;  // Identificador único de la superficie

    Superficie(int id_) : id(id_) {
        for (int i = 0; i < numero_su; i++) {
            pistas.emplace_back(i);
        }
    }
};

struct Plato {
    vector<Superficie> superficies;
    int id;  // Identificador único del plato

    Plato(int id_) : id(id_) {
        for (int i = 0; i < numero_pl; i++) {
            superficies.emplace_back(i);
        }
    }
};

struct Disk_Deque {
    vector<Plato> platos;

    Disk_Deque() {
        for (int i = 0; i < numero_di; i++) {
            platos.emplace_back(i);
        }
    }

    // Método para mostrar la estructura del disco
    void mostrar() const {
        for (int i = 0; i < platos.size(); i++) {
            cout << "Plato " << i + 1 << ":" << endl;
            for (int j = 0; j < platos[i].superficies.size(); j++) {
                cout << "  Superficie " << j + 1 << ":" << endl;
                for (int k = 0; k < platos[i].superficies[j].pistas.size(); k++) {
                    cout << "    Pista " << k + 1 << ":" << endl;
                    for (int l = 0; l < platos[i].superficies[j].pistas[k].sectores.size(); l++) {
                        cout << "      Sector " << l + 1
                            << " (Capacidad: " << platos[i].superficies[j].pistas[k].sectores[l].capacidad << ")" << endl;
                    }
                }
            }
        }
    }
};

int main() {
    cout << "numero de platos: ";
    cin >> numero_di;
    cout << "numero de pistas: ";
    cin >> numero_pl;
    cout << "numero de sectores: ";
    cin >> numero_pi;
    cout << "capacidad de sector: ";
    cin >> capacidad;
    Disk_Deque disco;
    disco.mostrar();
    return 0;
}

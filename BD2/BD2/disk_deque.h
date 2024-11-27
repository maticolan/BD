#ifndef DISK_DEQUE_H
#define DISK_DEQUE_H

#include <vector>
#include <string>

struct Sector {
    int id;
    int capacidad;

    Sector(int id_, int capacidad_) : id(id_), capacidad(capacidad_) {}
};

struct Pista {
    std::vector<Sector> sectores;
    int id;

    Pista(int id_, int numero_pi, int capacidad) : id(id_) {
        for (int i = 0; i < numero_pi; i++) {
            sectores.emplace_back(i, capacidad);
        }
    }
};

struct Superficie {
    std::vector<Pista> pistas;
    int id;

    Superficie(int id_, int numero_pi, int numero_su, int capacidad) : id(id_) {
        for (int i = 0; i < numero_su; i++) {
            pistas.emplace_back(i, numero_pi, capacidad);
        }
    }
};

struct Plato {
    std::vector<Superficie> superficies;
    int id;

    Plato(int id_, int numero_pi, int numero_pl, int numero_su, int capacidad) : id(id_) {
        for (int i = 0; i < numero_pl; i++) {
            superficies.emplace_back(i, numero_pi, numero_su, capacidad);
        }
    }
};

struct Disk_Deque {
    std::vector<Plato> platos;

    Disk_Deque(int numero_di, int numero_pi, int numero_pl, int numero_su, int capacidad) {
        for (int i = 0; i < numero_di; i++) {
            platos.emplace_back(i, numero_pi, numero_pl, numero_su, capacidad);
        }
    }

    std::string mostrar() const {
        std::string result;
        for (int i = 0; i < platos.size(); i++) {
            result += "Plato " + std::to_string(i + 1) + ":\n";
            for (int j = 0; j < platos[i].superficies.size(); j++) {
                result += "  Superficie " + std::to_string(j + 1) + ":\n";
                for (int k = 0; k < platos[i].superficies[j].pistas.size(); k++) {
                    result += "    Pista " + std::to_string(k + 1) + ":\n";
                    for (int l = 0; l < platos[i].superficies[j].pistas[k].sectores.size(); l++) {
                        result += "      Sector " + std::to_string(l + 1)
                            + " (Capacidad: " + std::to_string(platos[i].superficies[j].pistas[k].sectores[l].capacidad) + ")\n";
                    }
                }
            }
        }
        return result;
    }
};

#endif // DISK_DEQUE_H

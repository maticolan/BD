#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
using namespace std;

int capacidad;  // Capacidad global para todos los sectores
int numero_pi;
int numero_su = 2;
int numero_pl;
int numero_di;

struct Sector {
    int id;               // Identificador único del sector
    int capacidad;        // Capacidad del sector
    int espacio_usado = 0; // Espacio utilizado en el sector
    vector<string> almacenamiento;

    Sector(int id_, int capacidad_) : id(id_), capacidad(capacidad_) {}

    // Verifica si el sector tiene espacio suficiente
    bool tiene_espacio(int espacio_necesario) const {
        return (capacidad - espacio_usado) >= espacio_necesario;
    }

    // Almacena el dato si hay espacio suficiente
    bool almacenar(const string& dato, int espacio_necesario) {
        if (!tiene_espacio(espacio_necesario)) {
            return false;
        }
        almacenamiento.push_back(dato);
        espacio_usado += espacio_necesario;
        return true;
    }
};

struct Pista {
    vector<Sector> sectores;
    int id;

    Pista(int id_) : id(id_) {
        for (int i = 0; i < numero_pi; i++) {
            sectores.emplace_back(i, capacidad);
        }
    }
};

struct Superficie {
    vector<Pista> pistas;
    int id;

    Superficie(int id_) : id(id_) {
        for (int i = 0; i < numero_su; i++) {
            pistas.emplace_back(i);
        }
    }
};

struct Plato {
    vector<Superficie> superficies;
    int id;

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

    // Calcula el espacio necesario según el tipo de dato
    int calcular_espacio(const string& tipo, const string& dato) {
        if (tipo == "int") {
            return 4; // Enteros ocupan 4 unidades
        }
        else if (tipo == "varchar") {
            return 1 * dato.size(); // Cada carácter ocupa 3 unidades
        }
        else if (tipo == "decimal") {
            return 8; // Decimales ocupan 8 unidades
        }
        return 0; // Tipo desconocido
    }

    // Valida el dato según su tipo
    bool validar_dato(const string& tipo, const string& dato) {
        if (tipo == "int") {
            return regex_match(dato, regex("^-?\\d+$")); // Verifica que sea un número entero
        }
        else if (tipo == "decimal") {
            return regex_match(dato, regex("^-?\\d+\\.\\d+$")); // Verifica formato decimal
        }
        else if (tipo == "varchar") {
            return regex_search(dato, regex("[a-zA-Z]")); // Contiene al menos una letra
        }
        return false; // Tipo desconocido
    }

    // Almacena un dato en el primer sector disponible
    void almacenar_dato(const string& tipo, const string& dato) {
        if (!validar_dato(tipo, dato)) {
            cout << "Error: El dato '" << dato << "' no es válido para el tipo '" << tipo << "'." << endl;
            return;
        }

        int espacio_necesario = calcular_espacio(tipo, dato);

        for (auto& plato : platos) {
            for (auto& superficie : plato.superficies) {
                for (auto& pista : superficie.pistas) {
                    for (auto& sector : pista.sectores) {
                        if (sector.almacenar(dato, espacio_necesario)) {
                            cout << "Dato almacenado: " << dato << " en Sector "
                                << sector.id << ", Pista " << pista.id
                                << ", Superficie " << superficie.id
                                << ", Plato " << plato.id << endl;
                            return;
                        }
                    }
                }
            }
        }
        cout << "Error: No hay espacio suficiente para almacenar el dato." << endl;
    }

    // Muestra la estructura completa del disco
    void mostrar() const {
        for (int i = 0; i < platos.size(); i++) {
            cout << "Plato " << i + 1 << ":" << endl;
            for (int j = 0; j < platos[i].superficies.size(); j++) {
                cout << "  Superficie " << j + 1 << ":" << endl;
                for (int k = 0; k < platos[i].superficies[j].pistas.size(); k++) {
                    cout << "    Pista " << k + 1 << ":" << endl;
                    for (int l = 0; l < platos[i].superficies[j].pistas[k].sectores.size(); l++) {
                        cout << "      Sector " << l + 1
                            << " (Usado: " << platos[i].superficies[j].pistas[k].sectores[l].espacio_usado
                            << "/" << platos[i].superficies[j].pistas[k].sectores[l].capacidad << "): ";
                        if (platos[i].superficies[j].pistas[k].sectores[l].almacenamiento.empty()) {
                            cout << "Vacío";
                        }
                        else {
                            for (const auto& dato : platos[i].superficies[j].pistas[k].sectores[l].almacenamiento) {
                                cout << dato << " ";
                            }
                        }
                        cout << endl;
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

    int opcion;
    do {
        cout << "\nOpciones:\n";
        cout << "1. Mostrar estructura del disco\n";
        cout << "2. Almacenar un dato\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            disco.mostrar();
            break;
        case 2: {
            string tipo, dato;
            cout << "Ingrese el tipo de dato (int, varchar, decimal): ";
            cin >> tipo;
            cout << "Ingrese el dato: ";
            cin.ignore();  // Limpiar buffer
            getline(cin, dato);
            disco.almacenar_dato(tipo, dato);
            break;
        }
        case 3:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != 3);

    return 0;
}

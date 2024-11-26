class Sector:
    def __init__(self, id, capacidad):
        self.id = id  # Identificador único del sector
        self.capacidad = capacidad  # Capacidad en bytes del sector

    def __str__(self):
        return f"Sector {self.id} (Capacidad: {self.capacidad} bytes)"


class Pista:
    def __init__(self, id, num_sectores, capacidad_sector):
        self.id = id  # Identificador único de la pista
        self.sectores = [Sector(i, capacidad_sector) for i in range(num_sectores)]

    def __str__(self):
        return f"Pista {self.id} con {len(self.sectores)} sectores"


class Superficie:
    def __init__(self, id, num_pistas, num_sectores, capacidad_sector):
        self.id = id  # Identificador único de la superficie
        self.pistas = [
            Pista(i, num_sectores, capacidad_sector) for i in range(num_pistas)
        ]

    def __str__(self):
        return f"Superficie {self.id} con {len(self.pistas)} pistas"


class Plato:
    def __init__(self, id, num_superficies, num_pistas, num_sectores, capacidad_sector):
        self.id = id  # Identificador único del plato
        self.superficies = [
            Superficie(i, num_pistas, num_sectores, capacidad_sector)
            for i in range(num_superficies)
        ]

    def __str__(self):
        return f"Plato {self.id} con {len(self.superficies)} superficies"


class Disco:
    def __init__(self, num_platos, num_superficies, num_pistas, num_sectores, capacidad_sector):
        self.platos = [
            Plato(i, num_superficies, num_pistas, num_sectores, capacidad_sector)
            for i in range(num_platos)
        ]

    def mostrar(self):
        for plato in self.platos:
            print(f"Plato {plato.id}:")
            for superficie in plato.superficies:
                print(f"  Superficie {superficie.id}:")
                for pista in superficie.pistas:
                    print(f"    Pista {pista.id}:")
                    for sector in pista.sectores:
                        print(f"      {sector}")


# Configuración del disco
NUM_PLATOS = 2
NUM_SUPERFICIES = 2
NUM_PISTAS = 3
NUM_SECTORES = 4
CAPACIDAD_SECTOR = 512  # Capacidad de cada sector en bytes

# Crear y mostrar el disco
disco = Disco(NUM_PLATOS, NUM_SUPERFICIES, NUM_PISTAS, NUM_SECTORES, CAPACIDAD_SECTOR)
disco.mostrar()
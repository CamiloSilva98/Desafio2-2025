#ifndef CANCION_H
#define CANCION_H
#include <string>
#include "Arreglo.h"
#include "Credito.h"

    using namespace std;

class Cancion {
private:
    int id;  // 9 dígitos: 5 del artista + 2 del álbum + 2 de la canción
    string nombre;
    int duracion;  // En segundos
    string ruta128;  // Ruta archivo 128 kbps
    string ruta320;  // Ruta archivo 320 kbps
    ArregloDinamico<Credito*> creditos;
    int reproducciones;

public:
    // Constructor por defecto
    Cancion();

    // Constructor parametrizado
    Cancion(int id, string nombre, int duracion, string ruta128, string ruta320);

    // Constructor de copia
    Cancion(const Cancion& otra);

    // Destructor
    ~Cancion();

    // Sobrecarga de operadores
    bool operator==(const Cancion& otra) const;
    bool operator<(const Cancion& otra) const;
    Cancion& operator=(const Cancion& otra);

    // Métodos de créditos
    void agregarCredito(Credito* credito);
    Credito* obtenerCredito(int indice) const;
    int getCantidadCreditos() const;

    // Sobrecarga de método obtenerRuta
    string obtenerRuta() const;  // Retorna ruta por defecto (128)
    string obtenerRuta(int calidad) const;  // 128 o 320
    string obtenerRuta(bool esPremium) const;  // true=320, false=128

    // Métodos de reproducción
    void incrementarReproducciones();

    // Getters
    int getId() const;
    string getNombre() const;
    int getDuracion() const;
    string getRuta128() const;
    string getRuta320() const;
    int getReproducciones() const;

    // Setters con validación
    void setId(int id);
    void setNombre(string nombre);
    void setDuracion(int duracion);
    void setRuta128(string ruta);
    void setRuta320(string ruta);
};

#endif // CANCION_H

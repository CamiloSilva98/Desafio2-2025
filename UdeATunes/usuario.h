#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Arreglo.h"
#include "Cancion.h"
#include "ListaFavoritos.h"
#include "Fecha.h"

using namespace std;

class Usuario {
private:
    string nickname;  // Único
    string tipoMembresia;  // "estandar" o "premium"
    string ciudad;
    string pais;
    Fecha fechaInscripcion;
    ListaFavoritos* listaFavoritos;  // Solo para premium (puede ser nullptr)
    ArregloDinamico<Cancion*> historicoReproduccion;  // Últimas K canciones
    const int MAX_HISTORICO = 6;  // Según preinforme

public:
    // Constructor por defecto
    Usuario();

    // Constructor parametrizado
    Usuario(string nickname, string tipoMembresia, string ciudad, string pais, Fecha fechaInscripcion);

    // Constructor de copia
    Usuario(const Usuario& otro);

    // Destructor
    ~Usuario();

    // Sobrecarga de operadores
    bool operator==(const Usuario& otro) const;
    bool operator<(const Usuario& otro) const;
    Usuario& operator=(const Usuario& otro);

    // Métodos de historial
    void agregarAlHistorico(Cancion* cancion);
    Cancion* obtenerDelHistorico(int indice) const;
    int getCantidadHistorico() const;

    // Métodos de lista de favoritos
    void crearListaFavoritos();  // Solo para premium
    bool tieneListaFavoritos() const;
    ListaFavoritos* getListaFavoritos() const;

    // Métodos de verificación
    bool esPremium() const;
    bool esEstandar() const;

    // Getters
    string getNickname() const;
    string getTipoMembresia() const;
    string getCiudad() const;
    string getPais() const;
    Fecha getFechaInscripcion() const;

    // Setters con validación
    void setNickname(string nickname);
    void setTipoMembresia(string tipo);
    void setCiudad(string ciudad);
    void setPais(string pais);
    void setFechaInscripcion(Fecha fecha);
};

#endif // USUARIO_H

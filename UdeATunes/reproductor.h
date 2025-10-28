#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H

#include <string>
#include <random>
#include <chrono>
#include <thread>
#include "Arreglo.h"
#include "Cancion.h"
#include "Usuario.h"
#include "Artista.h"
#include "Album.h"
#include "Publicidad.h"

using namespace std;

class Reproductor {
private:
    ArregloDinamico<Cancion*> todasLasCanciones;
    ArregloDinamico<Album*> albumesPorCancion;
    ArregloDinamico<Cancion*> colaReproduccion;
    ArregloDinamico<Publicidad*>* publicidades;
    Usuario* usuarioActual;

    int indiceActual;
    bool reproduciendo;
    bool modoRepetir;
    int cancionesReproducidas;
    int indicePublicidadActual;
    //int ultimaPublicidadMostrada;

    mutable mt19937 generadorAleatorio;

    const int MAX_RETROCESO_ESTANDAR = 0;
    const int MAX_RETROCESO_PREMIUM = 4;
    const int MAX_RETROCESO_FAVORITOS = 6;
    const int INTERVALO_PUBLICIDAD = 2;
    const int DURACION_CANCION_SEGUNDOS = 3;
    const int CANTIDAD_CANCIONES_TEST = 5;

    int obtenerMaxRetroceso() const;
    bool puedeRetroceder() const;
    bool puedeAvanzar() const;
    void mostrarPublicidad();
    Publicidad* seleccionarPublicidadAleatoria();
    int generarIndiceAleatorio(int max) const;
    Album* obtenerAlbumDeCancion(Cancion* cancion) const;

public:
    Reproductor(Usuario* usuario);
    Reproductor(Usuario* usuario, ArregloDinamico<Publicidad*>* pubs);
    ~Reproductor();

    void cargarCanciones(ArregloDinamico<Artista*>& artistas);
    void reproduccionAleatoriaTemporizador();
    void iniciarReproduccionManual();
    void detenerReproduccion();
    void siguiente();
    void anterior();
    void toggleRepetir();
    void reproducirFavoritos(bool modoAleatorio);
    void reproducirLista(ArregloDinamico<Cancion*>& lista, bool modoAleatorio);

    Cancion* obtenerCancionActual() const;
    bool estaReproduciendo() const;
    bool estaModoRepetir() const;
    int getCantidadCanciones() const;
    int getIndiceActual() const;
    int getCancionesReproducidas() const;

    void mostrarCancionActual() const;
};

#endif

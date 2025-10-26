#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H

#include <string>
#include <cstdlib>
#include <ctime>
#include "Arreglo.h"
#include "Cancion.h"
#include "Usuario.h"
#include "Artista.h"
#include "Album.h"

using namespace std;

/**
 * Clase Reproductor
 * Maneja toda la lógica de reproducción de canciones según el tipo de usuario
 *
 * FUNCIONALIDAD III - REPRODUCCIÓN ALEATORIA CON TEMPORIZADOR:
 * - Reproduce 5 canciones aleatorias de TODA la plataforma
 * - Cada canción dura 3 segundos automáticamente
 * - NO se puede pausar/detener mientras el temporizador está activo
 * - Muestra publicidad cada 2 canciones (usuarios estándar)
 * - Termina automáticamente después de 5 canciones
 *
 * CONTROLES MANUALES (solo fuera del temporizador):
 * - siguiente, anterior, repetir (según tipo de usuario)
 */
class Reproductor {
private:
    // Arreglo con TODAS las canciones de la plataforma (referencias)
    ArregloDinamico<Cancion*> todasLasCanciones;

    // Mapa auxiliar para obtener el álbum de cada canción
    ArregloDinamico<Album*> albumesPorCancion;

    // Cola de reproducción actual
    ArregloDinamico<Cancion*> colaReproduccion;

    // Usuario actual
    Usuario* usuarioActual;

    // Estados de reproducción
    int indiceActual;           // Índice en la cola de reproducción
    bool reproduciendo;         // Estado: reproduciendo o detenido
    bool modoRepetir;          // Modo repetir canción actual
    int cancionesReproducidas; // Contador para publicidad (cada 2 canciones)

    // Constantes
    const int MAX_RETROCESO_ESTANDAR = 0;  // Usuario estándar NO puede retroceder
    const int MAX_RETROCESO_PREMIUM = 4;   // Premium puede retroceder 4 canciones
    const int MAX_RETROCESO_FAVORITOS = 6; // En favoritos puede retroceder 6
    const int INTERVALO_PUBLICIDAD = 2;    // Publicidad cada 2 canciones
    const int DURACION_CANCION_SEGUNDOS = 3;  // Temporizador: 3 segundos por canción
    const int CANTIDAD_CANCIONES_TEST = 5;    // Reproducir 5 canciones en modo test

    // Métodos privados auxiliares
    int obtenerMaxRetroceso() const;
    bool puedeRetroceder() const;
    bool puedeAvanzar() const;
    void mostrarPublicidad();
    int generarIndiceAleatorio(int max) const;
    Album* obtenerAlbumDeCancion(Cancion* cancion) const;

public:
    // Constructor
    Reproductor(Usuario* usuario);

    // Destructor
    ~Reproductor();

    // Cargar todas las canciones desde los artistas
    void cargarCanciones(ArregloDinamico<Artista*>& artistas);

    // ====== FUNCIONALIDAD III: REPRODUCCIÓN ALEATORIA CON TEMPORIZADOR ======
    // Esta función se ejecuta automáticamente por 5 canciones de 3 segundos cada una
    void reproduccionAleatoriaTemporizador();

    // ====== CONTROLES MANUALES (solo fuera del temporizador) ======
    void iniciarReproduccionManual();  // Inicia reproducción manual (sin temporizador)
    void detenerReproduccion();        // Detiene la reproducción

    // ====== CONTROLES DE NAVEGACIÓN ======
    void siguiente();                  // Avanzar a la siguiente canción
    void anterior();                   // Retroceder a la anterior (solo premium)
    void toggleRepetir();              // Activar/desactivar modo repetir (solo premium)

    // ====== FUNCIONALIDAD IV: REPRODUCIR LISTA DE FAVORITOS ======
    void reproducirFavoritos(bool modoAleatorio);

    // ====== REPRODUCIR LISTA ESPECÍFICA ======
    void reproducirLista(ArregloDinamico<Cancion*>& lista, bool modoAleatorio);

    // ====== MÉTODOS DE CONSULTA ======
    Cancion* obtenerCancionActual() const;
    bool estaReproduciendo() const;
    bool estaModoRepetir() const;
    int getCantidadCanciones() const;
    int getIndiceActual() const;
    int getCancionesReproducidas() const;

    // ====== MÉTODO AUXILIAR PARA MOSTRAR REPRODUCCIÓN ======
    void mostrarCancionActual() const;
};

#endif // REPRODUCTOR_H

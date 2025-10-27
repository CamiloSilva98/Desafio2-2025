#include "Reproductor.h"
#include "Medidor.h"
#include <iostream>

using namespace std;

// Constructor
Reproductor::Reproductor(Usuario* usuario)
    : generadorAleatorio(chrono::steady_clock::now().time_since_epoch().count())
{
    this->usuarioActual = usuario;
    this->indiceActual = -1;
    this->reproduciendo = false;
    this->modoRepetir = false;
    this->cancionesReproducidas = 0;

    Medidor::sumarMemoria(sizeof(Reproductor));
}

// Destructor
Reproductor::~Reproductor() {
    Medidor::restarMemoria(sizeof(Reproductor));
}

// Cargar canciones
void Reproductor::cargarCanciones(ArregloDinamico<Artista*>& artistas) {
    todasLasCanciones.limpiar();
    albumesPorCancion.limpiar();

    cout << "[Reproductor] Cargando canciones de la plataforma..." << endl;

    for (int i = 0; i < artistas.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Artista* artista = artistas.obtener(i);

        for (int j = 0; j < artista->getCantidadAlbumes(); j++) {
            Medidor::incrementarIteraciones();
            Album* album = artista->obtenerAlbum(j);

            for (int k = 0; k < album->getCantidadCanciones(); k++) {
                Medidor::incrementarIteraciones();
                Cancion* cancion = album->obtenerCancion(k);
                todasLasCanciones.agregar(cancion);
                albumesPorCancion.agregar(album);
            }
        }
    }

    cout << "[Reproductor] ✓ Cargadas " << todasLasCanciones.getCantidad()
         << " canciones en total de " << artistas.getCantidad() << " artistas." << endl;
}

// Obtener máximo retroceso
int Reproductor::obtenerMaxRetroceso() const {
    if (usuarioActual->esPremium()) {
        return MAX_RETROCESO_PREMIUM;
    }
    return MAX_RETROCESO_ESTANDAR;
}

// Puede retroceder
bool Reproductor::puedeRetroceder() const {
    int maxRetroceso = obtenerMaxRetroceso();
    return (indiceActual > 0 && indiceActual <= maxRetroceso);
}

// Puede avanzar
bool Reproductor::puedeAvanzar() const {
    return (indiceActual < colaReproduccion.getCantidad() - 1);
}

// Obtener álbum de canción
Album* Reproductor::obtenerAlbumDeCancion(Cancion* cancion) const {
    for (int i = 0; i < todasLasCanciones.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        if (todasLasCanciones.obtener(i) == cancion) {
            return albumesPorCancion.obtener(i);
        }
    }
    return nullptr;
}

// Mostrar publicidad
void Reproductor::mostrarPublicidad() {
    cout << "\n╔═════════════════════════════════════════════════════════╗" << endl;
    cout << "║                     PUBLICIDAD                      ║" << endl;
    cout << "╠═════════════════════════════════════════════════════════╣" << endl;
    cout << "║  ¡Actualiza a Premium por solo $19.900/mes!             ║" << endl;
    cout << "║  * Sin anuncios                                          ║" << endl;
    cout << "║  * Audio de alta calidad (320 kbps)                     ║" << endl;
    cout << "║  * Listas de favoritos ilimitadas (hasta 10,000)        ║" << endl;
    cout << "║  * Retroceder hasta 4 canciones                         ║" << endl;
    cout << "╚═════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
}

// Generar índice aleatorio (C++)
int Reproductor::generarIndiceAleatorio(int max) const {
    if (max <= 0) return 0;
    uniform_int_distribution<int> distribucion(0, max - 1);
    return distribucion(const_cast<mt19937&>(generadorAleatorio));
}

// REPRODUCCIÓN ALEATORIA CON TEMPORIZADOR
void Reproductor::reproduccionAleatoriaTemporizador() {
    if (todasLasCanciones.getCantidad() == 0) {
        cout << "\n[Error] No hay canciones cargadas en el sistema." << endl;
        return;
    }

    cout << "\n╔═════════════════════════════════════════════════════════╗" << endl;
    cout << "║       REPRODUCCIÓN ALEATORIA - MODO AUTOMÁTICO          ║" << endl;
    cout << "╠═════════════════════════════════════════════════════════╣" << endl;
    cout << "║  Se reproducirán 5 canciones aleatorias                 ║" << endl;
    cout << "║  Cada canción durará 3 segundos automáticamente         ║" << endl;
    cout << "║  Usuario: " << usuarioActual->getNickname() << " (" << usuarioActual->getTipoMembresia() << ")" << endl;
    cout << "╚═════════════════════════════════════════════════════════╝" << endl;

    cancionesReproducidas = 0;
    colaReproduccion.limpiar();

    for (int i = 0; i < CANTIDAD_CANCIONES_TEST; i++) {
        Medidor::incrementarIteraciones();
        int indiceAleatorio = generarIndiceAleatorio(todasLasCanciones.getCantidad());
        Cancion* cancion = todasLasCanciones.obtener(indiceAleatorio);
        colaReproduccion.agregar(cancion);
    }

    cout << "\n[Iniciando reproducción automática...]\n" << endl;

    for (int i = 0; i < CANTIDAD_CANCIONES_TEST; i++) {
        Medidor::incrementarIteraciones();

        indiceActual = i;
        Cancion* cancionActual = colaReproduccion.obtener(i);

        cancionActual->incrementarReproducciones();
        cancionesReproducidas++;
        usuarioActual->agregarAlHistorico(cancionActual);

        Album* album = obtenerAlbumDeCancion(cancionActual);

        string rutaAudio;
        string calidadTexto;
        if (usuarioActual->esPremium()) {
            rutaAudio = cancionActual->getRuta320();
            calidadTexto = "320 kbps (Premium)";
        } else {
            rutaAudio = cancionActual->getRuta128();
            calidadTexto = "128 kbps (Estándar)";
        }

        cout << "\n┌──────────────────────────────────────────────────────┐" << endl;
        cout << "│  CANCIÓN " << (i+1) << "/5 - REPRODUCIENDO AHORA" << endl;
        cout << "├──────────────────────────────────────────────────────┤" << endl;
        cout << "│ Título: " << cancionActual->getNombre() << endl;
        cout << "│ ID: " << cancionActual->getId() << endl;
        cout << "│ Duración: " << cancionActual->getDuracion() << " segundos" << endl;
        cout << "│ Calidad: " << calidadTexto << endl;

        if (album != nullptr) {
            cout << "├──────────────────────────────────────────────────────┤" << endl;
            cout << "│ Álbum: " << album->getNombre() << endl;
            cout << "│ Fecha: " << album->getFechaLanzamiento().getDia() << "/"
                 << album->getFechaLanzamiento().getMes() << "/"
                 << album->getFechaLanzamiento().getAño() << endl;
            cout << "│ Sello: " << album->getSelloDisco() << endl;
        }

        cout << "├──────────────────────────────────────────────────────┤" << endl;
        cout << "│  RUTA DEL ARCHIVO DE AUDIO:" << endl;
        cout << "│ " << rutaAudio << endl;
        cout << "├──────────────────────────────────────────────────────┤" << endl;
        cout << "│   RUTA DE LA PORTADA DEL ÁLBUM:" << endl;

        if (album != nullptr) {
            cout << "│ " << album->getRutaPortada() << endl;
        } else {
            cout << "│ [Portada no disponible]" << endl;
        }

        cout << "└──────────────────────────────────────────────────────┘" << endl;

        if (usuarioActual->esEstandar() &&
            cancionesReproducidas % INTERVALO_PUBLICIDAD == 0) {
            mostrarPublicidad();
        }

        cout << "\n[⏱  Reproduciendo... ";
        cout.flush();

        for (int seg = 1; seg <= DURACION_CANCION_SEGUNDOS; seg++) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << seg << "... ";
            cout.flush();
        }

        cout << "✓]\n" << endl;
    }

    cout << "\n╔═════════════════════════════════════════════════════════╗" << endl;
    cout << "║       REPRODUCCIÓN AUTOMÁTICA FINALIZADA                ║" << endl;
    cout << "╠═════════════════════════════════════════════════════════╣" << endl;
    cout << "║  Total reproducido: " << CANTIDAD_CANCIONES_TEST << " canciones" << endl;
    cout << "║  Usuario: " << usuarioActual->getNickname() << endl;
    cout << "╚═════════════════════════════════════════════════════════╝" << endl;

    reproduciendo = false;
    indiceActual = -1;
}

// Iniciar reproducción manual
void Reproductor::iniciarReproduccionManual() {
    if (todasLasCanciones.getCantidad() == 0) {
        cout << "[Error] No hay canciones cargadas en el sistema." << endl;
        return;
    }

    colaReproduccion.limpiar();
    ArregloDinamico<int> indices;

    for (int i = 0; i < todasLasCanciones.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        indices.agregar(i);
    }

    for (int i = indices.getCantidad() - 1; i > 0; i--) {
        Medidor::incrementarIteraciones();
        int j = generarIndiceAleatorio(i + 1);
        int temp = indices.obtener(i);
        indices.modificar(i, indices.obtener(j));
        indices.modificar(j, temp);
    }

    for (int i = 0; i < indices.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        int idx = indices.obtener(i);
        colaReproduccion.agregar(todasLasCanciones.obtener(idx));
    }

    indiceActual = 0;
    reproduciendo = true;
    modoRepetir = false;
    cancionesReproducidas = 0;

    cout << "\n[Reproductor] Reproducción manual iniciada." << endl;
    cout << "Total de canciones en cola: " << colaReproduccion.getCantidad() << endl;

    mostrarCancionActual();
}

// Detener reproducción
void Reproductor::detenerReproduccion() {
    if (!reproduciendo) {
        cout << "[Info] La reproducción ya está detenida." << endl;
        return;
    }

    reproduciendo = false;
    modoRepetir = false;

    cout << "\n[Reproductor] Reproducción detenida." << endl;
}

// Siguiente
void Reproductor::siguiente() {
    if (!reproduciendo) {
        cout << "[Error] No hay reproducción activa. Usa 'Iniciar reproducción manual' primero." << endl;
        return;
    }

    if (modoRepetir) {
        cout << "[Info] Modo repetir activado. Desactívalo para avanzar." << endl;
        return;
    }

    if (!puedeAvanzar()) {
        cout << "[Info] No hay más canciones en la cola." << endl;
        detenerReproduccion();
        return;
    }

    indiceActual++;
    cancionesReproducidas++;

    Cancion* cancion = colaReproduccion.obtener(indiceActual);
    cancion->incrementarReproducciones();
    usuarioActual->agregarAlHistorico(cancion);

    if (usuarioActual->esEstandar() &&
        cancionesReproducidas % INTERVALO_PUBLICIDAD == 0) {
        mostrarPublicidad();
    }

    mostrarCancionActual();
}

// Anterior
void Reproductor::anterior() {
    if (!reproduciendo) {
        cout << "[Error] No hay reproducción activa." << endl;
        return;
    }

    if (usuarioActual->esEstandar()) {
        cout << "[Error] Usuarios estándar no pueden retroceder. ¡Actualiza a Premium!" << endl;
        return;
    }

    if (indiceActual <= 0) {
        cout << "[Info] No hay canción anterior." << endl;
        return;
    }

    if (indiceActual > obtenerMaxRetroceso()) {
        cout << "[Info] Ya retrocediste el máximo permitido ("
             << obtenerMaxRetroceso() << " canciones)." << endl;
        return;
    }

    indiceActual--;
    mostrarCancionActual();
}

// Toggle repetir
void Reproductor::toggleRepetir() {
    if (!reproduciendo) {
        cout << "[Error] No hay reproducción activa." << endl;
        return;
    }

    if (usuarioActual->esEstandar()) {
        cout << "[Error] Usuarios estándar no tienen modo repetir. ¡Actualiza a Premium!" << endl;
        return;
    }

    modoRepetir = !modoRepetir;

    if (modoRepetir) {
        cout << "\n[Reproductor]  Modo REPETIR activado" << endl;
    } else {
        cout << "\n[Reproductor]  Modo REPETIR desactivado" << endl;
    }
}

// Reproducir favoritos
void Reproductor::reproducirFavoritos(bool modoAleatorio) {
    if (!usuarioActual->esPremium()) {
        cout << "[Error] Solo usuarios premium pueden reproducir favoritos." << endl;
        return;
    }

    ListaFavoritos* lista = usuarioActual->getListaFavoritos();

    if (lista == nullptr || lista->estaVacia()) {
        cout << "[Error] No tienes canciones en favoritos." << endl;
        return;
    }

    colaReproduccion.limpiar();

    if (modoAleatorio) {
        ArregloDinamico<int> indices;

        for (int i = 0; i < lista->getCantidad(); i++) {
            Medidor::incrementarIteraciones();
            indices.agregar(i);
        }

        for (int i = indices.getCantidad() - 1; i > 0; i--) {
            Medidor::incrementarIteraciones();
            int j = generarIndiceAleatorio(i + 1);
            int temp = indices.obtener(i);
            indices.modificar(i, indices.obtener(j));
            indices.modificar(j, temp);
        }

        for (int i = 0; i < indices.getCantidad(); i++) {
            Medidor::incrementarIteraciones();
            int idx = indices.obtener(i);
            colaReproduccion.agregar(lista->obtenerCancion(idx));
        }

        cout << "\n[Reproductor] Reproduciendo favoritos en modo ALEATORIO" << endl;

    } else {
        for (int i = 0; i < lista->getCantidad(); i++) {
            Medidor::incrementarIteraciones();
            colaReproduccion.agregar(lista->obtenerCancion(i));
        }

        cout << "\n[Reproductor] Reproduciendo favoritos en orden ORIGINAL" << endl;
    }

    indiceActual = 0;
    reproduciendo = true;
    modoRepetir = false;
    cancionesReproducidas = 0;

    cout << "Total de canciones: " << colaReproduccion.getCantidad() << endl;

    mostrarCancionActual();
}

// Reproducir lista
void Reproductor::reproducirLista(ArregloDinamico<Cancion*>& lista, bool modoAleatorio) {
    if (lista.getCantidad() == 0) {
        cout << "[Error] La lista está vacía." << endl;
        return;
    }

    colaReproduccion.limpiar();

    if (modoAleatorio) {
        ArregloDinamico<int> indices;

        for (int i = 0; i < lista.getCantidad(); i++) {
            Medidor::incrementarIteraciones();
            indices.agregar(i);
        }

        for (int i = indices.getCantidad() - 1; i > 0; i--) {
            Medidor::incrementarIteraciones();
            int j = generarIndiceAleatorio(i + 1);
            int temp = indices.obtener(i);
            indices.modificar(i, indices.obtener(j));
            indices.modificar(j, temp);
        }

        for (int i = 0; i < indices.getCantidad(); i++) {
            Medidor::incrementarIteraciones();
            int idx = indices.obtener(i);
            colaReproduccion.agregar(lista.obtener(idx));
        }

    } else {
        for (int i = 0; i < lista.getCantidad(); i++) {
            Medidor::incrementarIteraciones();
            colaReproduccion.agregar(lista.obtener(i));
        }
    }

    indiceActual = 0;
    reproduciendo = true;
    modoRepetir = false;
    cancionesReproducidas = 0;

    cout << "\n[Reproductor] Lista cargada con " << colaReproduccion.getCantidad()
         << " canciones." << endl;

    mostrarCancionActual();
}

// Obtener canción actual
Cancion* Reproductor::obtenerCancionActual() const {
    if (indiceActual >= 0 && indiceActual < colaReproduccion.getCantidad()) {
        return colaReproduccion.obtener(indiceActual);
    }
    return nullptr;
}

bool Reproductor::estaReproduciendo() const {
    return reproduciendo;
}

bool Reproductor::estaModoRepetir() const {
    return modoRepetir;
}

int Reproductor::getCantidadCanciones() const {
    return colaReproduccion.getCantidad();
}

int Reproductor::getIndiceActual() const {
    return indiceActual;
}

int Reproductor::getCancionesReproducidas() const {
    return cancionesReproducidas;
}

// Mostrar canción actual
void Reproductor::mostrarCancionActual() const {
    Cancion* cancion = obtenerCancionActual();

    if (cancion == nullptr) {
        cout << "[Info] No hay canción en reproducción." << endl;
        return;
    }

    Album* album = obtenerAlbumDeCancion(cancion);

    string rutaAudio;
    if (usuarioActual->esPremium()) {
        rutaAudio = cancion->getRuta320();
    } else {
        rutaAudio = cancion->getRuta128();
    }

    cout << "\n┌──────────────────────────────────────────────────────┐" << endl;
    cout << "│ 🎵 REPRODUCIENDO AHORA                               │" << endl;
    cout << "├──────────────────────────────────────────────────────┤" << endl;
    cout << "│ Canción: " << cancion->getNombre() << endl;
    cout << "│ ID: " << cancion->getId() << endl;
    cout << "│ Duración: " << cancion->getDuracion() << " segundos" << endl;
    cout << "│ Calidad: " << (usuarioActual->esPremium() ? "320 kbps (Premium)" : "128 kbps (Estándar)") << endl;

    if (album != nullptr) {
        cout << "├──────────────────────────────────────────────────────┤" << endl;
        cout << "│ Álbum: " << album->getNombre() << endl;
    }

    cout << "├──────────────────────────────────────────────────────┤" << endl;
    cout << "│  Ruta de audio:" << endl;
    cout << "│ " << rutaAudio << endl;

    if (album != nullptr) {
        cout << "├──────────────────────────────────────────────────────┤" << endl;
        cout << "│   Portada del álbum:" << endl;
        cout << "│ " << album->getRutaPortada() << endl;
    }

    cout << "├──────────────────────────────────────────────────────┤" << endl;
    cout << "│ Posición: " << (indiceActual + 1) << "/" << colaReproduccion.getCantidad() << endl;

    if (modoRepetir) {
        cout << "│ Estado: MODO REPETIR ACTIVADO" << endl;
    }

    cout << "└──────────────────────────────────────────────────────┘" << endl;
}

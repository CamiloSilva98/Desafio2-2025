#include "GestorDatos.h"
#include "Medidor.h"
#include <sstream>
#include <iostream>

using namespace std;

// Constructor
GestorDatos::GestorDatos() {
    Medidor::sumarMemoria(sizeof(GestorDatos));
}

// Destructor
GestorDatos::~GestorDatos() {
    // Liberar usuarios
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        delete usuarios.obtener(i);
    }

    // Liberar artistas (también liberan álbumes y canciones)
    for (int i = 0; i < artistas.getCantidad(); i++) {
        delete artistas.obtener(i);
    }

    // Liberar publicidades
    for (int i = 0; i < publicidades.getCantidad(); i++) {
        delete publicidades.obtener(i);
    }

    Medidor::restarMemoria(sizeof(GestorDatos));
}

// Dividir cadena por delimitador
ArregloDinamico<string> GestorDatos::dividirCadena(const string& cadena, char delimitador) {
    ArregloDinamico<string> tokens;
    stringstream ss(cadena);
    string token;

    while (getline(ss, token, delimitador)) {
        tokens.agregar(token);
    }

    return tokens;
}

// Parsear fecha desde string "año-mes-dia"
Fecha GestorDatos::parsearFecha(const string& fechaStr) {
    ArregloDinamico<string> partes = dividirCadena(fechaStr, '-');

    if (partes.getCantidad() == 3) {
        int anio = stoi(partes.obtener(0));
        int mes = stoi(partes.obtener(1));
        int dia = stoi(partes.obtener(2));
        return Fecha(anio, mes, dia);
    }

    return Fecha(2000, 1, 1); // Fecha por defecto
}

// CARGAR USUARIOS
bool GestorDatos::cargarUsuarios() {
    ifstream archivo(PATH_USUARIOS);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo abrir " << PATH_USUARIOS << endl;
        return false;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        Medidor::incrementarIteraciones();

        if (linea.empty()) continue;

        ArregloDinamico<string> campos = dividirCadena(linea, '|');

        if (campos.getCantidad() >= 5) {
            string nickname = campos.obtener(0);
            string tipoMembresia = campos.obtener(1);
            string ciudad = campos.obtener(2);
            string pais = campos.obtener(3);
            Fecha fechaInscripcion = parsearFecha(campos.obtener(4));

            Usuario* usuario = new Usuario(nickname, tipoMembresia, ciudad, pais, fechaInscripcion);
            usuarios.agregar(usuario);
            count++;
        }
    }

    archivo.close();
    cout << "[GestorDatos] ✓ Cargados " << count << " usuarios" << endl;
    return true;
}

// CARGAR ARTISTAS
bool GestorDatos::cargarArtistas() {
    ifstream archivo(PATH_ARTISTAS);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo abrir " << PATH_ARTISTAS << endl;
        return false;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        Medidor::incrementarIteraciones();

        if (linea.empty()) continue;

        ArregloDinamico<string> campos = dividirCadena(linea, '|');

        if (campos.getCantidad() >= 5) {
            int id = stoi(campos.obtener(0));
            int edad = stoi(campos.obtener(1));
            string paisOrigen = campos.obtener(2);
            int seguidores = stoi(campos.obtener(3));
            int posicionTendencias = stoi(campos.obtener(4));

            Artista* artista = new Artista(id, edad, paisOrigen, seguidores, posicionTendencias);
            artistas.agregar(artista);
            count++;
        }
    }

    archivo.close();
    cout << "[GestorDatos] ✓ Cargados " << count << " artistas" << endl;
    return true;
}

// CARGAR ÁLBUMES
bool GestorDatos::cargarAlbumes() {
    ifstream archivo(PATH_ALBUMES);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo abrir " << PATH_ALBUMES << endl;
        return false;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        Medidor::incrementarIteraciones();

        if (linea.empty()) continue;

        ArregloDinamico<string> campos = dividirCadena(linea, '|');

        if (campos.getCantidad() >= 8) {
            int idArtista = stoi(campos.obtener(0));
            int idAlbum = stoi(campos.obtener(1));
            string nombre = campos.obtener(2);
            string generosStr = campos.obtener(3);
            Fecha fechaLanzamiento = parsearFecha(campos.obtener(4));
            int duracionTotal = stoi(campos.obtener(5));
            string selloDisco = campos.obtener(6);
            string rutaPortada = campos.obtener(7);
            float puntuacion = (campos.getCantidad() >= 9) ? stof(campos.obtener(8)) : 0.0f;

            // Buscar artista correspondiente
            Artista* artista = buscarArtistaPorId(idArtista);

            if (artista != nullptr) {
                Album* album = new Album(idArtista, idAlbum, nombre, fechaLanzamiento,
                                         selloDisco, rutaPortada, puntuacion);

                // Agregar géneros (separados por coma)
                ArregloDinamico<string> generos = dividirCadena(generosStr, ',');
                for (int i = 0; i < generos.getCantidad(); i++) {
                    album->agregarGenero(generos.obtener(i));
                }

                album->setDuracionTotal(duracionTotal);
                artista->agregarAlbum(album);
                count++;
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] ✓ Cargados " << count << " álbumes" << endl;
    return true;
}

// CARGAR CANCIONES
bool GestorDatos::cargarCanciones() {
    ifstream archivo(PATH_CANCIONES);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo abrir " << PATH_CANCIONES << endl;
        return false;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        Medidor::incrementarIteraciones();

        if (linea.empty()) continue;

        ArregloDinamico<string> campos = dividirCadena(linea, '|');

        if (campos.getCantidad() >= 6) {
            int idCancion = stoi(campos.obtener(0));
            string nombre = campos.obtener(1);
            int duracion = stoi(campos.obtener(2));
            string ruta128 = campos.obtener(3);
            string ruta320 = campos.obtener(4);
            int reproducciones = stoi(campos.obtener(5));

            // Extraer IDs del ID de 9 dígitos
            int idArtista = idCancion / 10000;
            int idAlbum = (idCancion / 100) % 100;

            // Buscar álbum correspondiente
            Album* album = buscarAlbum(idArtista, idAlbum);

            if (album != nullptr) {
                Cancion* cancion = new Cancion(idCancion, nombre, duracion, ruta128, ruta320);

                // Setear reproducciones (si hay)
                for (int i = 0; i < reproducciones; i++) {
                    cancion->incrementarReproducciones();
                }

                album->agregarCancion(cancion);
                count++;
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] ✓ Cargadas " << count << " canciones" << endl;
    return true;
}

// CARGAR CRÉDITOS
bool GestorDatos::cargarCreditos() {
    ifstream archivo(PATH_CREDITOS);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo abrir " << PATH_CREDITOS << endl;
        return false;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        Medidor::incrementarIteraciones();

        if (linea.empty()) continue;

        ArregloDinamico<string> campos = dividirCadena(linea, '|');

        if (campos.getCantidad() >= 5) {
            int idCancion = stoi(campos.obtener(0));
            string nombre = campos.obtener(1);
            string apellido = campos.obtener(2);
            string codigoAfiliacion = campos.obtener(3);
            string tipo = campos.obtener(4);

            // Buscar canción correspondiente
            Cancion* cancion = buscarCancionPorId(idCancion);

            if (cancion != nullptr) {
                Credito* credito = new Credito(nombre, apellido, codigoAfiliacion, tipo);
                cancion->agregarCredito(credito);
                count++;
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] ✓ Cargados " << count << " créditos" << endl;
    return true;
}

// CARGAR PUBLICIDAD
bool GestorDatos::cargarPublicidad() {
    ifstream archivo(PATH_PUBLICIDAD);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo abrir " << PATH_PUBLICIDAD << endl;
        return false;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        Medidor::incrementarIteraciones();

        if (linea.empty()) continue;

        ArregloDinamico<string> campos = dividirCadena(linea, '|');

        if (campos.getCantidad() >= 4) {
            int id = stoi(campos.obtener(0));
            string mensaje = campos.obtener(1);
            char categoria = campos.obtener(2)[0];
            int ultimaVez = stoi(campos.obtener(3));

            Publicidad* publicidad = new Publicidad(id, mensaje, categoria);
            publicidad->setUltimaVezMostrada(ultimaVez);
            publicidades.agregar(publicidad);
            count++;
        }
    }

    archivo.close();
    cout << "[GestorDatos] ✓ Cargadas " << count << " publicidades" << endl;
    return true;
}

// CARGAR FAVORITOS
bool GestorDatos::cargarFavoritos() {
    ifstream archivo(PATH_FAVORITOS);

    if (!archivo.is_open()) {
        // No es error crítico si no existe
        cout << "[GestorDatos] No se encontró archivo de favoritos (se creará al guardar)" << endl;
        return true;
    }

    string linea;
    int count = 0;

    while (getline(archivo, linea)) {
        Medidor::incrementarIteraciones();

        if (linea.empty()) continue;

        ArregloDinamico<string> campos = dividirCadena(linea, '|');

        if (campos.getCantidad() >= 1) {
            string nickname = campos.obtener(0);
            Usuario* usuario = buscarUsuario(nickname);

            if (usuario != nullptr && usuario->esPremium()) {
                ListaFavoritos* lista = usuario->getListaFavoritos();

                if (lista != nullptr) {
                    // Agregar canciones (del campo 1 en adelante)
                    for (int i = 1; i < campos.getCantidad(); i++) {
                        Medidor::incrementarIteraciones();
                        int idCancion = stoi(campos.obtener(i));
                        Cancion* cancion = buscarCancionPorId(idCancion);

                        if (cancion != nullptr) {
                            lista->agregar(cancion);
                        }
                    }
                    count++;
                }
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] ✓ Cargadas " << count << " listas de favoritos" << endl;
    return true;
}

// GUARDAR USUARIOS
bool GestorDatos::guardarUsuarios() {
    ofstream archivo(PATH_USUARIOS);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo crear " << PATH_USUARIOS << endl;
        return false;
    }

    for (int i = 0; i < usuarios.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Usuario* usuario = usuarios.obtener(i);

        archivo << usuario->getNickname() << "|"
                << usuario->getTipoMembresia() << "|"
                << usuario->getCiudad() << "|"
                << usuario->getPais() << "|"
                << usuario->getFechaInscripcion().getAño() << "-"
                << usuario->getFechaInscripcion().getMes() << "-"
                << usuario->getFechaInscripcion().getDia() << endl;
    }

    archivo.close();
    return true;
}

// GUARDAR ARTISTAS
bool GestorDatos::guardarArtistas() {
    ofstream archivo(PATH_ARTISTAS);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo crear " << PATH_ARTISTAS << endl;
        return false;
    }

    for (int i = 0; i < artistas.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Artista* artista = artistas.obtener(i);

        archivo << artista->getId() << "|"
                << artista->getEdad() << "|"
                << artista->getPaisOrigen() << "|"
                << artista->getSeguidores() << "|"
                << artista->getPosicionTendencias() << endl;
    }

    archivo.close();
    return true;
}

// GUARDAR ÁLBUMES
bool GestorDatos::guardarAlbumes() {
    ofstream archivo(PATH_ALBUMES);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo crear " << PATH_ALBUMES << endl;
        return false;
    }

    for (int i = 0; i < artistas.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Artista* artista = artistas.obtener(i);

        for (int j = 0; j < artista->getCantidadAlbumes(); j++) {
            Medidor::incrementarIteraciones();
            Album* album = artista->obtenerAlbum(j);

            archivo << album->getIdArtista() << "|"
                    << album->getIdAlbum() << "|"
                    << album->getNombre() << "|";

            // Géneros separados por coma
            for (int k = 0; k < album->getCantidadGeneros(); k++) {
                archivo << album->obtenerGenero(k);
                if (k < album->getCantidadGeneros() - 1) {
                    archivo << ",";
                }
            }

            archivo << "|"
                    << album->getFechaLanzamiento().getAño() << "-"
                    << album->getFechaLanzamiento().getMes() << "-"
                    << album->getFechaLanzamiento().getDia() << "|"
                    << album->getDuracionTotal() << "|"
                    << album->getSelloDisco() << "|"
                    << album->getRutaPortada() << "|"
                    << album->getPuntuacion() << endl;
        }
    }

    archivo.close();
    return true;
}

// GUARDAR CANCIONES
bool GestorDatos::guardarCanciones() {
    ofstream archivo(PATH_CANCIONES);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo crear " << PATH_CANCIONES << endl;
        return false;
    }

    for (int i = 0; i < artistas.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Artista* artista = artistas.obtener(i);

        for (int j = 0; j < artista->getCantidadAlbumes(); j++) {
            Medidor::incrementarIteraciones();
            Album* album = artista->obtenerAlbum(j);

            for (int k = 0; k < album->getCantidadCanciones(); k++) {
                Medidor::incrementarIteraciones();
                Cancion* cancion = album->obtenerCancion(k);

                archivo << cancion->getId() << "|"
                        << cancion->getNombre() << "|"
                        << cancion->getDuracion() << "|"
                        << cancion->getRuta128() << "|"
                        << cancion->getRuta320() << "|"
                        << cancion->getReproducciones() << endl;
            }
        }
    }

    archivo.close();
    return true;
}

// GUARDAR CRÉDITOS
bool GestorDatos::guardarCreditos() {
    ofstream archivo(PATH_CREDITOS);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo crear " << PATH_CREDITOS << endl;
        return false;
    }

    for (int i = 0; i < artistas.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Artista* artista = artistas.obtener(i);

        for (int j = 0; j < artista->getCantidadAlbumes(); j++) {
            Medidor::incrementarIteraciones();
            Album* album = artista->obtenerAlbum(j);

            for (int k = 0; k < album->getCantidadCanciones(); k++) {
                Medidor::incrementarIteraciones();
                Cancion* cancion = album->obtenerCancion(k);

                for (int m = 0; m < cancion->getCantidadCreditos(); m++) {
                    Medidor::incrementarIteraciones();
                    Credito* credito = cancion->obtenerCredito(m);

                    archivo << cancion->getId() << "|"
                            << credito->getNombre() << "|"
                            << credito->getApellido() << "|"
                            << credito->getCodigoAfiliacion() << "|"
                            << credito->getTipo() << endl;
                }
            }
        }
    }

    archivo.close();
    return true;
}

// GUARDAR PUBLICIDAD
bool GestorDatos::guardarPublicidad() {
    ofstream archivo(PATH_PUBLICIDAD);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo crear " << PATH_PUBLICIDAD << endl;
        return false;
    }

    for (int i = 0; i < publicidades.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Publicidad* pub = publicidades.obtener(i);

        archivo << pub->getId() << "|"
                << pub->getMensaje() << "|"
                << pub->getCategoria() << "|"
                << pub->getUltimaVezMostrada() << endl;
    }

    archivo.close();
    return true;
}

// GUARDAR FAVORITOS
bool GestorDatos::guardarFavoritos() {
    ofstream archivo(PATH_FAVORITOS);

    if (!archivo.is_open()) {
        cerr << "[Error] No se pudo crear " << PATH_FAVORITOS << endl;
        return false;
    }

    for (int i = 0; i < usuarios.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Usuario* usuario = usuarios.obtener(i);

        if (usuario->esPremium() && usuario->tieneListaFavoritos()) {
            ListaFavoritos* lista = usuario->getListaFavoritos();

            if (!lista->estaVacia()) {
                archivo << usuario->getNickname();

                for (int j = 0; j < lista->getCantidad(); j++) {
                    Medidor::incrementarIteraciones();
                    Cancion* cancion = lista->obtenerCancion(j);
                    archivo << "|" << cancion->getId();
                }

                archivo << endl;
            }
        }
    }

    archivo.close();
    return true;
}

// CARGAR TODOS LOS DATOS
bool GestorDatos::cargarDatos() {
    bool exito = true;

    exito &= cargarUsuarios();
    exito &= cargarArtistas();
    exito &= cargarAlbumes();
    exito &= cargarCanciones();
    exito &= cargarCreditos();
    exito &= cargarPublicidad();
    exito &= cargarFavoritos();

    return exito;
}

// GUARDAR TODOS LOS DATOS
bool GestorDatos::guardarDatos() {
    bool exito = true;

    exito &= guardarUsuarios();
    exito &= guardarArtistas();
    exito &= guardarAlbumes();
    exito &= guardarCanciones();
    exito &= guardarCreditos();
    exito &= guardarPublicidad();
    exito &= guardarFavoritos();

    return exito;
}

// BUSCAR USUARIO POR NICKNAME (búsqueda binaria)
Usuario* GestorDatos::buscarUsuario(const string& nickname) {
    // Búsqueda lineal (puedes optimizar con binaria si están ordenados)
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        Medidor::incrementarIteraciones();

        if (usuarios.obtener(i)->getNickname() == nickname) {
            return usuarios.obtener(i);
        }
    }

    return nullptr;
}

// BUSCAR ARTISTA POR ID
Artista* GestorDatos::buscarArtistaPorId(int id) {
    for (int i = 0; i < artistas.getCantidad(); i++) {
        Medidor::incrementarIteraciones();

        if (artistas.obtener(i)->getId() == id) {
            return artistas.obtener(i);
        }
    }

    return nullptr;
}

// BUSCAR ÁLBUM
Album* GestorDatos::buscarAlbum(int idArtista, int idAlbum) {
    Artista* artista = buscarArtistaPorId(idArtista);

    if (artista == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < artista->getCantidadAlbumes(); i++) {
        Medidor::incrementarIteraciones();
        Album* album = artista->obtenerAlbum(i);

        if (album->getIdAlbum() == idAlbum) {
            return album;
        }
    }

    return nullptr;
}

// BUSCAR CANCIÓN POR ID
Cancion* GestorDatos::buscarCancionPorId(int id) {
    for (int i = 0; i < artistas.getCantidad(); i++) {
        Medidor::incrementarIteraciones();
        Artista* artista = artistas.obtener(i);

        for (int j = 0; j < artista->getCantidadAlbumes(); j++) {
            Medidor::incrementarIteraciones();
            Album* album = artista->obtenerAlbum(j);

            for (int k = 0; k < album->getCantidadCanciones(); k++) {
                Medidor::incrementarIteraciones();
                Cancion* cancion = album->obtenerCancion(k);

                if (cancion->getId() == id) {
                    return cancion;
                }
            }
        }
    }

    return nullptr;
}

// GETTERS
ArregloDinamico<Usuario*>& GestorDatos::getUsuarios() {
    return usuarios;
}

ArregloDinamico<Artista*>& GestorDatos::getArtistas() {
    return artistas;
}

ArregloDinamico<Publicidad*>& GestorDatos::getPublicidades() {
    return publicidades;
}

#include "GestorDatos.h"
#include <iostream>
#include <sstream>

// Constructor por defecto
GestorDatos::GestorDatos() {
    rutaUsuarios = "data/usuarios.txt";
    rutaArtistas = "data/artistas.txt";
    rutaAlbumes = "data/albumes.txt";
    rutaCanciones = "data/canciones.txt";
    rutaCreditos = "data/creditos.txt";
    rutaPublicidad = "data/publicidad.txt";
    rutaFavoritos = "data/favoritos.txt";
}

// Constructor con carpeta personalizada
GestorDatos::GestorDatos(string carpetaData) {
    rutaUsuarios = carpetaData + "/usuarios.txt";
    rutaArtistas = carpetaData + "/artistas.txt";
    rutaAlbumes = carpetaData + "/albumes.txt";
    rutaCanciones = carpetaData + "/canciones.txt";
    rutaCreditos = carpetaData + "/creditos.txt";
    rutaPublicidad = carpetaData + "/publicidad.txt";
    rutaFavoritos = carpetaData + "/favoritos.txt";
}

// Destructor
GestorDatos::~GestorDatos() {
    // No hay memoria dinámica que liberar
}

// ============================================
// MÉTODOS AUXILIARES
// ============================================

// Parsear línea separada por delimitador
ArregloDinamico<string> GestorDatos::parsearLinea(string linea, char delimitador) {
    ArregloDinamico<string> campos;
    stringstream ss(linea);
    string campo;

    while (getline(ss, campo, delimitador)) {
        campos.agregar(campo);
    }

    return campos;
}

// Parsear fecha formato: año-mes-día
Fecha GestorDatos::parsearFecha(string fecha) {
    ArregloDinamico<string> partes = parsearLinea(fecha, '-');

    if (partes.getCantidad() == 3) {
        int año = stoi(partes.obtener(0));
        int mes = stoi(partes.obtener(1));
        int dia = stoi(partes.obtener(2));
        return Fecha(año, mes, dia);
    }

    return Fecha(2000, 1, 1);  // Fecha por defecto si hay error
}

// ============================================
// MÉTODOS DE CARGA
// ============================================

// Cargar usuarios
// Formato: nickname|tipoMembresia|ciudad|país|año-mes-día
void GestorDatos::cargarUsuarios(ArregloDinamico<Usuario*>& usuarios) {
    ifstream archivo(rutaUsuarios);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << rutaUsuarios << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        ArregloDinamico<string> campos = parsearLinea(linea, '|');

        if (campos.getCantidad() >= 5) {
            string nickname = campos.obtener(0);
            string tipoMembresia = campos.obtener(1);
            string ciudad = campos.obtener(2);
            string pais = campos.obtener(3);
            Fecha fechaInscripcion = parsearFecha(campos.obtener(4));

            Usuario* usuario = new Usuario(nickname, tipoMembresia, ciudad, pais, fechaInscripcion);
            usuarios.agregar(usuario);
        }
    }

    archivo.close();
    cout << "[GestorDatos] Cargados " << usuarios.getCantidad() << " usuarios" << endl;
}

// Cargar artistas
// Formato: id|edad|país|seguidores|posicionTendencias
void GestorDatos::cargarArtistas(ArregloDinamico<Artista*>& artistas) {
    ifstream archivo(rutaArtistas);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << rutaArtistas << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        ArregloDinamico<string> campos = parsearLinea(linea, '|');

        if (campos.getCantidad() >= 5) {
            int id = stoi(campos.obtener(0));
            int edad = stoi(campos.obtener(1));
            string pais = campos.obtener(2);
            int seguidores = stoi(campos.obtener(3));
            int posicion = stoi(campos.obtener(4));

            Artista* artista = new Artista(id, edad, pais, seguidores, posicion);
            artistas.agregar(artista);
        }
    }

    archivo.close();
    cout << "[GestorDatos] Cargados " << artistas.getCantidad() << " artistas" << endl;
}

// Cargar álbumes
// Formato: idArtista|idAlbum|nombre|géneros|año-mes-día|duracionTotal|sello|rutaPortada|puntuacion
void GestorDatos::cargarAlbumes(ArregloDinamico<Artista*>& artistas) {
    ifstream archivo(rutaAlbumes);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << rutaAlbumes << endl;
        return;
    }

    int totalAlbumes = 0;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        ArregloDinamico<string> campos = parsearLinea(linea, '|');

        if (campos.getCantidad() >= 9) {
            int idArtista = stoi(campos.obtener(0));
            int idAlbum = stoi(campos.obtener(1));
            string nombre = campos.obtener(2);
            string generosStr = campos.obtener(3);
            Fecha fechaLanzamiento = parsearFecha(campos.obtener(4));
            int duracionTotal = stoi(campos.obtener(5));
            string sello = campos.obtener(6);
            string rutaPortada = campos.obtener(7);
            float puntuacion = stof(campos.obtener(8));

            // Buscar el artista correspondiente
            for (int i = 0; i < artistas.getCantidad(); i++) {
                if (artistas[i]->getId() == idArtista) {
                    Album* album = new Album(idArtista, idAlbum, nombre, fechaLanzamiento,
                                             sello, rutaPortada, puntuacion);

                    // Parsear géneros (separados por comas)
                    ArregloDinamico<string> generos = parsearLinea(generosStr, ',');
                    for (int j = 0; j < generos.getCantidad(); j++) {
                        album->agregarGenero(generos[j]);
                    }

                    album->setDuracionTotal(duracionTotal);
                    artistas[i]->agregarAlbum(album);
                    totalAlbumes++;
                    break;
                }
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] Cargados " << totalAlbumes << " albumes" << endl;
}

// Cargar canciones
// Formato: idCancion|nombre|duracion|ruta128|ruta320|reproducciones
void GestorDatos::cargarCanciones(ArregloDinamico<Artista*>& artistas) {
    ifstream archivo(rutaCanciones);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << rutaCanciones << endl;
        return;
    }

    int totalCanciones = 0;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        ArregloDinamico<string> campos = parsearLinea(linea, '|');

        if (campos.getCantidad() >= 6) {
            int idCancion = stoi(campos.obtener(0));
            string nombre = campos.obtener(1);
            int duracion = stoi(campos.obtener(2));
            string ruta128 = campos.obtener(3);
            string ruta320 = campos.obtener(4);
            int reproducciones = stoi(campos.obtener(5));

            // Extraer IDs: 5 dígitos artista + 2 álbum + 2 canción
            int idArtista = idCancion / 10000;  // Primeros 5 dígitos
            int idAlbum = (idCancion / 100) % 100;  // Siguientes 2 dígitos

            // Buscar artista y álbum
            for (int i = 0; i < artistas.getCantidad(); i++) {
                if (artistas[i]->getId() == idArtista) {
                    for (int j = 0; j < artistas[i]->getCantidadAlbumes(); j++) {
                        Album* album = artistas[i]->obtenerAlbum(j);
                        if (album->getIdAlbum() == idAlbum) {
                            Cancion* cancion = new Cancion(idCancion, nombre, duracion,
                                                           ruta128, ruta320);
                            // Establecer reproducciones
                            for (int r = 0; r < reproducciones; r++) {
                                cancion->incrementarReproducciones();
                            }

                            album->agregarCancion(cancion);
                            totalCanciones++;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] Cargadas " << totalCanciones << " canciones" << endl;
}

// Cargar créditos
// Formato: idCancion|nombre|apellido|codigoAfiliacion|tipo
void GestorDatos::cargarCreditos(ArregloDinamico<Artista*>& artistas) {
    ifstream archivo(rutaCreditos);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << rutaCreditos << endl;
        return;
    }

    int totalCreditos = 0;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        ArregloDinamico<string> campos = parsearLinea(linea, '|');

        if (campos.getCantidad() >= 5) {
            int idCancion = stoi(campos.obtener(0));
            string nombre = campos.obtener(1);
            string apellido = campos.obtener(2);
            string codigo = campos.obtener(3);
            string tipo = campos.obtener(4);

            // Buscar la canción correspondiente
            Cancion* cancion = buscarCancionPorId(artistas, idCancion);
            if (cancion != nullptr) {
                Credito* credito = new Credito(nombre, apellido, codigo, tipo);
                cancion->agregarCredito(credito);
                totalCreditos++;
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] Cargados " << totalCreditos << " creditos" << endl;
}

// Cargar publicidad
// Formato: id|mensaje|categoría|ultVez
void GestorDatos::cargarPublicidad(ArregloDinamico<Publicidad*>& publicidades) {
    ifstream archivo(rutaPublicidad);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << rutaPublicidad << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        ArregloDinamico<string> campos = parsearLinea(linea, '|');

        if (campos.getCantidad() >= 4) {
            int id = stoi(campos.obtener(0));
            string mensaje = campos.obtener(1);
            char categoria = campos.obtener(2)[0];
            int ultVez = stoi(campos.obtener(3));

            Publicidad* pub = new Publicidad(id, mensaje, categoria);
            pub->setUltimaVezMostrada(ultVez);
            publicidades.agregar(pub);
        }
    }

    archivo.close();
    cout << "[GestorDatos] Cargadas " << publicidades.getCantidad() << " publicidades" << endl;
}

// Cargar favoritos
// Formato: nicknameUsuario|idCancion1|idCancion2|...
void GestorDatos::cargarFavoritos(ArregloDinamico<Usuario*>& usuarios,
                                  ArregloDinamico<Artista*>& artistas) {
    ifstream archivo(rutaFavoritos);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << rutaFavoritos << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        ArregloDinamico<string> campos = parsearLinea(linea, '|');

        if (campos.getCantidad() >= 2) {
            string nickname = campos.obtener(0);

            // Buscar usuario
            Usuario* usuario = buscarUsuarioPorNickname(usuarios, nickname);
            if (usuario != nullptr && usuario->tieneListaFavoritos()) {
                ListaFavoritos* lista = usuario->getListaFavoritos();

                // Agregar canciones a favoritos
                for (int i = 1; i < campos.getCantidad(); i++) {
                    int idCancion = stoi(campos.obtener(i));
                    Cancion* cancion = buscarCancionPorId(artistas, idCancion);
                    if (cancion != nullptr) {
                        lista->agregar(cancion);
                    }
                }
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] Favoritos cargados" << endl;
}

// ============================================
// MÉTODOS DE GUARDADO
// ============================================

// Guardar usuarios
void GestorDatos::guardarUsuarios(ArregloDinamico<Usuario*>& usuarios) {
    ofstream archivo(rutaUsuarios);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear " << rutaUsuarios << endl;
        return;
    }

    for (int i = 0; i < usuarios.getCantidad(); i++) {
        Usuario* u = usuarios[i];
        Fecha fecha = u->getFechaInscripcion();

        archivo << u->getNickname() << "|"
                << u->getTipoMembresia() << "|"
                << u->getCiudad() << "|"
                << u->getPais() << "|"
                << fecha.getAño() << "-" << fecha.getMes() << "-" << fecha.getDia()
                << endl;
    }

    archivo.close();
    cout << "[GestorDatos] Guardados " << usuarios.getCantidad() << " usuarios" << endl;
}

// Guardar publicidad
void GestorDatos::guardarPublicidad(ArregloDinamico<Publicidad*>& publicidades) {
    ofstream archivo(rutaPublicidad);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear " << rutaPublicidad << endl;
        return;
    }

    for (int i = 0; i < publicidades.getCantidad(); i++) {
        Publicidad* p = publicidades[i];

        archivo << p->getId() << "|"
                << p->getMensaje() << "|"
                << p->getCategoria() << "|"
                << p->getUltimaVezMostrada()
                << endl;
    }

    archivo.close();
    cout << "[GestorDatos] Guardadas " << publicidades.getCantidad() << " publicidades" << endl;
}

// Guardar favoritos
void GestorDatos::guardarFavoritos(ArregloDinamico<Usuario*>& usuarios) {
    ofstream archivo(rutaFavoritos);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear " << rutaFavoritos << endl;
        return;
    }

    for (int i = 0; i < usuarios.getCantidad(); i++) {
        Usuario* u = usuarios[i];

        if (u->tieneListaFavoritos()) {
            ListaFavoritos* lista = u->getListaFavoritos();

            if (lista->getCantidad() > 0) {
                archivo << u->getNickname();

                for (int j = 0; j < lista->getCantidad(); j++) {
                    archivo << "|" << lista->obtenerCancion(j)->getId();
                }

                archivo << endl;
            }
        }
    }

    archivo.close();
    cout << "[GestorDatos] Favoritos guardados" << endl;
}

// Guardar artistas (solo datos básicos)
void GestorDatos::guardarArtistas(ArregloDinamico<Artista*>& artistas) {
    ofstream archivo(rutaArtistas);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear " << rutaArtistas << endl;
        return;
    }

    for (int i = 0; i < artistas.getCantidad(); i++) {
        Artista* a = artistas[i];

        archivo << a->getId() << "|"
                << a->getEdad() << "|"
                << a->getPaisOrigen() << "|"
                << a->getSeguidores() << "|"
                << a->getPosicionTendencias()
                << endl;
    }

    archivo.close();
    cout << "[GestorDatos] Guardados " << artistas.getCantidad() << " artistas" << endl;
}

// Guardar álbumes (nota: implementación simplificada)
void GestorDatos::guardarAlbumes(ArregloDinamico<Artista*>& artistas) {
    // Implementación simplificada - en proyecto real recorrería todos los álbumes
    cout << "[GestorDatos] Guardado de albumes (implementacion pendiente)" << endl;
}

void GestorDatos::guardarCanciones(ArregloDinamico<Artista*>& artistas) {
    cout << "[GestorDatos] Guardado de canciones (implementacion pendiente)" << endl;
}

void GestorDatos::guardarCreditos(ArregloDinamico<Artista*>& artistas) {
    cout << "[GestorDatos] Guardado de creditos (implementacion pendiente)" << endl;
}

// Guardar todo
void GestorDatos::guardarTodo(ArregloDinamico<Usuario*>& usuarios,
                              ArregloDinamico<Artista*>& artistas,
                              ArregloDinamico<Publicidad*>& publicidades) {
    cout << "\n=== GUARDANDO DATOS ===" << endl;
    guardarUsuarios(usuarios);
    guardarArtistas(artistas);
    guardarPublicidad(publicidades);
    guardarFavoritos(usuarios);
    cout << "======================\n" << endl;
}

// Cargar todo
void GestorDatos::cargarTodo(ArregloDinamico<Usuario*>& usuarios,
                             ArregloDinamico<Artista*>& artistas,
                             ArregloDinamico<Publicidad*>& publicidades) {
    cout << "\n=== CARGANDO DATOS ===" << endl;
    cargarUsuarios(usuarios);
    cargarArtistas(artistas);
    cargarAlbumes(artistas);
    cargarCanciones(artistas);
    cargarCreditos(artistas);
    cargarPublicidad(publicidades);
    cargarFavoritos(usuarios, artistas);
    cout << "======================\n" << endl;
}

// ============================================
// MÉTODOS DE BÚSQUEDA AUXILIARES
// ============================================

// Buscar canción por ID en todos los artistas
Cancion* GestorDatos::buscarCancionPorId(ArregloDinamico<Artista*>& artistas, int idCancion) {
    for (int i = 0; i < artistas.getCantidad(); i++) {
        Artista* artista = artistas[i];
        for (int j = 0; j < artista->getCantidadAlbumes(); j++) {
            Album* album = artista->obtenerAlbum(j);
            for (int k = 0; k < album->getCantidadCanciones(); k++) {
                Cancion* cancion = album->obtenerCancion(k);
                if (cancion->getId() == idCancion) {
                    return cancion;
                }
            }
        }
    }
    return nullptr;
}

// Buscar usuario por nickname
Usuario* GestorDatos::buscarUsuarioPorNickname(ArregloDinamico<Usuario*>& usuarios, string nickname) {
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        if (usuarios[i]->getNickname() == nickname) {
            return usuarios[i];
        }
    }
    return nullptr;
}

// Validar integridad
bool GestorDatos::validarIntegridad() {
    // Implementación básica - verificar que existan los archivos
    ifstream testUsuarios(rutaUsuarios);
    bool existe = testUsuarios.is_open();
    testUsuarios.close();
    return existe;
}

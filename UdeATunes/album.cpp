#include "Album.h"

// Constructor por defecto
Album::Album() : fechaLanzamiento(2000, 1, 1)
{
    idArtista = 0;
    idAlbum = 0;
    nombre = "";
    duracionTotal = 0;
    selloDisco = "";
    rutaPortada = "";
    puntuacion = 0.0;
}

// Constructor parametrizado
Album::Album(int idArtista, int idAlbum, string nombre, Fecha fechaLanzamiento,
             string selloDisco, string rutaPortada, float puntuacion)
    : fechaLanzamiento(fechaLanzamiento)
{
    this->idArtista = idArtista;
    this->idAlbum = idAlbum;
    this->nombre = nombre;
    this->duracionTotal = 0;
    this->selloDisco = selloDisco;
    this->rutaPortada = rutaPortada;
    this->puntuacion = puntuacion;
}

// Constructor de copia
Album::Album(const Album& otro) : fechaLanzamiento(otro.fechaLanzamiento)
{
    idArtista = otro.idArtista;
    idAlbum = otro.idAlbum;
    nombre = otro.nombre;
    duracionTotal = otro.duracionTotal;
    selloDisco = otro.selloDisco;
    rutaPortada = otro.rutaPortada;
    puntuacion = otro.puntuacion;

    // Copiar géneros
    for (int i = 0; i < otro.generos.getCantidad(); i++)
    {
        generos.agregar(otro.generos.obtener(i));
    }

    // Copiar canciones (copia profunda)
    for (int i = 0; i < otro.canciones.getCantidad(); i++)
    {
        Cancion* cancionOriginal = otro.canciones.obtener(i);
        Cancion* cancionCopia = new Cancion(*cancionOriginal);
        canciones.agregar(cancionCopia);
    }
}

// Destructor
Album::~Album()
{
    // Liberar memoria de todas las canciones
    for (int i = 0; i < canciones.getCantidad(); i++)
    {
        delete canciones.obtener(i);
    }
}

// Operador de igualdad (compara por IDs)
bool Album::operator==(const Album& otro) const
{
    return (idArtista == otro.idArtista && idAlbum == otro.idAlbum);
}

// Operador menor que (ordenar por nombre)
bool Album::operator<(const Album& otro) const
{
    return nombre < otro.nombre;
}

// Operador de asignación
Album& Album::operator=(const Album& otro)
{
    if (this != &otro)
    {
        // Liberar memoria existente
        for (int i = 0; i < canciones.getCantidad(); i++)
        {
            delete canciones.obtener(i);
        }
        canciones.limpiar();
        generos.limpiar();

        // Copiar datos básicos
        idArtista = otro.idArtista;
        idAlbum = otro.idAlbum;
        nombre = otro.nombre;
        fechaLanzamiento = otro.fechaLanzamiento;
        duracionTotal = otro.duracionTotal;
        selloDisco = otro.selloDisco;
        rutaPortada = otro.rutaPortada;
        puntuacion = otro.puntuacion;

        // Copiar géneros
        for (int i = 0; i < otro.generos.getCantidad(); i++)
        {
            generos.agregar(otro.generos.obtener(i));
        }

        // Copiar canciones
        for (int i = 0; i < otro.canciones.getCantidad(); i++)
        {
            Cancion* cancionOriginal = otro.canciones.obtener(i);
            Cancion* cancionCopia = new Cancion(*cancionOriginal);
            canciones.agregar(cancionCopia);
        }
    }
    return *this;
}

// Agregar canción
void Album::agregarCancion(Cancion* cancion)
{
    if (cancion != nullptr)
    {
        canciones.agregar(cancion);
    }
}

// Obtener canción por índice
Cancion* Album::obtenerCancion(int indice) const
{
    if (indice >= 0 && indice < canciones.getCantidad())
    {
        return canciones.obtener(indice);
    }
    return nullptr;
}

// Obtener cantidad de canciones
int Album::getCantidadCanciones() const
{
    return canciones.getCantidad();
}

// Agregar género
void Album::agregarGenero(string genero)
{
    if (!genero.empty())
    {
        generos.agregar(genero);
    }
}

// Obtener género por índice
string Album::obtenerGenero(int indice) const
{
    if (indice >= 0 && indice < generos.getCantidad())
    {
        return generos.obtener(indice);
    }
    return "";
}

// Obtener cantidad de géneros
int Album::getCantidadGeneros() const
{
    return generos.getCantidad();
}

// Calcular duración total sumando todas las canciones
void Album::calcularDuracionTotal()
{
    duracionTotal = 0;
    for (int i = 0; i < canciones.getCantidad(); i++)
    {
        duracionTotal += canciones.obtener(i)->getDuracion();
    }
}

// Getters
int Album::getIdArtista() const
{
    return idArtista;
}

int Album::getIdAlbum() const
{
    return idAlbum;
}

string Album::getNombre() const
{
    return nombre;
}

Fecha Album::getFechaLanzamiento() const
{
    return fechaLanzamiento;
}

int Album::getDuracionTotal() const
{
    return duracionTotal;
}

string Album::getSelloDisco() const
{
    return selloDisco;
}

string Album::getRutaPortada() const
{
    return rutaPortada;
}

float Album::getPuntuacion() const
{
    return puntuacion;
}

// Setters con validación
void Album::setIdArtista(int idArtista)
{
    // Validar que sea 5 dígitos
    if (idArtista >= 10000 && idArtista <= 99999)
    {
        this->idArtista = idArtista;
    }
}

void Album::setIdAlbum(int idAlbum)
{
    // Validar que sea 2 dígitos
    if (idAlbum >= 10 && idAlbum <= 99)
    {
        this->idAlbum = idAlbum;
    }
}

void Album::setNombre(string nombre)
{
    if (!nombre.empty()) {
        this->nombre = nombre;
    }
}

void Album::setFechaLanzamiento(Fecha fecha)
{
    fechaLanzamiento = fecha;
}

void Album::setDuracionTotal(int duracion)
{
    if (duracion >= 0) {
        this->duracionTotal = duracion;
    }
}

void Album::setSelloDisco(string sello)
{
    if (!sello.empty()) {
        this->selloDisco = sello;
    }
}

void Album::setRutaPortada(string ruta)
{
    if (!ruta.empty()) {
        this->rutaPortada = ruta;
    }
}

void Album::setPuntuacion(float puntuacion)
{
    // Validar rango 0.0 - 10.0
    if (puntuacion >= 0.0 && puntuacion <= 10.0)
    {
        this->puntuacion = puntuacion;
    }
}

#include "Artista.h"

// Constructor por defecto
Artista::Artista() {
    id = 0;
    edad = 0;
    paisOrigen = "";
    seguidores = 0;
    posicionTendencias = 0;
}

// Constructor parametrizado
Artista::Artista(int id, int edad, string paisOrigen, int seguidores, int posicionTendencias)
{
    this->id = id;
    this->edad = edad;
    this->paisOrigen = paisOrigen;
    this->seguidores = seguidores;
    this->posicionTendencias = posicionTendencias;
}

// Constructor de copia
Artista::Artista(const Artista& otro)
{
    id = otro.id;
    edad = otro.edad;
    paisOrigen = otro.paisOrigen;
    seguidores = otro.seguidores;
    posicionTendencias = otro.posicionTendencias;

    // Copiar álbumes (copia profunda)
    for (int i = 0; i < otro.albumes.getCantidad(); i++)
    {
        Album* albumOriginal = otro.albumes.obtener(i);
        Album* albumCopia = new Album(*albumOriginal);
        albumes.agregar(albumCopia);
    }
}

// Destructor
Artista::~Artista()
{
    // Liberar memoria de todos los álbumes
    for (int i = 0; i < albumes.getCantidad(); i++)
    {
        delete albumes.obtener(i);
    }
}

// Operador de igualdad (compara por ID)
bool Artista::operator==(const Artista& otro) const
{
    return id == otro.id;
}

// Operador menor que (ordenar por seguidores, descendente)
bool Artista::operator<(const Artista& otro) const
{
    // Mayor número de seguidores es "menor" (para ordenar descendente)
    return seguidores > otro.seguidores;
}

// Operador de asignación
Artista& Artista::operator=(const Artista& otro)
{
    if (this != &otro)
    {
        // Liberar memoria existente
        for (int i = 0; i < albumes.getCantidad(); i++)
        {
            delete albumes.obtener(i);
        }
        albumes.limpiar();

        // Copiar datos básicos
        id = otro.id;
        edad = otro.edad;
        paisOrigen = otro.paisOrigen;
        seguidores = otro.seguidores;
        posicionTendencias = otro.posicionTendencias;

        // Copiar álbumes
        for (int i = 0; i < otro.albumes.getCantidad(); i++)
        {
            Album* albumOriginal = otro.albumes.obtener(i);
            Album* albumCopia = new Album(*albumOriginal);
            albumes.agregar(albumCopia);
        }
    }
    return *this;
}

// Agregar álbum
void Artista::agregarAlbum(Album* album)
{
    if (album != nullptr)
    {
        albumes.agregar(album);
    }
}

// Obtener álbum por índice
Album* Artista::obtenerAlbum(int indice) const
{
    if (indice >= 0 && indice < albumes.getCantidad())
    {
        return albumes.obtener(indice);
    }
    return nullptr;
}

// Obtener cantidad de álbumes
int Artista::getCantidadAlbumes() const
{
    return albumes.getCantidad();
}

// Getters
int Artista::getId() const
{
    return id;
}

int Artista::getEdad() const
{
    return edad;
}

string Artista::getPaisOrigen() const
{
    return paisOrigen;
}

int Artista::getSeguidores() const
{
    return seguidores;
}

int Artista::getPosicionTendencias() const
{
    return posicionTendencias;
}

// Setters con validación
void Artista::setId(int id)
{
    // Validar que sea 5 dígitos
    if (id >= 10000 && id <= 99999)
    {
        this->id = id;
    }
}

void Artista::setEdad(int edad)
{
    if (edad >= 0 && edad <= 120)
    {
        this->edad = edad;
    }
}

void Artista::setPaisOrigen(string pais)
{
    if (!pais.empty())
    {
        this->paisOrigen = pais;
    }
}

void Artista::setSeguidores(int seguidores)
{
    if (seguidores >= 0)
    {
        this->seguidores = seguidores;
    }
}

void Artista::setPosicionTendencias(int posicion)
{
    if (posicion >= 0)
    {
        this->posicionTendencias = posicion;
    }
}

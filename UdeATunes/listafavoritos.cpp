#include "ListaFavoritos.h"

// Constructor por defecto
ListaFavoritos::ListaFavoritos()
{
    usuarioDueño = "";
}

// Constructor parametrizado
ListaFavoritos::ListaFavoritos(string usuarioDueño)
{
    this->usuarioDueño = usuarioDueño;
}

// Constructor de copia
ListaFavoritos::ListaFavoritos(const ListaFavoritos& otra)
{
    usuarioDueño = otra.usuarioDueño;

    // Copiar referencias a canciones (NO copia profunda, solo punteros)
    // Las canciones pertenecen a otros objetos (álbumes)
    for (int i = 0; i < otra.canciones.getCantidad(); i++) {
        canciones.agregar(otra.canciones.obtener(i));
    }
}

// Destructor
ListaFavoritos::~ListaFavoritos()
{
    // NO liberar memoria de canciones
    // Las canciones son referencias a objetos que existen en álbumes
    // Solo limpiamos el arreglo de punteros
}

// Operador de igualdad (compara por usuario dueño)
bool ListaFavoritos::operator==(const ListaFavoritos& otra) const
{
    return usuarioDueño == otra.usuarioDueño;
}

// Operador de asignación
ListaFavoritos& ListaFavoritos::operator=(const ListaFavoritos& otra)
{
    if (this != &otra)
    {
        // Limpiar canciones existentes (sin liberar memoria)
        canciones.limpiar();

        // Copiar datos
        usuarioDueño = otra.usuarioDueño;

        // Copiar referencias
        for (int i = 0; i < otra.canciones.getCantidad(); i++)
        {
            canciones.agregar(otra.canciones.obtener(i));
        }
    }
    return *this;
}

// Agregar canción
bool ListaFavoritos::agregar(Cancion* cancion)
{
    // Verificar que no sea nullptr
    if (cancion == nullptr)
    {
        return false;
    }

    // Verificar que no esté llena
    if (estaLlena()) {
        return false;
    }

    // Verificar que no esté duplicada
    if (contiene(cancion->getId()))
    {
        return false;
    }

    // Agregar la canción
    canciones.agregar(cancion);
    return true;
}

// Eliminar canción por ID
bool ListaFavoritos::eliminar(int idCancion)
{
    int indice = buscarIndicePorId(idCancion);

    if (indice != -1)
    {
        canciones.eliminar(indice);
        return true;
    }

    return false;  // No se encontró
}

// Verificar si contiene una canción
bool ListaFavoritos::contiene(int idCancion) const
{
    return buscarIndicePorId(idCancion) != -1;
}

// Obtener canción por índice
Cancion* ListaFavoritos::obtenerCancion(int indice) const
{
    if (indice >= 0 && indice < canciones.getCantidad())
    {
        return canciones.obtener(indice);
    }
    return nullptr;
}

// Buscar índice de una canción por su ID
int ListaFavoritos::buscarIndicePorId(int idCancion) const
{
    for (int i = 0; i < canciones.getCantidad(); i++)
    {
        if (canciones.obtener(i)->getId() == idCancion)
        {
            return i;
        }
    }
    return -1;  // No encontrada
}

// Obtener cantidad de canciones
int ListaFavoritos::getCantidad() const
{
    return canciones.getCantidad();
}

// Obtener usuario dueño
string ListaFavoritos::getUsuarioDueño() const
{
    return usuarioDueño;
}

// Verificar si está llena
bool ListaFavoritos::estaLlena() const
{
    return canciones.getCantidad() >= MAX_CANCIONES;
}

// Verificar si está vacía
bool ListaFavoritos::estaVacia() const
{
    return canciones.getCantidad() == 0;
}

// Setter de usuario dueño
void ListaFavoritos::setUsuarioDueño(string usuario)
{
    if (!usuario.empty())
    {
        this->usuarioDueño = usuario;
    }
}

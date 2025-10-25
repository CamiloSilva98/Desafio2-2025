#include "Usuario.h"

// Constructor por defecto
Usuario::Usuario() : fechaInscripcion(2000, 1, 1)
{
    nickname = "";
    tipoMembresia = "estandar";
    ciudad = "";
    pais = "";
    listaFavoritos = nullptr;  // Por defecto no tiene lista
}

// Constructor parametrizado
Usuario::Usuario(string nickname, string tipoMembresia, string ciudad, string pais, Fecha fechaInscripcion)
    : fechaInscripcion(fechaInscripcion)
{
    this->nickname = nickname;
    this->tipoMembresia = tipoMembresia;
    this->ciudad = ciudad;
    this->pais = pais;
    this->listaFavoritos = nullptr;

    // Si es premium, crear lista de favoritos automáticamente
    if (tipoMembresia == "premium")
    {
        crearListaFavoritos();
    }
}

// Constructor de copia
Usuario::Usuario(const Usuario& otro) : fechaInscripcion(otro.fechaInscripcion)
{
    nickname = otro.nickname;
    tipoMembresia = otro.tipoMembresia;
    ciudad = otro.ciudad;
    pais = otro.pais;

    // Copiar lista de favoritos si existe
    if (otro.listaFavoritos != nullptr)
    {
        listaFavoritos = new ListaFavoritos(*otro.listaFavoritos);
    }
    else
    {
        listaFavoritos = nullptr;
    }

    // Copiar historial (solo referencias, no copia profunda)
    for (int i = 0; i < otro.historicoReproduccion.getCantidad(); i++)
    {
        historicoReproduccion.agregar(otro.historicoReproduccion.obtener(i));
    }
}

// Destructor
Usuario::~Usuario()
{
    // Liberar lista de favoritos si existe
    if (listaFavoritos != nullptr)
    {
        delete listaFavoritos;
    }

    // NO liberar canciones del historial (son referencias)
}

// Operador de igualdad (compara por nickname)
bool Usuario::operator==(const Usuario& otro) const
{
    return nickname == otro.nickname;
}

// Operador menor que (ordenar por nickname alfabéticamente)
bool Usuario::operator<(const Usuario& otro) const
{
    return nickname < otro.nickname;
}

// Operador de asignación
Usuario& Usuario::operator=(const Usuario& otro)
{
    if (this != &otro)
    {
        // Liberar memoria existente
        if (listaFavoritos != nullptr)
        {
            delete listaFavoritos;
            listaFavoritos = nullptr;
        }

        historicoReproduccion.limpiar();

        // Copiar datos básicos
        nickname = otro.nickname;
        tipoMembresia = otro.tipoMembresia;
        ciudad = otro.ciudad;
        pais = otro.pais;
        fechaInscripcion = otro.fechaInscripcion;

        // Copiar lista de favoritos
        if (otro.listaFavoritos != nullptr)
        {
            listaFavoritos = new ListaFavoritos(*otro.listaFavoritos);
        }

        // Copiar historial
        for (int i = 0; i < otro.historicoReproduccion.getCantidad(); i++)
        {
            historicoReproduccion.agregar(otro.historicoReproduccion.obtener(i));
        }
    }
    return *this;
}

// Agregar canción al historial
void Usuario::agregarAlHistorico(Cancion* cancion)
{
    if (cancion == nullptr)
    {
        return;
    }

    // Si el historial está lleno, eliminar la más antigua (primera)
    if (historicoReproduccion.getCantidad() >= MAX_HISTORICO)
    {
        historicoReproduccion.eliminar(0);
    }

    // Agregar la nueva canción al final
    historicoReproduccion.agregar(cancion);
}

// Obtener canción del historial
Cancion* Usuario::obtenerDelHistorico(int indice) const
{
    if (indice >= 0 && indice < historicoReproduccion.getCantidad())
    {
        return historicoReproduccion.obtener(indice);
    }
    return nullptr;
}

// Obtener cantidad de canciones en historial
int Usuario::getCantidadHistorico() const
{
    return historicoReproduccion.getCantidad();
}

// Crear lista de favoritos (solo para premium)
void Usuario::crearListaFavoritos()
{
    // Solo crear si es premium y no tiene una ya
    if (esPremium() && listaFavoritos == nullptr)
    {
        listaFavoritos = new ListaFavoritos(nickname);
    }
}

// Verificar si tiene lista de favoritos
bool Usuario::tieneListaFavoritos() const
{
    return listaFavoritos != nullptr;
}

// Obtener lista de favoritos
ListaFavoritos* Usuario::getListaFavoritos() const
{
    return listaFavoritos;
}

// Verificar si es premium
bool Usuario::esPremium() const
{
    return tipoMembresia == "premium";
}

// Verificar si es estándar
bool Usuario::esEstandar() const
{
    return tipoMembresia == "estandar";
}

// Getters
string Usuario::getNickname() const
{
    return nickname;
}

string Usuario::getTipoMembresia() const
{
    return tipoMembresia;
}

string Usuario::getCiudad() const
{
    return ciudad;
}

string Usuario::getPais() const
{
    return pais;
}

Fecha Usuario::getFechaInscripcion() const
{
    return fechaInscripcion;
}

// Setters con validación
void Usuario::setNickname(string nickname)
{
    if (!nickname.empty())
    {
        this->nickname = nickname;
    }
}

void Usuario::setTipoMembresia(string tipo)
{
    // Solo permitir "estandar" o "premium"
    if (tipo == "estandar" || tipo == "premium")
    {
        // Si cambia a premium y no tiene lista, crearla
        if (tipo == "premium" && this->tipoMembresia != "premium")
        {
            this->tipoMembresia = tipo;
            crearListaFavoritos();
        }
        // Si cambia a estándar, eliminar lista de favoritos
        else if (tipo == "estandar" && this->tipoMembresia == "premium")
        {
            this->tipoMembresia = tipo;
            if (listaFavoritos != nullptr)
            {
                delete listaFavoritos;
                listaFavoritos = nullptr;
            }
        } else
        {
            this->tipoMembresia = tipo;
        }
    }
}

void Usuario::setCiudad(string ciudad)
{
    if (!ciudad.empty())
    {
        this->ciudad = ciudad;
    }
}

void Usuario::setPais(string pais)
{
    if (!pais.empty())
    {
        this->pais = pais;
    }
}

void Usuario::setFechaInscripcion(Fecha fecha)
{
    fechaInscripcion = fecha;
}

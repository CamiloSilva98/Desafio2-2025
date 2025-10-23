#include "Credito.h"

// Constructor parametrizado
Credito::Credito(string nombre, string apellido, string codigoAfiliacion, string tipo)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->codigoAfiliacion = codigoAfiliacion;
    this->tipo = tipo;
}

// Constructor de copia
Credito::Credito(const Credito& otro)
{
    nombre = otro.nombre;
    apellido = otro.apellido;
    codigoAfiliacion = otro.codigoAfiliacion;
    tipo = otro.tipo;
}

// Destructor
Credito::~Credito()
{
    // No hay memoria dinámica que liberar
    // Los strings se destruyen automáticamente
}

// Operador de igualdad
bool Credito::operator==(const Credito& otro) const
{
    return (codigoAfiliacion == otro.codigoAfiliacion);
    // Comparamos por código de afiliación (debe ser único)
}

// Operador menor que (para ordenamiento)
bool Credito::operator<(const Credito& otro) const
{
    // Ordenar por apellido, luego por nombre
    if (apellido != otro.apellido)
        return apellido < otro.apellido;
    return nombre < otro.nombre;
}

// Operador de asignación
Credito& Credito::operator=(const Credito& otro)
{
    // Protección contra autoasignación
    if (this != &otro)
    {
        nombre = otro.nombre;
        apellido = otro.apellido;
        codigoAfiliacion = otro.codigoAfiliacion;
        tipo = otro.tipo;
    }
    return *this;
}

// Getters
string Credito::getNombre() const
{
    return nombre;
}

string Credito::getApellido() const
{
    return apellido;
}

string Credito::getCodigoAfiliacion() const
{
    return codigoAfiliacion;
}

string Credito::getTipo() const
{
    return tipo;
}

// Setters con validación
void Credito::setNombre(string nombre)
{
    if (!nombre.empty())
    {
        this->nombre = nombre;
    }
}

void Credito::setApellido(string apellido)
{
    if (!apellido.empty())
    {
        this->apellido = apellido;
    }
}

void Credito::setCodigoAfiliacion(string codigoAfiliacion)
{
    if (!codigoAfiliacion.empty())
    {
        this->codigoAfiliacion = codigoAfiliacion;
    }
}

void Credito::setTipo(string tipo)
{
    // Validar que sea un tipo válido
    if (tipo == "productor" || tipo == "musico" || tipo == "compositor" ||
        tipo == "arreglista" || tipo == "ingeniero" || tipo == "letrista")
    {
        this->tipo = tipo;
    }
}

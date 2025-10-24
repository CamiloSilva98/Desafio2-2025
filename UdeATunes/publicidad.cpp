#include "Publicidad.h"

// Constructor por defecto
Publicidad::Publicidad()
{
    id = 0;
    mensaje = "";
    categoria = 'C';
    ultimaVezMostrada = 0;
}

// Constructor parametrizado
Publicidad::Publicidad(int id, string mensaje, char categoria)
{
    this->id = id;
    this->mensaje = mensaje;
    this->categoria = categoria;
    this->ultimaVezMostrada = 0;
}

// Constructor de copia
Publicidad::Publicidad(const Publicidad& otra)
{
    id = otra.id;
    mensaje = otra.mensaje;
    categoria = otra.categoria;
    ultimaVezMostrada = otra.ultimaVezMostrada;
}

// Destructor
Publicidad::~Publicidad()
{
    // No hay memoria dinámica que liberar
}

// Operador de igualdad (compara por ID)
bool Publicidad::operator==(const Publicidad& otra) const
{
    return id == otra.id;
}

// Operador menor que (ordenar por categoría: AAA > B > C)
bool Publicidad::operator<(const Publicidad& otra) const
{
    // Orden: 'A' < 'B' < 'C' (alfabéticamente)
    // Pero queremos prioridad: AAA > B > C
    // Entonces invertimos: C < B < A
    return categoria > otra.categoria;
}

// Operador de asignación
Publicidad& Publicidad::operator=(const Publicidad& otra)
{
    if (this != &otra) {
        id = otra.id;
        mensaje = otra.mensaje;
        categoria = otra.categoria;
        ultimaVezMostrada = otra.ultimaVezMostrada;
    }
    return *this;
}

// Calcular peso según categoría (para selección probabilística)
int Publicidad::calcularPeso() const
{
    // Según preinforme: C=1, B=2, AAA=3
    switch (categoria) {
    case 'C':
        return 1;
    case 'B':
        return 2;
    case 'A':  // AAA
        return 3;
    default:
        return 1;  // Por defecto C
    }
}

// Getters
int Publicidad::getId() const
{
    return id;
}

string Publicidad::getMensaje() const
{
    return mensaje;
}

char Publicidad::getCategoria() const
{
    return categoria;
}

int Publicidad::getUltimaVezMostrada() const
{
    return ultimaVezMostrada;
}

// Setters con validación
void Publicidad::setId(int id)
{
    if (id > 0)
    {
        this->id = id;
    }
}

void Publicidad::setMensaje(string mensaje)
{
    if (!mensaje.empty())
    {
        this->mensaje = mensaje;
    }
}

void Publicidad::setCategoria(char categoria)
{
    // Solo permitir 'C', 'B', 'A'
    if (categoria == 'C' || categoria == 'B' || categoria == 'A')
    {
        this->categoria = categoria;
    }
}

void Publicidad::setUltimaVezMostrada(int valor)
{
    if (valor >= 0)
    {
        this->ultimaVezMostrada = valor;
    }
}

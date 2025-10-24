#include "Cancion.h"

// Constructor por defecto
Cancion::Cancion()
{
    id = 0;
    nombre = "";
    duracion = 0;
    ruta128 = "";
    ruta320 = "";
    reproducciones = 0;
}

// Constructor parametrizado
Cancion::Cancion(int id, string nombre, int duracion, string ruta128, string ruta320)
{
    this->id = id;
    this->nombre = nombre;
    this->duracion = duracion;
    this->ruta128 = ruta128;
    this->ruta320 = ruta320;
    this->reproducciones = 0;
}

// Constructor de copia
Cancion::Cancion(const Cancion& otra)
{
    id = otra.id;
    nombre = otra.nombre;
    duracion = otra.duracion;
    ruta128 = otra.ruta128;
    ruta320 = otra.ruta320;
    reproducciones = otra.reproducciones;

    // Copiar créditos (copia profunda de punteros)
    for (int i = 0; i < otra.creditos.getCantidad(); i++)
    {
        Credito* creditoOriginal = otra.creditos.obtener(i);
        Credito* creditoCopia = new Credito(*creditoOriginal);
        creditos.agregar(creditoCopia);
    }
}

// Destructor
Cancion::~Cancion()
{
    // Liberar memoria de todos los créditos
    for (int i = 0; i < creditos.getCantidad(); i++)
    {
        delete creditos.obtener(i);
    }
}

// Operador de igualdad (compara por ID)
bool Cancion::operator==(const Cancion& otra) const
{
    return id == otra.id;
}

// Operador menor que (ordenar por nombre)
bool Cancion::operator<(const Cancion& otra) const
{
    return nombre < otra.nombre;
}

// Operador de asignación
Cancion& Cancion::operator=(const Cancion& otra)
{
    if (this != &otra)
    {
        // Liberar memoria existente
        for (int i = 0; i < creditos.getCantidad(); i++)
        {
            delete creditos.obtener(i);
        }
        creditos.limpiar();

        // Copiar datos
        id = otra.id;
        nombre = otra.nombre;
        duracion = otra.duracion;
        ruta128 = otra.ruta128;
        ruta320 = otra.ruta320;
        reproducciones = otra.reproducciones;

        // Copiar créditos
        for (int i = 0; i < otra.creditos.getCantidad(); i++)
        {
            Credito* creditoOriginal = otra.creditos.obtener(i);
            Credito* creditoCopia = new Credito(*creditoOriginal);
            creditos.agregar(creditoCopia);
        }
    }
    return *this;
}

// Agregar crédito
void Cancion::agregarCredito(Credito* credito)
{
    if (credito != nullptr)
    {
        creditos.agregar(credito);
    }
}

// Obtener crédito por índice
Credito* Cancion::obtenerCredito(int indice) const
{
    if (indice >= 0 && indice < creditos.getCantidad())
    {
        return creditos.obtener(indice);
    }
    return nullptr;
}

// Obtener cantidad de créditos
int Cancion::getCantidadCreditos() const
{
    return creditos.getCantidad();
}

// Sobrecarga 1: obtenerRuta() - retorna ruta por defecto (128)
string Cancion::obtenerRuta() const
{
    return ruta128;
}

// Sobrecarga 2: obtenerRuta(int) - según calidad específica
string Cancion::obtenerRuta(int calidad) const
{
    if (calidad == 320)
    {
        return ruta320;
    }
    return ruta128;  // Por defecto 128
}

// Sobrecarga 3: obtenerRuta(bool) - según membresía
string Cancion::obtenerRuta(bool esPremium) const
{
    if (esPremium)
    {
        return ruta320;
    }
    return ruta128;
}

// Incrementar reproducciones
void Cancion::incrementarReproducciones()
{
    reproducciones++;
}

// Getters
int Cancion::getId() const
{
    return id;
}

string Cancion::getNombre() const
{
    return nombre;
}

int Cancion::getDuracion() const
{
    return duracion;
}

string Cancion::getRuta128() const
{
    return ruta128;
}

string Cancion::getRuta320() const
{
    return ruta320;
}

int Cancion::getReproducciones() const
{
    return reproducciones;
}

// Setters con validación
void Cancion::setId(int id) {
    // Validar que sea 9 dígitos
    if (id >= 100000000 && id <= 999999999)
    {
        this->id = id;
    }
}

void Cancion::setNombre(string nombre)
{
    if (!nombre.empty())
    {
        this->nombre = nombre;
    }
}

void Cancion::setDuracion(int duracion)
{
    if (duracion > 0) {
        this->duracion = duracion;
    }
}

void Cancion::setRuta128(string ruta)
{
    if (!ruta.empty()) {
        this->ruta128 = ruta;
    }
}

void Cancion::setRuta320(string ruta)
{
    if (!ruta.empty())
    {
        this->ruta320 = ruta;
    }
}

//
// Created by almar on 05/10/2026.
//

#include "Parque.h"

#include "Iterador.h"

/**
 * @brief Constructor por defecto de la clase Parque.
 * Inicializa el código de parque a 0 y el nombre a un espacio en blanco.
 */
Parque::Parque():codigo_parque(0),nombre_parque(" ") {}

/**
 * @brief Constructor parametrizado con un contenedor inicial de especies.
 * @param codigo Código identificador del parque.
 * @param nombre Nombre del parque.
 * @param especies Vector dinámico con los punteros a los árboles a incluir en el parque.
 */
Parque::Parque(int codigo, const string &nombre, const VDinamico<Arbol> &especies):
            codigo_parque(codigo),nombre_parque(nombre),contenedor(especies) {
}

/**
 * @brief Constructor parametrizado básico.
 * @param codigo Código identificador del parque.
 * @param nombre Nombre del parque.
 */
Parque::Parque(const int &codigo, const string &nombre) {
    this->codigo_parque = codigo;
    this->nombre_parque = nombre;
}

/**
 * @brief Destructor de la clase Parque.
 * Libera la memoria del contenedor de árboles.
 */
Parque::~Parque() {
    for ( int i = contenedor.getLogico(); i >= 0; i--) {
        contenedor.borrar(i);
    }
}

/**
 * @brief Obtiene el código del parque.
 * @return int Código identificador del parque.
 */
int Parque::getCodigoParque() const {
    return codigo_parque;
}

/**
 * @brief Establece el código del parque.
 * @param codigo Nuevo código identificador.
 */
void Parque::setCodigoParque(int codigo) {
    this->codigo_parque = codigo;
}

/**
 * @brief Obtiene el nombre del parque.
 * @return string Nombre del parque.
 */
string Parque::getNombreParque() const {
    return nombre_parque;
}

/**
 * @brief Establece el nombre del parque.
 * @param nombre Nuevo nombre para el parque.
 */
void Parque::setNombreParque(const string &nombre) {
    this->nombre_parque = nombre;
}

/**
 * @brief Inserta un nuevo árbol en el contenedor del parque.
 * @param arbol Puntero al árbol que se va a insertar.
 */
void Parque::insertarArbol(Arbol *arbol) {
    if(arbol) this->contenedor.insertar(*arbol);
}

/**
 * @brief Comprueba si existe en el parque un árbol con un determinado nombre común.
 * @param nombre Nombre común de la especie a buscar.
 * @return true Si existe al menos un árbol con ese nombre común, false en caso contrario.
 */
bool Parque::existeNComun(const string &nombre) {
    for(int i =0; i < this->contenedor.getLogico(); i++) {
        if(this->contenedor[i].getNombreComun() == nombre) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Busca y devuelve el árbol de mayor altura presente en el parque.
 * @return Arbol* Puntero al árbol más alto del parque.
 */
Arbol* Parque::arbolMasAlto() {

    Arbol *a = &this->contenedor[0];

    for(int i =1; i < this->contenedor.getLogico(); i++) {
        if(this->contenedor[i].get_altura() > a->get_altura()) {
            a= &this->contenedor[i];
        }
    }
    return a;
}

/**
 * @brief Devuelve el número de especies distintas presentes en el parque.
 * @return unsigned int Cantidad de especies únicas almacenadas.
 */
unsigned int Parque::contrarEspecies() {

    unsigned int num = this->contenedor.getLogico();
    int aux;

    for(int i =0; i < this->contenedor.getLogico(); i++) {
        aux =0;
        for(int j = i+1; j < this->contenedor.getLogico(); j++) {
            if(this->contenedor[i].getCodigoEspecie() == this->contenedor[j].getCodigoEspecie()) {
                aux++;
            }
        }
        num -= num - aux;
    }
    return num;
}

/**
 * @brief Devuelve el número de tipos de planta distintos presentes en el parque.
 * @return unsigned int Cantidad de tipos de planta únicos almacenados.
 */
unsigned int Parque::contarTipos() {
    unsigned int num = this->contenedor.getLogico();
    int aux;

    for(int i =0; i < this->contenedor.getLogico(); i++) {
        aux =0;
        for(int j = i+1; j < this->contenedor.getLogico(); j++) {
            if(this->contenedor[i].getTipoEspecie() == this->contenedor[j].getTipoEspecie()) {
                aux++;
            }
        }
        num -= num - aux;
    }
    return num;
}


/**
 * @brief Obtiene la referencia al contenedor dinámico con los árboles del parque.
 * @return VDinamico<Arbol>& Referencia al vector dinámico de punteros a objetos Arbol.
 */
VDinamico<Arbol>& Parque::get_contenedor() {return this->contenedor; }


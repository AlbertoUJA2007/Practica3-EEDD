//
// Created by almar on 05/10/2026.
//

#include "Parque.h"

Parque::Parque():codigo_parque(0),nombre_parque(" ") {}

Parque::Parque(int codigo, const string &nombre, const VDinamico<Arbol*> &especies):
            codigo_parque(codigo),nombre_parque(nombre),contenedor(especies) {
}

Parque::Parque(int codigo, const string &nombre) {
    this->codigo_parque = codigo;
    this->nombre_parque = nombre;
}

Parque::~Parque() {
    for ( int i = contenedor.getLogico(); i >= 0; i--) {
        contenedor.borrar(i);
    }
}

int Parque::getCodigoParque() const {
    return codigo_parque;
}

void Parque::setCodigoParque(int codigo) {
    this->codigo_parque = codigo;
}

string Parque::getNombreParque() const {
    return nombre_parque;
}

void Parque::setNombreParque(const string &nombre) {
    this->nombre_parque = nombre;
}

void Parque::insertarArbol(Arbol *arbol) {
    this->contenedor.insertar(arbol);
}

bool Parque::existeNComun(const string &nombre) {
    for(int i =0; i < this->contenedor.getLogico(); i++) {
        if(this->contenedor[i]->getNombreComun() == nombre) {
            return true;
        }
    }
    return false;
}

Arbol* Parque::arbolMasAlto() {

    Arbol *a = this->contenedor[0];

    for(int i =1; i < this->contenedor.getLogico(); i++) {
        if(this->contenedor[i]->getAltura() > a->getAltura()) {
            a= this->contenedor[i];
        }
    }
    return a;
}


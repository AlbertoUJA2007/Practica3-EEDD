//
// Created by almar on 05/10/2026.
//

#include "Parque.h"

Parque::Parque():codigo_parque(0),nombre_parque(" ") {}

Parque::Parque(int codigo, const string &nombre, const VDinamico<Especie*> &especies):
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

void Parque::insertarEspecie(Especie *esp) {
    contenedor.insertar(esp,contenedor.getLogico());
}

bool Parque::existeNComun(const string &nombre) {
    for (int i = 0; i < contenedor.getLogico(); i++) {
        if (contenedor[i]->get_nombre_comun() == nombre) {
            return true;
        }
    }
    return false;
}

bool Parque::existeNCientifico(const string &nombre) {
    for (int i = 0; i < contenedor.getLogico(); i++) {
        if (contenedor[i]->get_nombre_cientifico() == nombre) {
            return true;
        }
    }
    return false;
}

unsigned int Parque::getCantEspecies() {
    return this->contenedor.getLogico();
}

VDinamico<Especie *>& Parque::get_contenedor() {
    return this->contenedor;
}

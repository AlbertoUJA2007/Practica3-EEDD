//
// Created by almar on 05/10/2026.
//

#ifndef PRACTICA2_EEDD_PARQUE_H
#define PRACTICA2_EEDD_PARQUE_H
#include <iostream>

#include "Arbol.h"
#include "Especie.h"
using namespace std;

class Parque {
private:
    int codigo_parque;                  //Id de parque
    string nombre_parque;
    VDinamico<Arbol*> contenedor;     // Especies que hay en el parque

public:
    Parque();
    Parque(int codigo,const string &nombre,const VDinamico<Arbol*> &especies);
    Parque(int codigo, const string &nombre);
    ~Parque();

    int getCodigoParque()const;
    void setCodigoParque(int codigo);
    string getNombreParque()const;
    void setNombreParque(const string &nombre);

    void insertarArbol(Arbol *arbol);
    bool existeNComun(const string &nombre);
    Arbol* arbolMasAlto();

    unsigned int contrarEspecies();

    unsigned int contarTipos();


    VDinamico<Arbol*>& get_contenedor();
};


#endif //PRACTICA2_EEDD_PARQUE_H
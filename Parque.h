//
// Created by almar on 05/10/2026.
//

#ifndef PRACTICA2_EEDD_PARQUE_H
#define PRACTICA2_EEDD_PARQUE_H
#include <iostream>
#include "Especie.h"
using namespace std;

class Parque {
private:
    int codigo_parque;                  //Id de parque
    string nombre_parque;
    VDinamico<Especie*> contenedor;     // Especies que hay en el parque

public:
    Parque();
    Parque(int codigo,const string &nombre,const VDinamico<Especie*> &especies);
    Parque(int codigo, const string &nombre);
    ~Parque();

    int getCodigoParque()const;
    void setCodigoParque(int codigo);
    string getNombreParque()const;
    void setNombreParque(const string &nombre);

    void insertarEspecie(Especie *esp);
    bool existeNComun(const string &nombre);
    bool existeNCientifico(const string &nombre);

    unsigned int getCantEspecies();

    VDinamico<Especie*>& get_contenedor();
};


#endif //PRACTICA2_EEDD_PARQUE_H
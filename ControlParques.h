//
// Created by almar on 05/10/2026.
//

#ifndef PRACTICA2_EEDD_CONTROLPARQUES_H
#define PRACTICA2_EEDD_CONTROLPARQUES_H
#include "ListaDE.h"
#include "Parque.h"

class ControlParques {
private:
    ListaDE<Parque> parques;
    VDinamico<Especie*> variantes;
public:
    ControlParques(const string &nomFichEspecies, const string &nomFichParques);    //Hay que cargar los ficheros aqui
    ~ControlParques();

    void asignarEspecieParque( Especie &e,  Parque &p);
    int contarEspecieParque(const string &nombre);
    Parque& buscarParque(const string &nombre);
    VDinamico<Especie>& listadoEspecieSubNombre(const string &cadena);
};


#endif //PRACTICA2_EEDD_CONTROLPARQUES_H
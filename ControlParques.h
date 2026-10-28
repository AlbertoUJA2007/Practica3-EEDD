//
// Created by almar on 05/10/2026.
//

#ifndef PRACTICA2_EEDD_CONTROLPARQUES_H
#define PRACTICA2_EEDD_CONTROLPARQUES_H
#include "AVL.h"
#include "ListaDE.h"
#include "Parque.h"

class ControlParques {
private:
    ListaDE<Parque> parques;
    VDinamico<Especie*> variantes;
    AVL<Arbol> arboles;

public:
    ControlParques(const string &nomFichEspecies, const string &nomFichParques, const string &nomFiceroArbol);    //Hay que cargar los ficheros aqui
    ~ControlParques();


    Parque *buscarParque(const string &nombre);
    VDinamico<Especie>& listadoEspecieSubNombre(const string &cadena);
    VDinamico<Especie*>& getVariantes();
    ListaDE<Parque>& getparques();
    AVL<Arbol>& getArboles();


    Arbol *buscarArbol(const string &asnum);
    void eliminarParque(const string &nombre);
    VDinamico<Arbol>* listaArbolesParque(const string &nombre_parque);

    VDinamico<Arbol*>& buscarArbolesRango();

    Arbol *getArbolMasAlto();

    unsigned int contarEspecies(const string &nombreparque);

    unsigned int contarTipos();

};


#endif //PRACTICA2_EEDD_CONTROLPARQUES_H
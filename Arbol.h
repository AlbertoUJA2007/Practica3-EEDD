
#ifndef PRACTICA2_EEDD_ARBOL_H
#define PRACTICA2_EEDD_ARBOL_H
#include <iostream>
#include <Especie.h>
using namespace std;

template <class T>
class Arbol {
private:
    string assetnum;
    int num_parque;
    int num_distrito;
    string nombre_distrito;
    int num_barrio;
    string nombre_barrio;
    double x;
    double y;
    float perimetro;
    float altura;

    Especie *especie_arbol;    //Cada arbol tiene 1 sola especie
public:
    Arbol();
    Arbol(const string &assetnum, int num_parque, int num_distrito,
        const string &nombre_distrito, int num_barrio, const string &nombre_barrio,
        double x, double y, float perimetro, float altura);
    Arbol(const Arbol &orig);
    ~Arbol();

    void setEspecie(const Especie &e);
    string getCodigoEspecie() const;
    string getTipoEspecie() const;
    string getNombreComun() const;
};


#endif //PRACTICA2_EEDD_ARBOL_H
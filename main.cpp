#include <iostream>

#include <ctime>
#include "AVL.h"
#include "ControlParques.h"
#include "LectorCSV.h"
#include "ListaDE.h"
#include "ListaDE.h"
#include "Parque.h"

template <class T>
void mostrarLista(ListaDE<T> l)
{
    for (Iterador<T> it = l.iterador(); !it.fin(); it.siguiente())
    {
        std::cout << std::to_string(it.dato()) << " ";
    }
    cout << endl;
}


Iterador<Parque> buscaParque(ListaDE<Parque>& lista, const string &nombre)
{
    Iterador<Parque> it = lista.iterador();
    for (it; !it.fin(); it.siguiente())
    {
        if (it.dato().getNombreParque() == nombre)
        {
            return it;
        }
    }
    return it;
}

bool buscaEspecieNbrComun(VDinamico<Especie*>& vector, const string &nombreComun)
{
    unsigned int  n = vector.getLogico();
    for (int i = 0; i < n; ++i)
    {
        if (vector[i]->get_nombre_comun() == nombreComun)
        {
            return true;
        }
    }
    return false;
}

bool buscaEspecieNbrCientif(VDinamico<Especie*>& vector, string nombreCentif)
{
    int n = vector.getLogico();
    for (int i = 0; i < n; ++i)
    {
        string s = vector[i]->get_nombre_cientifico();
        if (vector[i]->get_nombre_cientifico() == nombreCentif)
        {
            return true;
        }
    }
    return false;
}

const string RUTA_ESPECIES = "arbolado-especies.csv";
const string RUTA_PARQUES = "parques.csv";
const string RUTA_ARBOLES = "arboladoMadrid.csv";

void prueba1() {
    ControlParques cp(RUTA_ESPECIES, RUTA_PARQUES, RUTA_ARBOLES);

    //Variables fuera del bucle por eficiencia
   /* VDinamico<Especie*> especies = cp.getVariantes();
    ListaDE<Parque>* parques = &cp.getparques();
    VDinamico<Arbol> arboles = *cp.getArboles().recorreInorden_v();

    VDinamico<string> aux;


    //GUARDAMOS EN UN VECTOR AUXILIAR los identificadores de 500 arboles
    for(int i =0; i < arboles.getLogico() && aux.getLogico() < 500; i+=250 ) {
        aux.insertar(arboles[i].getCodigoEspecie());
    }

    //BUSCAMOS EL ASSETNUM DE ESOS 500 ARBOLES EN EL AVL
    clock_t inicio = clock();

    for(int i =0; i < aux.getLogico(); i++) {
        cp.buscarParque(aux[i]);
    }

    clock_t fin = clock();

    double tiempo_segundos = double(fin - inicio) / CLOCKS_PER_SEC;
    std::cout << "Tiempo: " << tiempo_segundos << " segundos" << std::endl;*/
}

void prueba2() {

}
int main()
{
    prueba1();
    //prueba2();
}

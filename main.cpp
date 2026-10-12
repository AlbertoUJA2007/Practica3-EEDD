#include <iostream>
#include <conio.h>
#include "ControlParques.h"
#include "LectorCSV.h"
#include "ListaDE.h"
#include "ListaDE.h"
#include "Parque.h"

template <class T>
void mostrarLista(ListaDE<T> l)
{
    for (Iterador<T> it = l.iterador(); it.haySiguiente(); it.siguiente())
    {
        std::cout << std::to_string(it.dato()) << "  ";
    }
    cout << endl;
}


Iterador<Parque> buscaParque(ListaDE<Parque>& lista, string nombre)
{
    Iterador<Parque> it = lista.iterador();
    for (it; it.haySiguiente(); it.siguiente())
    {
        if (it.dato().getNombreParque() == nombre)
        {
            return it;
        }
    }
    return it;
}

bool buscaEspecieNbrComun(VDinamico<Especie*>& vector, string nombreComun)
{
    int n = vector.getLogico();
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

const string RUTA_ESPECIES = "data/arbolado-especies.csv";
const string RUTA_PARQUES = "data/parques.csv";

void programa1() {
    cout << "PROGRAMA DE PRUEBA 1" << endl;

    //Crear la lista vacía
    ListaDE<int> lista;

    cout<<"Insetar al final del 101 al 200"<<endl;

    for (int i = 101; i <= 200; ++i)
    {
        lista.insertaFin(i);
    }
    mostrarLista(lista);

    cout<<endl<<"Insertar por el comienzo del 1 al 98"<<endl;
    for (int i = 98; i >= 1; --i)
    {
        lista.insertaInicio(i);
    }
    mostrarLista(lista);

    cout<<endl<<"insertar el dato 100 delante del 101"<<endl;
    Iterador<int> itint = lista.iterador();
    while (itint.dato() != 101)
    {
        itint.siguiente();
    }
    lista.inserta(itint, 100);
    mostrarLista(lista);

    itint = lista.iterador();
    while (itint.dato() != 98)
    {
        itint.siguiente();
    }
    lista.inserta(itint, 99);
    mostrarLista(lista);

    cout<<endl<<"Borrar los 10 primeros y los 10 últimos"<<endl;
    for (int i = 0; i < 10; ++i)
    {
        lista.borraInicio();
        lista.borraFinal();
    }
    mostrarLista(lista);

    cout<<endl<<"PULSAR CUALQUIER TECLA PARA CONTINUAR"<<endl;
    getch();
}
void programa2() {
    /* cout << "PROGRAMA DE PRUEBA 2" << endl;
    ControlParques cp(RUTA_ESPECIES, RUTA_PARQUES);

    //Variables fuera del bucle por eficiencia
    VDinamico<Especie>* especies = &cp.get_varieties();
    ListaDE<Parque>* parques = &cp.get_parks();

    for (int i = 0; i < especies->getLogico(); ++i)
    {
        Iterador<Parque> it = parques->iterador();
        Especie& esp = (*especies)[i];
        int tipo = esp.get_tipo_planta();
        for (it; !it.fin(); it.avanza())
        {
            Parque& pq = it.dato();
            int resto = pq.getCodigoParque() % 2;

            //parques con codigo par
            if ((tipo == ARBUSTO || tipo == CONIFERA || tipo == PALMACEA ||
                tipo == HERB_PERENNES || tipo == FRONDOSA) && (resto == 0))
            {
                pq.insertaEspecie(&esp);
                //Parques con codigo impar
            }
            else if ((tipo == TAPIZANTE_TREPADORA || tipo == CACTACEA_SUCULENTA ||
                tipo == SUBTROPICAL_TROPICAL ||
                tipo == HERB_ANUAL || tipo == HERB_ANUALES) && (resto == 1))
            {
                pq.insertaEspecie(&esp);
            }
        }
    }

    cout << endl << "ASIGNACIÓN DE ESPECIES A LOS PARQUES" << endl;
    for (Iterador<Parque> it = parques->iterador(); !it.fin(); it.avanza())
    {
        cout << "  Codigo: " << to_string(it.dato().getCodigoParque()) << " nombre: " << it.dato().
            getNombreParque() << " total especies: " << to_string(
                it.dato().()) << endl;
    }


    cout << endl << "BUSCAR EN PARQUE PRINCESA LEONOR LOS NOMBRES COMUNES EUCALIPTO ROJO Y ARCE DE SIERRA" << endl;
    Parque& princLeonor = buscaParque(cp.get_parks(), "PARQUE PRINCESA LEONOR").dato();
    //Debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contains(), "Eucalipto rojo"))
    {
        cout << "  Encontrado Eucalipto rojo" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Eucalipto rojo" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contains(), "Arce de sierra"))
    {
        cout << "  Encontrado Arce de sierra" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Arce de sierra" << endl;
    }

    cout << endl << "BUSCAR EN PARQUE MADRID RIO LOS NOMBRES CIENTÍFICOS HEBE FLORIBUNDA Y ANANAS COMOSA" << endl;
    Parque& madridRio = buscaParque(cp.get_parks(), "PARQUE MADRID RIO").dato();
    //No debe estar
    if (buscaEspecieNbrCientif(madridRio.get_contains(), "Hebe floribunda"))
    {
        cout << "  Encontrado Hebe floribunda" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Hebe floribunda" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(madridRio.get_contains(), "Ananas comosa"))
    {
        cout << "  Encontrado Ananas comosa" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Ananas comosa" << endl;
    }

    cout << endl << "BUSCAR PARQUES JUAN CARLOS III Y VIVERO DE MIGAS CALIENTES" << endl;
    //No debe estar
    Iterador<Parque> it = buscaParque(cp.get_parks(), "JUAN CARLOS III");
    if (it.fin())
    {
        cout << "  No se ha encontrado parque JUAN CARLOS III" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it.dato().getCodigoParque()) <<" nombre: "<< it.dato().getNombreParque()<< endl;
    }

    Iterador<Parque> it2 = buscaParque(cp.get_parks(), "VIVERO DE MIGAS CALIENTES");
    //Sí debe estar
    if (it.fin())
    {
        cout << "  No se ha encontrado parque VIVERO DE MIGAS CALIENTES" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it.dato().getCodigoParque()) <<" nombre: "<< it.dato().getNombreParque()<< endl;
    }

    cout<< endl<<"BUSCAR ESPECIES CON LA SUBCADENA ROSA EN SU NOMBRE CIENTÍFICO"<<endl;
    for (int i =0; i < especies->getLogico(); ++i)
    {
        string ncientif = (*especies)[i].get_nombre_cientifico();
        if (ncientif.find("rosa") != string::npos)
        {
            (*especies)[i].mostrarInfo();
        }
    }

    cout<< endl<<"CONTAR CUÁNTOS PARQUES TIENEN LA ESPECIE CON NOMBRE COMÚN ABETO"<<endl;
    it = cp.get_parks().iterador();
    int total = 0;
    for (it; !it.fin(); it.avanza())
    {
       VDinamico<Especie*>  esp = it.dato().get_contains();
        for (int i =0; i < esp.getLogico(); ++i)
        {
            string nombreComun = esp[i]->get_nombre_comun();
            if (nombreComun.find("Abeto") != string::npos)
            {
                ++total;
                break;
            }
        }
    }
    cout<<"  Total: "<<total<<endl;*/
}
int main()
{

    programa1();





    return 0;
}

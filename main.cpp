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

void programa1() {
    cout << "PROGRAMA DE PRUEBA 1" << endl;

    //Crear la lista vacía
    ListaDE<int> lista;

    cout<<"Insetar al final del 101 al 200"<<endl;

    for (int i = 101; i <= 200; i++)
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

    cout<<endl<<"insertar el dato 99 detras del 98"<<endl;
    itint = lista.iterador();
    while (itint.dato() != 98)
    {
        itint.siguiente();
    }
    itint.siguiente();
    lista.inserta(itint, 99);
    mostrarLista(lista);

    cout<<endl<<"Borrar los 10 primeros y los 10 ultimos"<<endl;
    for (int i = 0; i < 10; ++i)
    {
        lista.borraInicio();
        lista.borraFinal();
    }
    mostrarLista(lista);

    cout<<endl<<"Borrar todos los multiplos de 10"<<endl;
    itint = lista.iterador();
    while (itint.haySiguiente()) {

        if (itint.dato()%10==0) {
            Iterador<int> p = itint;
            itint.siguiente();
            lista.borra(p);
        }
        itint.siguiente();
    }
    if (itint.dato()%10==0) {
        Iterador<int> p = itint;
        lista.borra(p);
    }
    mostrarLista(lista);

    cout<<endl<<"PULSAR CUALQUIER TECLA PARA CONTINUAR"<<endl;
    getch();
}
void programa2() {
     cout << "PROGRAMA DE PRUEBA 2" << endl;
    ControlParques cp(RUTA_ESPECIES, RUTA_PARQUES);

    //Variables fuera del bucle por eficiencia
    VDinamico<Especie*> especies = cp.getVariantes();
    ListaDE<Parque>* parques = &cp.getparques();

    for (int i = 0; i < especies.getLogico(); ++i)
    {
        Iterador<Parque> it = parques->iterador();
        Especie *esp = (especies)[i];
        TipoPlanta tipo = esp->get_tipo_planta();
        for (it; !it.fin(); it.siguiente())
        {
            Parque& pq = it.dato();
            int resto = pq.getCodigoParque() % 2;

            //parques con codigo par
            if ((tipo == TipoPlanta::ARBUSTO || tipo == TipoPlanta::CONIFERA || tipo == TipoPlanta::PALMACEA ||
                tipo == TipoPlanta::HERB_PERENNES || tipo == TipoPlanta::FRONDOSA) && (resto == 0))
            {
                pq.insertarEspecie(esp);

            }//Parques con codigo impar
            else if ((tipo == TipoPlanta::TAPIZANTE_TREPADORA || tipo == TipoPlanta::CACTACEA_SUCULENTA ||
                tipo == TipoPlanta::SUBTROPICAL_TROPICAL ||
                tipo == TipoPlanta::HERB_ANUAL || tipo == TipoPlanta::HERB_ANUALES) && (resto == 1))
            {
                pq.insertarEspecie(esp);
            }
        }
    }
    cout << "Cantidad de especies " << especies.getLogico() << endl;
    cout << "Cantidad de parques " << parques->tam() << endl;

    cout << endl << "ASIGNACIÓN DE ESPECIES A LOS PARQUES" << endl;
    for (Iterador<Parque> it = parques->iterador(); !it.fin(); it.siguiente())
    {
        cout << "  Codigo: " << to_string(it.dato().getCodigoParque()) << " nombre: " << it.dato().
            getNombreParque() << " total especies: " << to_string(
                it.dato().getCantEspecies()) << endl;
    }


    cout << endl << "BUSCAR EN PARQUE PRINCESA LEONOR LOS NOMBRES COMUNES EUCALIPTO ROJO Y ARCE DE SIERRA" << endl;
    Parque& princLeonor = buscaParque(cp.getparques(), "PARQUE PRINCESA LEONOR").dato();
    //Debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contenedor(), "Eucalipto rojo"))
    {
        cout << "  Encontrado Eucalipto rojo" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Eucalipto rojo" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contenedor(), "Arce de sierra"))
    {
        cout << "  Encontrado Arce de sierra" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Arce de sierra" << endl;
    }

    cout << endl << "BUSCAR EN PARQUE MADRID RIO LOS NOMBRES CIENTÍFICOS HEBE FLORIBUNDA Y ANANAS COMOSA" << endl;
    Parque& madridRio = buscaParque(cp.getparques(), "PARQUE MADRID RIO").dato();
    //No debe estar
    if (buscaEspecieNbrCientif(madridRio.get_contenedor(), "Hebe floribunda"))
    {
        cout << "  Encontrado Hebe floribunda" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Hebe floribunda" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(madridRio.get_contenedor(), "Ananas comosa"))
    {
        cout << "  Encontrado Ananas comosa" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Ananas comosa" << endl;
    }

    cout << endl << "BUSCAR PARQUES JUAN CARLOS III Y VIVERO DE MIGAS CALIENTES" << endl;
    //No debe estar
    Iterador<Parque> it = buscaParque(cp.getparques(), "JUAN CARLOS III");
    if (it.fin())
    {
        cout << "  No se ha encontrado parque JUAN CARLOS III" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it.dato().getCodigoParque()) <<" nombre: "<< it.dato().getNombreParque()<< endl;
    }

    Iterador<Parque> it2 = buscaParque(cp.getparques(), "VIVERO DE MIGAS CALIENTES");
    //Sí debe estar
    if (it2.fin())
    {
        cout << "  No se ha encontrado parque VIVERO DE MIGAS CALIENTES" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it2.dato().getCodigoParque()) <<" nombre: "<< it2.dato().getNombreParque()<< endl;
    }

    cout<< endl<<"BUSCAR ESPECIES CON LA SUBCADENA ROSA EN SU NOMBRE CIENTÍFICO"<<endl;
    int cant=0;
    for (int i =0; i < especies.getLogico(); ++i)
    {
        string ncientif = (especies)[i]->get_nombre_cientifico();
        if (ncientif.find("rosa") != string::npos)
        {
            (especies)[i]->mostrarInfo();
            cant++;
        }
    }
    cout << "Cantidad encontrada de parques que tiene ROSA en su nombre cientifico" << cant << endl;

    cout<< endl<<"CONTAR CUÁNTOS PARQUES TIENEN LA ESPECIE CON NOMBRE COMÚN ABETO"<<endl;
    it = cp.getparques().iterador();
    int total = 0;
    for (it; !it.fin(); it.siguiente())
    {
       VDinamico<Especie*>  esp = it.dato().get_contenedor();
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
    cout<<"  Total: "<<total<<endl;

    cout << "---------------------" << endl;
    cout << "Trabajo por parejas" << endl;

    cout << "Elimando parque VIVERO DE MIGAS CALIENTES" << endl;
    cp.eliminarParque("VIVERO DE MIGAS CALIENTES");
    cout << "Parque eliminado "<< endl;
    cout << "Buscando el parque en la lista" << endl;

    Parque *p = &cp.buscarParque("VIVERO DE MIGAS CALIENTES");

    if(!p) cout << "El parque ya no existe en la lista" << endl;
    else cout << "El parque sigue en la lista" << endl;
}


int main()
{
    programa1();

    programa2();
    return 0;
}

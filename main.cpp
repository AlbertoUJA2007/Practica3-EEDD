
#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "ControlParques.h"
#include "Arbol.h"
#include "Especie.h"
#include "AVL.h"

using namespace std;

float leerMedida(std::string campo)
{
    std::replace(campo.begin(), campo.end(), ',', '.');

    return campo.empty() ? -1.0f : std::stof(campo);
}

Arbol& leerArbol(const std::string &linea)
{
    std::stringstream registro(linea);
    std::string campos[12];

    for (unsigned int i = 0; i < 12; ++i)
    {
        if (!std::getline(registro, campos[i], ';'))
        {
            if (i != 11 || linea.empty() || linea.back() != ';')
                throw std::runtime_error("Registro de arbol incompleto");
        }
    }

    std::replace(campos[6].begin(), campos[6].end(), ',', '.');
    std::replace(campos[7].begin(), campos[7].end(), ',', '.');

    Arbol *a  = new  Arbol(
        campos[0],
        std::stoi(campos[1]),
        std::stoi(campos[2]),
        campos[3],
        std::stoi(campos[4]),
        campos[5],
        std::stod(campos[6]),
        std::stod(campos[7]),
        leerMedida(campos[10]),
        leerMedida(campos[11]),
        new Especie(campos[10], campos[11]));
    return *a;
}

void cargarAVL(const std::string &ruta, AVL<Arbol> &avl)
{
    std::ifstream fichero(ruta);

    if (!fichero.is_open())
        throw std::runtime_error("No se puede abrir: " + ruta);

    std::string linea;
    std::getline(fichero, linea); // Saltar cabecera.

    while (std::getline(fichero, linea))
    {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        if (linea.empty())
            continue;

        Arbol arbol = leerArbol(linea);
      //  cout << "insertado " << arbol.getAssetNum() << endl;
        if (!avl.inserta(arbol))
            throw std::runtime_error(
                "Identificador duplicado: " + arbol.getAssetNum());
    }
}

void cargarVector(
    const std::string &ruta, VDinamico<Arbol> &arboles)
{
    std::ifstream fichero(ruta);

    if (!fichero.is_open())
        throw std::runtime_error("No se puede abrir: " + ruta);

    std::string linea;
    std::getline(fichero, linea); // Saltar cabecera.

    while (std::getline(fichero, linea))
    {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        if (linea.empty())
            continue;

        Arbol arbol = leerArbol(linea);
       // cout << "arbol: " << Especie::tptostring(arbol.getTipoEspecie()) << endl;;
        arboles.insertar(arbol);
    }
}

void prueba1() {
      std::cout << "PROGRAMA DE PRUEBA I\n"
                  << "-------------------\n\n";

        const std::string ruta = "arboladoMadrid.csv";

        AVL<Arbol> avl;
        VDinamico<Arbol> arboles;
        VDinamico<std::string> identificadores;

        // 1. Leer los árboles e insertarlos en el AVL.
        cargarAVL(ruta, avl);

        // 2. Leer nuevamente los árboles y almacenarlos en el vector.
        cargarVector(ruta, arboles);

        std::cout << "Arboles en el AVL: "
                  << avl.getNumElementos() << '\n';

        std::cout << "Arboles en el vector: "
                  << arboles.getLogico() << '\n';

        if (avl.getNumElementos() != arboles.getLogico())
            throw std::runtime_error(
                "Las estructuras contienen cantidades diferentes");

        // 3. Seleccionar 500 identificadores: posiciones
        // 0, 250, 500, ..., 124750.
        const unsigned int numeroBusquedas = 500;
        const unsigned int salto = 250;

        if (arboles.getLogico() <= (numeroBusquedas - 1) * salto)
            throw std::runtime_error(
                "No hay suficientes arboles para seleccionar la muestra");

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            std::string id = arboles[i * salto].getAssetNum();
            identificadores.insertar(id);
        }

        // Preparar las claves antes de empezar a medir.
        VDinamico<Arbol> claves;

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            Arbol clave;
            clave.setAsNum(identificadores[i]);
            claves.insertar(clave);
        }

        // 4. Buscar los 500 árboles en el AVL.
        unsigned int encontradosAVL = 0;

        auto inicioAVL = std::chrono::steady_clock::now();

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            if (avl.buscaRecursiva(claves[i]) != nullptr)
                ++encontradosAVL;
        }

        auto finAVL = std::chrono::steady_clock::now();

        // 5. Buscar linealmente los mismos árboles en el vector.
        unsigned int encontradosVector = 0;

        auto inicioVector = std::chrono::steady_clock::now();

        for (unsigned int i = 0; i < numeroBusquedas; ++i)
        {
            for (unsigned int j = 0; j < arboles.getLogico(); ++j)
            {
                if (arboles[j] == claves[i])
                {
                    ++encontradosVector;
                    break;
                }
            }
        }

        auto finVector = std::chrono::steady_clock::now();

        // 6. Mostrar los resultados y los tiempos en milisegundos.
        double tiempoAVL =
            std::chrono::duration<double, std::milli>(
                finAVL - inicioAVL)
                .count();

        double tiempoVector =
            std::chrono::duration<double, std::milli>(
                finVector - inicioVector)
                .count();

        std::cout << "\nEncontrados en AVL: "
                  << encontradosAVL << '/' << numeroBusquedas;

        std::cout << "\nEncontrados en vector: "
                  << encontradosVector << '/' << numeroBusquedas;

        std::cout << "\n\nTiempo AVL: "
                  << tiempoAVL << " ms";

        std::cout << "\nTiempo busqueda lineal: "
                  << tiempoVector << " ms\n";

        if (encontradosAVL != numeroBusquedas ||
            encontradosVector != numeroBusquedas)
        {
            throw std::runtime_error(
                "Alguna busqueda no ha encontrado el arbol esperado");
        }

        if (tiempoAVL < tiempoVector)
            std::cout << "El AVL ha sido mas rapido en esta medicion.\n";
        else
            std::cout << "El AVL no ha sido mas rapido en esta medicion.\n";

        // 7. Mostrar la altura.
        std::cout << "\nAltura del AVL: "
                  << avl.altura() << '\n';

        // 8. Mostrar los 100 primeros árboles en inorden.
        VDinamico<Arbol> *ordenados = avl.recorreInorden_v();

        std::cout << "\nPrimeros 100 arboles en inorden:\n";

        for (unsigned int i = 0;
             i < 100 && i < ordenados->getLogico(); ++i)
        {
            Arbol arbol = (*ordenados)[i];

            std::cout << i + 1
                      << ". ID: " << arbol.getAssetNum() << endl;
        }

}
/*
void prueba2() {
     std::cout << "\nPROGRAMA DE PRUEBA II\n"
                  << "-------------------\n\n";

        ControlParques control(
            "./data/arbolado-especies.csv",
            "./data/parques.csv",
            "./data/arboladoMadrid.csv");

        std::cout << "\nEJERCICIO 5: BUSQUEDA DE ARBOLES\n";
        std::cout << "-------------------------------\n";

        const std::string ids[] = {
            "9850684", "5702331", "5697360", "0000000"};

        for (const std::string &id : ids)
        {
            Arbol *arbol = control.buscarArbol(id);

            if (arbol == nullptr)
            {
                std::cout << "\nNo existe el arbol con identificador "
                          << id << '\n';
                continue;
            }

            std::cout << "\nIdentificador: " << arbol->getAssetNum()
                      << "\nCodigo de parque: " << arbol->getNumParque()
                      << "\nNombre comun: " << arbol->getNombreComun()
                      << "\nNombre cientifico: " << arbol->getNbreCientifico()
                      << "\nTipo de planta: " << arbol->getTipo()
                      << '\n';
        }

        std::cout << "\nEJERCICIO 6: ARBOLES DEL RETIRO\n";
        std::cout << "-------------------------------\n";

        VDinamico<Arbol *> arbolesRetiro =
            control.listaArbParque("JARDINES DEL BUEN RETIRO");

        std::cout << "Numero de arboles: "
                  << arbolesRetiro.tamLog() << '\n';

        for (unsigned int i = 0;
             i < 10 && i < arbolesRetiro.tamLog(); ++i)
        {
            Arbol *arbol = arbolesRetiro[i];

            std::cout << "\nIdentificador: " << arbol->getAssetNum()
                      << "\nNombre comun: " << arbol->getNombreComun()
                      << "\nNombre cientifico: " << arbol->getNbreCientifico()
                      << "\nTipo de planta: " << arbol->getTipo()
                      << '\n';
        }

        std::cout << "\nEJERCICIO 7: COMPROBACION DE OBJETOS\n";
        std::cout << "-------------------------------\n";

        unsigned int comprobados = 0;
        unsigned int correctos = 0;

        for (unsigned int i = 0;
             i < 10 && i < arbolesRetiro.tamLog(); ++i)
        {
            Arbol *listado = arbolesRetiro[i];
            Arbol *encontrado = control.buscarArbol(listado->getAssetNum());

            bool coincide = (encontrado == listado);

            ++comprobados;

            if (coincide)
                ++correctos;

            std::cout << "Arbol " << listado->getAssetNum()
                      << ": " << (coincide ? "CORRECTO" : "ERROR")
                      << '\n';
        }

        std::cout << "Comprobaciones correctas: "
                  << correctos << '/' << comprobados << '\n';

        std::cout << "\nEJERCICIO 8: ESPECIES POR PARQUE\n";
        std::cout << "-------------------------------\n";

        const std::string nombresParques[] = {
            "JARDINES DEL BUEN RETIRO",
            "PARQUE DEL OESTE",
            "QUINTA DE LOS MOLINOS"};

        unsigned int recuentosEspecies[3];
        unsigned int maximoEspecies = 0;

        for (unsigned int i = 0; i < 3; ++i)
        {
            recuentosEspecies[i] = control.contarEspecies(nombresParques[i]);

            std::cout << nombresParques[i] << ": "
                      << recuentosEspecies[i] << " especies distintas\n";

            if (recuentosEspecies[i] > maximoEspecies)
                maximoEspecies = recuentosEspecies[i];
        }

        std::cout << "\nParques con mayor numero de especies distintas:\n";

        for (unsigned int i = 0; i < 3; ++i)
        {
            if (recuentosEspecies[i] == maximoEspecies)
                std::cout << nombresParques[i]
                          << " (" << maximoEspecies << " especies)\n";
        }

        std::cout << "\nEJERCICIO 9: TIPOS DE PLANTA POR PARQUE\n";
        std::cout << "-------------------------------\n";

        for (const std::string &nombre : nombresParques)
        {
            Parque *parque = control.buscarParque(nombre);

            if (parque == nullptr)
            {
                std::cout << "No existe el parque " << nombre << '\n';
                continue;
            }

            std::cout << nombre << ": "
                      << parque->contarTipos()
                      << " tipos de planta distintos\n";
        }

        std::cout << "\nEJERCICIO 10: ESPECIES PRESENTES EN EL RETIRO\n";
        std::cout << "-------------------------------\n";

        Parque *retiro = control.buscarParque("JARDINES DEL BUEN RETIRO");

        if (retiro == nullptr)
        {
            std::cout << "No existe el parque JARDINES DEL BUEN RETIRO\n";
        }
        else
        {
            const std::string especies[] = {
                "Pino piñonero", "Olivilla"};

            for (const std::string &nombre : especies)
            {
                bool existe = retiro->existeNbreCom(nombre);

                std::cout << nombre << ": "
                          << (existe ? "PRESENTE" : "AUSENTE")
                          << '\n';
            }
        }

        std::cout << "\nEJERCICIO 11: TIPOS DE PLANTA EN TODOS LOS PARQUES\n";
        std::cout << "-------------------------------\n";

        std::cout << "Numero de tipos de planta distintos: "
                  << control.contarTipos() << '\n';

        std::cout << "\nEJERCICIO 12: ARBOL MAS ALTO\n";
        std::cout << "-------------------------------\n";

        Arbol *masAlto = control.getArbolMasAlto();

        if (masAlto == nullptr)
        {
            std::cout << "No hay arboles con altura conocida.\n";
        }
        else
        {
            std::cout << "Identificador: " << masAlto->getAssetNum()
                      << "\nAltura: " << masAlto->get_altura() << " m"
                      << "\nEspecie: " << masAlto->getNombreComun()
                      << " (" << masAlto->getNbreCientifico() << ")\n";
        }

        // Ejercicio por parejas
        std::cout << "\nEJERCICIO POR PAREJAS: BUSQUEDA POR INTERVALO\n";
        std::cout << "-------------------------------\n";

        VDinamico<Arbol *> resultadoRango =
            control.buscarArbolesRango("5700000", "5709999");

        std::cout << "Numero de arboles encontrados: "
                  << resultadoRango.getLogico() << '\n';

        for (unsigned int i = 0;
             i < 10 && i < resultadoRango.getLogico(); ++i)
        {
            Arbol *arbol = resultadoRango[i];

            std::cout << "\nIdentificador: " << arbol->getAssetNum()
                      << "\nCodigo de parque: " << arbol->getNumParque()
                      << "\nNombre comun: " << arbol->getNombreComun()
                      << "\nNombre cientifico: " << arbol->getNbreCientifico()
                      << "\nTipo de planta: " << arbol->getTipo()
                      << '\n';
        }
}*/

int main()
{
    try
    {
      prueba1();
      //prueba2();
    }
    catch (const std::exception &error)
    {
        std::cerr << "\nError: " << error.what() << '\n';
        return 1;
    }

    return 0;
};
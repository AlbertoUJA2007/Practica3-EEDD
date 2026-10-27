#include "LectorCSV.h"

#include <fstream>
#include <iostream>
#include "Especie.h"
#include "VDinamico.h"

std::size_t LectorCSV::numeroEspecies_ = 0;
std::size_t LectorCSV::filasDescartadas_ = 0;
/**
 * @brief Carga el fichero CSV indicado, mostrando cada especie por pantalla.
 *
 * Cada línea se analiza y, si tiene el número de campos esperado, se
 * construye una Especie que se almacena en el VDinamico
 * Las filas con un número de campos
 * distinto del esperado se descartan (ver filasDescartadas()).
 *
 * @param rutaFichero Ruta del fichero CSV a leer.
 * @return true si el fichero se ha podido abrir, false en caso contrario.
 */
bool LectorCSV::cargarEspecies(VDinamico<Especie*> &vector, const std::string& rutaFichero) {
    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }

    //Declaradas fuera del bucle por eficiencia
    string codigo, nombreComun, nombreCientifico, tipoPlanta;
    while (std::getline(fichero, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (contarCampos(linea) != 4) {
            ++filasDescartadas_;
            continue;
        }

        codigo = extraerCampo(linea, 0);
        nombreComun = extraerCampo(linea, 1);
        nombreCientifico = extraerCampo(linea, 2);
        tipoPlanta = extraerCampo(linea, 3);

        TipoPlanta p = Especie::stringtotp(tipoPlanta);

        vector.insertar(new Especie(codigo, nombreComun, nombreCientifico,p));

    }
    numeroEspecies_= vector.getLogico();
    return true;
}

/**
 * @brief Número de especies leídas correctamente.
 * @return Cantidad de especies mostradas durante la última llamada a cargar().
 */
std::size_t LectorCSV::numeroEspecies() const {
    return numeroEspecies_;
}

/**
 * @brief Número de filas descartadas por no tener el número de campos esperado.
 * @return Cantidad de filas descartadas durante la última llamada a cargar().
 */
std::size_t LectorCSV::filasDescartadas() const {
    return filasDescartadas_;
}

/**
 * @brief Cuenta los campos de una línea CSV sin almacenarlos.
 *
 * Tiene en cuenta comillas envolventes y comillas escapadas ("") dentro
 * de un campo entrecomillado, tal como especifica RFC4180.
 *
 * @param linea Línea física a analizar.
 * @return Número de campos que contiene la línea.
 */
std::size_t LectorCSV::contarCampos(const std::string& linea) {
    std::size_t numCampos = 1;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ',') {
            ++numCampos;
            ++i;
        } else {
            ++i;
        }
    }

    return numCampos;
}

/**
 * @brief Extrae un único campo (por índice) de una línea CSV.
 *
 * Recorre la línea completa pero solo acumula el contenido del campo
 * solicitado; el resto de campos se descarta sin llegar a almacenarse.
 * Tiene en cuenta comillas envolventes y comillas escapadas ("").
 *
 * @param linea Línea física a analizar.
 * @param indiceObjetivo Índice (base 0) del campo a extraer.
 * @return Contenido del campo solicitado.
 */
std::string LectorCSV::extraerCampo(const std::string& linea, std::size_t indiceObjetivo) {
    std::string campo;
    std::size_t indiceActual = 0;
    bool dentroComillas = false;
    const std::size_t n = linea.size();

    for (std::size_t i = 0; i < n; ) {
        const char c = linea[i];

        if (dentroComillas) {
            if (c == '"') {
                if (i + 1 < n && linea[i + 1] == '"') {
                    if (indiceActual == indiceObjetivo) {
                        campo += '"';
                    }
                    i += 2;
                } else {
                    dentroComillas = false;
                    ++i;
                }
            } else {
                if (indiceActual == indiceObjetivo) {
                    campo += c;
                }
                ++i;
            }
        } else if (c == '"') {
            dentroComillas = true;
            ++i;
        } else if (c == ',') {
            if (indiceActual == indiceObjetivo) {
                return campo;
            }
            ++indiceActual;
            ++i;
        } else {
            if (indiceActual == indiceObjetivo) {
                campo += c;
            }
            ++i;
        }
    }

    return campo;
}

/**
 * @brief Elimina el BOM UTF-8 (0xEF 0xBB 0xBF) al inicio de la línea, si existe.
 * @param linea Línea a modificar in-place.
 */
void LectorCSV::eliminarBOM(std::string& linea) {
    static const char bom[3] = { static_cast<char>(0xEF), static_cast<char>(0xBB), static_cast<char>(0xBF) };
    if (linea.size() >= 3 && linea[0] == bom[0] && linea[1] == bom[1] && linea[2] == bom[2]) {
        linea.erase(0, 3);
    }
}

/**
 * @brief Muestra por pantalla los datos de una especie.
 * @param especie Especie a mostrar.
 */
void LectorCSV::mostrarEspecie(const Especie& especie) {
    std::cout << " - [" << especie.get_codigo_especie() << "] " << especie.get_nombre_comun()
              << " (" << especie.get_nombre_cientifico() << ") - "
              << Especie::tptostring(especie.get_tipo_planta()) << "\n";
}

bool  LectorCSV::cargarParques(ListaDE<Parque > &parques, const std::string &rutaFichero) {
    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }

    //Declaradas fuera del bucle por eficiencia

    while (std::getline(fichero, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (contarCampos(linea) < 2) {
            ++filasDescartadas_;
            continue;
        }

        int codigo_parque;              //Id de parque
        string nombre_parque;

        codigo_parque = stoi(extraerCampo(linea, 0));
        nombre_parque = extraerCampo(linea, 1);
        parques.insertaFin( Parque(codigo_parque,nombre_parque));

    }
    numeroEspecies_= parques.tam();
    return true;
}

bool LectorCSV::cargosArbol(AVL<Arbol *> &arboles, const std::string &rutaFichero, ListaDE<Parque> &parques) {
    filasDescartadas_ = 0;

    std::ifstream fichero(rutaFichero);
    if (!fichero.is_open()) {
        return false;
    }

    std::string linea;
    if (std::getline(fichero, linea)) {
        eliminarBOM(linea);
    }

    //Declaradas fuera del bucle por eficiencia

    while (std::getline(fichero, linea)) {
        if (linea.empty()) {
            continue;
        }

        if (contarCampos(linea) < 2) {
            ++filasDescartadas_;
            continue;
        }

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


        assetnum = extraerCampo(linea, 0);
        num_parque = stoi(extraerCampo(linea, 1));
        num_distrito = stoi(extraerCampo(linea, 2));
        nombre_distrito = extraerCampo(linea, 3);
        num_barrio = stoi(extraerCampo(linea, 4));
        nombre_barrio= extraerCampo(linea, 5);
        x= stod(extraerCampo(linea, 6));
        y= stod(extraerCampo(linea, 7));
        perimetro = stof(extraerCampo(linea, 8));
        altura = stof(extraerCampo(linea, 9));

        Arbol *a = new Arbol(assetnum,  num_parque,  num_distrito,
        nombre_distrito,  num_barrio, nombre_barrio,
         x,  y,  perimetro,  altura);
        arboles.inserta(a);

        Iterador<Parque> i = parques.iterador();

        while(!i.fin()) { //ligamos el arbol con un parque
            if(i.dato().getCodigoParque() == num_parque) {
                i.dato().insertarArbol(a);
            }
            i.siguiente();
        }

    }

    return true;
}

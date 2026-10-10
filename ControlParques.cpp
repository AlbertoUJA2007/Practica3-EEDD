//
// Created by almar on 05/10/2026.
//

#include "ControlParques.h"
#include "LectorCSV.h"

/**
 *
 * @param nomFichEspecies
 * @param nomFichParques
 */
ControlParques::ControlParques(const string &nomFichEspecies, const string &nomFichParques) {
	if(nomFichEspecies.empty() || nomFichParques.empty()) {
		throw invalid_argument("[ControlParques]: parametros no validos ");
	}
	if(!LectorCSV::cargarParques(this->parques, nomFichParques)) {
		throw std::runtime_error("[ControlParques:cargaParques]: error al abrir fichero ");
	}
	if(!LectorCSV::cargarEspecies(this->variantes, nomFichEspecies)) {
		throw std::runtime_error("[ControlParques:cargaEspecies]: error al abrir fichero ");
	}
}

/**
 * Destructor de parques
 */
ControlParques::~ControlParques() {
	for(int i =0; i < this->variantes.getLogico(); i++) { //eliminamos las especies
		delete this->variantes[i];
	}
	//la eliminación de parque se gestiona dentro de la clase listaDE
}

/**
* @def se encarga de enlazar la especie con el parque que la contiene
 * @param e objeto especie a enlazar
 * @param p objeto parque con el que se enlaza la especie
 */
void ControlParques::asignarEspecieParque( Especie &e,  Parque &p) {
	if(e.get_codigo_especie().empty() || p.getCodigoParque()) {
		throw invalid_argument("[ControlParques:asignarEspecieParque] parametro no valido   ");
	}
	p.insertarEspecie(&e);
}

/**
 * @brief cuenta la cantidad de veces que una especie aparece en un parque
 * @param nombre cadena de texto, indica el nombre de la especiie a buscar
 * @return cantidad de parques en la que aparece la especie
 */
int ControlParques::contarEspecieParque(const string &nombre) {
	int cant=0;

	
}

/**
 *
 * @param nombre
 * @return
 */
Parque & ControlParques::buscarParque(const string &nombre) {
}

/**
 *
 * @param cadena
 * @return
 */
VDinamico<Especie> & ControlParques::listadoEspecieSubNombre(const string &cadena) {
}

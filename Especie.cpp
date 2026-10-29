//
// Created by Maitena on 19/9/2026.
//

#include "Especie.h"

#include <iostream>


/**
 *	Obtiene el codigo de especie
 * @return codigo de especie
 */
string Especie::get_codigo_especie() const { return this->codigoEspecie; }

/**
 *	 establece el codigo de especie
 * @param codigo_especie, cadena no nula
 */
void Especie::set_codigo_especie(const string &codigo_especie) {

	if(codigo_especie.empty()) {
		throw invalid_argument("[set_codigo_especie]: codigo de especie no válido");
	}
	this->codigoEspecie = codigo_especie;
}

/**
 *	obtiene nombre comun de la especie
 * @return cadena
 */
string Especie::get_nombre_comun() const {return this->nombreComun;}

/**
 *	Establece el nombre comun de la especie
 * @param nombre_comun cadena no nula
 */
void Especie::set_nombre_comun(const string &nombre_comun) {
	if(nombre_comun.empty()) {
		throw invalid_argument("[set_nombre_comun]: nombre común de especie no válido");
	}
     this->nombreComun = nombre_comun;
}

/**
 * obtiene nombre cientifico
 * @return cadena
 */
string Especie::get_nombre_cientifico() const {return this->nombreCientifico;}

/**
 * establece nombre cientifico de la especie
 * @param nombre_cientifico cadena no nula
 */
void Especie::set_nombre_cientifico(const string &nombre_cientifico) {
	if(nombre_cientifico.empty()) {
		throw invalid_argument("[set_nombre_cientifico]: nombre cientifico de especie no válido");
	}
	this->nombreCientifico = nombre_cientifico;
}

/**
 * @brief Obtiene el tipo de planta de la especie.
 * @return Cadena de texto con el tipo de planta.
 */
TipoPlanta Especie::get_tipo_planta() const {
	return this->tipo_planta_;
}

/**
 * @brief Modifica el tipo de planta de la especie.
 * @param tipo_planta Cadena de texto con el nuevo tipo de planta.
 */
void Especie::set_tipo_planta(const TipoPlanta &tipo_planta) {

      this->tipo_planta_ = tipo_planta;
}

/**
 * @brief Compara si la especie actual es igual a otra.
 * @param arr Especie con la que se realiza la comparación.
 * @return true si coinciden en dirección de memoria o código de especie; false en caso contrario.
 */
bool Especie::operator==(const Especie &arr) {
      if(this == &arr) {                        //son el mismo objeto
        return true;
      }
      if(this->codigoEspecie == arr.codigoEspecie)
      {
          return true;
      } else {
          return false;
       }
}

/**
 * @brief Determina si la especie actual es menor que otra basándose en el código de especie.
 * @param arr Especie con la que se realiza la comparación.
 * @return true si el código de la especie actual es menor que el de 'arr'; false en caso contrario.
 */
bool Especie::operator<(const Especie &arr) {
      if(this->codigoEspecie < arr.codigoEspecie) {
            return true;
      } else {
          return false;
      }
}

/**
 * @brief Constructor parametrizado de la clase Especie.
 * @param cod Código identificador de la especie (mínimo 2 caracteres).
 * @param nombreComun Nombre común de la especie.
 * @param nombreCientifico Nombre científico de la especie.
 * @param tipoPlanta Tipo de planta de la especie.
 * @throw std::invalid_argument Si el código introducido tiene una longitud menor a 2 caracteres.
 */
Especie::Especie(const string &cod, const string &nombreComun, const string &nombreCientifico,
				 const TipoPlanta &tipoPlanta) {

           if(cod.length()< 2) {
           throw invalid_argument("[Especie:Especie()]: codigo no válido "  );
          }

          this->codigoEspecie = cod;
          this->nombreCientifico = nombreCientifico;
          this->nombreComun = nombreComun;
          this->tipo_planta_ = tipoPlanta;

}

/**
 * @brief Constructor por defecto de la clase Especie.
 */
Especie::Especie() {
	this->codigoEspecie="";
	this->nombreCientifico="";
	this->nombreComun="";
	this->tipo_planta_ = TipoPlanta::NONE;
}
/**
 * @brief Muestra por consola los datos detallados de la especie.
 */
void Especie::mostrarInfo() {
	cout << " -------------------------------" << endl;
	cout << "Codigo especie: " << this->codigoEspecie << endl;
	cout << "Nombre común: " << this->nombreComun << endl;
	cout << "Nombre cientifico: " << this->nombreCientifico << endl;
	cout << "Tipo planta: ";
	tptostring(this->tipo_planta_);
	cout << " -------------------------------" << endl;
}

/**
 * @brief Convierte un valor de TipoPlanta a su representación en texto en mayúsculas.
 * @param p Tipo de planta a convertir.
 * @return Cadena con el nombre legible del tipo de planta.
 */
string Especie::tptostring(const TipoPlanta &p) {
	if (p == TipoPlanta::ARBUSTO) return "ARBUSTO";
	if (p == TipoPlanta::CONIFERA) return "CONÍFERA";
	if (p == TipoPlanta::PALMACEA) return "PALMÁCEA";
	if (p == TipoPlanta::HERB_PERENNES) return "HERBÁCEA PERENNE";
	if (p == TipoPlanta::FRONDOSA) return "FRONDOSA";
	if (p == TipoPlanta::TAPIZANTE_TREPADORA) return "TAPIZANTE/TREPADORA";
	if (p == TipoPlanta::CACTACEA_SUCULENTA) return "CACTÁCEA/SUCULENTA";
	if (p == TipoPlanta::SUBTROPICAL_TROPICAL) return "SUBTROPICAL/TROPICAL";
	if (p == TipoPlanta::HERB_ANUAL) return "HERBÁCEA ANUAL";
	if (p == TipoPlanta::HERB_ANUALES) return "HERBÁCEAS ANUALES";

	return "";
}

/**
 * @brief Convierte una cadena de texto a su valor correspondiente de TipoPlanta.
 * @param texto Cadena a convertir.
 * @return Enumerado TipoPlanta asignado.
 */
TipoPlanta Especie::stringtotp(const string &texto) {
		if (texto == "ARBUSTO")              return TipoPlanta::ARBUSTO;
		if (texto == "CONÍFERA" || texto == "CONIFERA")             return TipoPlanta::CONIFERA;
		if (texto == "PALMACEA" || texto == "PALMÁCEA")             return TipoPlanta::PALMACEA;
		if (texto == "HERB_PERENNES" || texto == "HERBÁCEA PERENNE")     return TipoPlanta::HERB_PERENNES;
		if (texto == "FRONDOSA")             return TipoPlanta::FRONDOSA;
		if (texto == "TAPIZANTE/TREPADORA")  return TipoPlanta::TAPIZANTE_TREPADORA;
		if (texto == "CACTACEA/SUCULENTA" || texto == "CACTÁCEA/SUCULENTA")   return TipoPlanta::CACTACEA_SUCULENTA;
		if (texto == "SUBTROPICAL/TROPICAL") return TipoPlanta::SUBTROPICAL_TROPICAL;
		if (texto == "HERB_ANUAL")       return TipoPlanta::HERB_ANUAL;
		if (texto == "HERB_ANUALES" || texto == "HERBÁCEAS ANUALES")    return TipoPlanta::HERB_ANUALES;
		if(texto.empty()) return TipoPlanta::NONE;
		else return TipoPlanta::NONE;
}

/**
 * @brief Destructor de la clase Especie.
 */
Especie::~Especie() {
	this->codigoEspecie ="";
	this->nombreComun="";
	this->nombreCientifico="";
	this->tipo_planta_ = TipoPlanta::NONE;
}
/**
 * @brief Constructor parametrizado.
 * @param cod Código de la especie.
 * @param nombre Nombre común de la especie.
 */
Especie::Especie(const string &cod, const string &nombre) {
	this->codigoEspecie = cod; this->nombreComun = nombre;
	this->tipo_planta_ = TipoPlanta::NONE;
}

/**
 * @brief Constructor de copia.
 * @param arr Objeto Especie a copiar.
 */
Especie::Especie(const Especie &arr) {
	this->codigoEspecie = arr.get_codigo_especie();
	this->tipo_planta_ = arr.get_tipo_planta();
	this->nombreComun = arr.get_nombre_comun();
	this->nombreCientifico = arr.get_nombre_cientifico();
}


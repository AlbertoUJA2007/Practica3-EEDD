//
// Created by Maitena on 19/9/2026.
//

#ifndef ESPECIE_H
#define ESPECIE_H
#include <string>
#include <VDinamico.h>
enum class TipoPlanta{
	ARBUSTO,CONIFERA, PALMACEA, HERB_PERENNES, FRONDOSA, TAPIZANTE_TREPADORA
	,CACTACEA_SUCULENTA, SUBTROPICAL_TROPICAL,  HERB_ANUAL, HERB_ANUALES, NONE
};

using namespace std;

class Especie {
private:
	string codigoEspecie;
	string nombreComun;
	string nombreCientifico;
	TipoPlanta tipo_planta_;

public:
	/**
	 *
	 * @return
	 */
	string get_codigo_especie() const;

	/**
	 *
	 * @param codigo_especie
	 */
	void set_codigo_especie(const string &codigo_especie);
	
	string get_nombre_comun() const;

	void set_nombre_comun(const string &nombre_comun);

	string get_nombre_cientifico() const;

	void set_nombre_cientifico(const string &nombre_cientifico);

	TipoPlanta get_tipo_planta() const;

	void set_tipo_planta(const TipoPlanta &tipo_planta);

	bool operator==(const Especie &arr);
	bool operator<(const Especie &arr);


	Especie(const string &cod, const string &nombreComun, const string &nombreCientifico, const TipoPlanta &tipoPlanta);

	Especie();

	void mostrarInfo();

	static string tptostring(const TipoPlanta &p);
	static TipoPlanta stringtotp(const string &texto);
	~Especie();
	Especie(const string &cod, const string &nombre);
	Especie(const Especie &arr);

};



#endif //ESPECIE_H


#include "Arbol.h"

/**
 * @brief Constructor por defecto de la clase Arbol.
 * Inicializa los atributos numéricos a 0, las cadenas vacías y la especie a nullptr.
 */
Arbol::Arbol(): assetnum(""),num_parque(0),num_distrito(0),
                nombre_distrito(""),num_barrio(0),nombre_barrio(""),
                x(0),y(0),perimetro(0),altura(0),especie_arbol(nullptr)
{
}

/**
 * @brief Constructor parametrizado de la clase Arbol.
 * @param assetnum Identificador único del árbol.
 * @param num_parque Número del parque donde se ubica el árbol.
 * @param num_distrito Número del distrito.
 * @param nombre_distrito Nombre del distrito.
 * @param num_barrio Número del barrio.
 * @param nombre_barrio Nombre del barrio.
 * @param x Coordenada X de la ubicación del árbol.
 * @param y Coordenada Y de la ubicación del árbol.
 * @param perimetro Perímetro del tronco del árbol.
 * @param altura Altura del árbol.
 */
Arbol::Arbol(const string &assetnum, int num_parque, int num_distrito, const string &nombre_distrito, int num_barrio,
    const string &nombre_barrio, double x, double y, float perimetro, float altura):
        assetnum(assetnum),num_parque(num_parque),num_distrito(num_distrito),nombre_distrito(nombre_distrito),
        num_barrio(num_barrio),nombre_barrio(nombre_barrio),x(x),y(y),perimetro(perimetro),altura(altura)
{
}

/**
 * @brief Constructor de copia de la clase Arbol.
 * @param orig Objeto Arbol de origen a copiar.
 */
Arbol::Arbol(const Arbol &orig): assetnum(orig.assetnum),num_parque(orig.num_parque),num_distrito(orig.num_distrito),
                                nombre_distrito(orig.nombre_distrito),num_barrio(orig.num_barrio),
                                nombre_barrio(orig.nombre_barrio),x(orig.x),y(orig.y),perimetro(orig.perimetro),
                                altura(orig.altura),especie_arbol(orig.especie_arbol)
{
}

/**
 * @brief Destructor de la clase Arbol.
 * Reinicia los miembros a valores por defecto y libera la memoria asignada a la especie.
 */
Arbol::~Arbol() {
    this->assetnum = "";
    this->num_parque = 0;
    this->num_distrito = 0;
    this->nombre_distrito = "";
    this->num_barrio = 0;
    this->nombre_barrio = "";
    this->x = 0;
    this->y = 0;
    this->perimetro = 0;
    this->altura = 0;
    delete especie_arbol;
    especie_arbol = nullptr;
}

/**
 * @brief Sobrecarga del operador de asignación.
 * @param arbol Objeto Arbol a asignar.
 * @return Arbol& Referencia al objeto actual modificado.
 */
Arbol & Arbol::operator=(const Arbol &arbol) {
    if (this != &arbol) {

        delete especie_arbol;
        especie_arbol = nullptr;

        this->especie_arbol = arbol.especie_arbol;
        this->assetnum = arbol.assetnum;
        this->num_parque = arbol.num_parque;
        this->num_distrito = arbol.num_distrito;
        this->nombre_distrito = arbol.nombre_distrito;
        this->num_barrio = arbol.num_barrio;
        this->nombre_barrio = arbol.nombre_barrio;
        this->x = arbol.x;
        this->y = arbol.y;
        this->perimetro = arbol.perimetro;
        this->altura = arbol.altura;

    }
    return *this;
}

/**
 * @brief Sobrecarga del operador mayor que (>). Compara según el identificador assetnum.
 * @param arbol Objeto Arbol con el cual comparar.
 * @return true Si el assetnum del árbol actual es alfabéticamente mayor.
 * @return false En caso contrario.
 */
bool Arbol::operator>(const Arbol &arbol) {
    return this->assetnum > arbol.assetnum;
}

/**
 * @brief Sobrecarga del operador menor que (<). Compara según el identificador assetnum.
 * @param arbol Objeto Arbol con el cual comparar.
 * @return true Si el assetnum del árbol actual es alfabéticamente menor.
 * @return false En caso contrario.
 */
bool Arbol::operator<(const Arbol &arbol) {
    return this->assetnum < arbol.assetnum;
}

/**
 * @brief Sobrecarga del operador de igualdad (==). Compara dos árboles según su identificador único (assetnum).
 * @param arbol Objeto Arbol con el cual comparar.
 * @return true Si ambos árboles tienen el mismo assetnum.
 * @return false En caso contrario.
 */
bool Arbol::operator==(const Arbol &arbol) {
	return (this->assetnum == arbol.assetnum) ;
}

/**
 * @brief Establece la especie asociada al árbol.
 * @param e Puntero al objeto Especie.
 */
void Arbol::setEspecie(Especie *e) {
    this->especie_arbol = e;
}

/**
 * @brief Obtiene el código de la especie asociada al árbol.
 * @return string Código de la especie.
 */
string Arbol::getCodigoEspecie() const {
    return especie_arbol->get_codigo_especie();
}

/**
 * @brief Obtiene el tipo de planta de la especie del árbol.
 * @return TipoPlanta Enumerado o tipo con la categoría de la planta.
 */
TipoPlanta Arbol::getTipoEspecie() const {
    return especie_arbol->get_tipo_planta();
}

/**
 * @brief Obtiene el nombre común de la especie del árbol.
 * @return string Nombre común de la especie.
 */
string Arbol::getNombreComun() const {
    return especie_arbol->get_nombre_comun();
}

/**
 * @brief Establece el identificador único del árbol (assetnum).
 * @param asNum Nuevo código identificador.
 */
void Arbol::setAsNum(const string &asNum) {
    this->assetnum= asNum;
}
/**
 * @brief Obtiene la altura del árbol.
 * @return float Altura en metros o unidad correspondiente.
 */
float Arbol::get_altura() const {
    return altura;
}


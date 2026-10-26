
#include "Arbol.h"

Arbol::Arbol(): assetnum(""),num_parque(0),num_distrito(0),
                nombre_distrito(""),num_barrio(0),nombre_barrio(""),
                x(0),y(0),perimetro(0),altura(0),especie_arbol(nullptr)
{
}

Arbol::Arbol(const string &assetnum, int num_parque, int num_distrito, const string &nombre_distrito, int num_barrio,
    const string &nombre_barrio, double x, double y, float perimetro, float altura):
        assetnum(assetnum),num_parque(num_parque),num_distrito(num_distrito),nombre_distrito(nombre_distrito),
        num_barrio(num_barrio),nombre_barrio(nombre_barrio),x(x),y(y),perimetro(perimetro),altura(altura)
{
}

Arbol::Arbol(const Arbol &orig): assetnum(orig.assetnum),num_parque(orig.num_parque),num_distrito(orig.num_distrito),
                                nombre_distrito(orig.nombre_distrito),num_barrio(orig.num_barrio),
                                nombre_barrio(orig.nombre_barrio),x(orig.x),y(orig.y),perimetro(orig.perimetro),
                                altura(orig.altura),especie_arbol(orig.especie_arbol)
{
}

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

bool Arbol::operator>(const Arbol &arbol) {
    return this->assetnum > arbol.assetnum;
}

bool Arbol::operator<(const Arbol &arbol) {
    return this->assetnum < arbol.assetnum;
}

void Arbol::setEspecie(Especie *e) {
    this->especie_arbol = e;
}

string Arbol::getCodigoEspecie() const {
    return especie_arbol->get_codigo_especie();
}

TipoPlanta Arbol::getTipoEspecie() const {
    return especie_arbol->get_tipo_planta();
}

string Arbol::getNombreComun() const {
    return especie_arbol->get_nombre_comun();
}

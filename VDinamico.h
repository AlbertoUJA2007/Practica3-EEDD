
#ifndef VDINAMICO_H
#define VDINAMICO_H
#include <cmath>
#include <stdexcept>
#include <climits>

#include <algorithm>
#include "iostream"
using namespace std;

template<class T>
class VDinamico {

	T *v;
	unsigned long  int tamlog;
	unsigned long int tamfis;

public:

	/**
	* @brief  Constructor por defecto, inicializa el vector, tamaño logico a 0 y tamaño fisico a 1
	*/
	VDinamico<T>();

	/**
	 * @brief  Constructor parametrizado. El tamaño fisico será potencia de 2
	* @param tamLog tamaño logico que tendrá el vector
	* @param dato elementos a introducir dentro del vector, la cantidad de elementos dentro del vector
	* será determinada por el parametro tamLog. El tamaño fiisco será la potencia de 2 igual o mayor
	* que el tamLog
	*/
	VDinamico<T>(unsigned int tamLog, T &dato);

	/**
	 * @brief  Constructor copia
	* @param origen
	*/
	VDinamico<T>(const VDinamico<T>& origen);

	/**
	 * @brief Constructor copia parcial, crea un vector de tamaño logico numElementos a partir de posicion inicial del vector origen
	* @param origen vector al que se le hará la copia
	* @param posicionInicial poicion donde comienza la copia del vector
	* @param numElementos cantidad de elementos a copiar
	* @cond tamaño fisico será potencia de 2
	*/
	VDinamico<T>(const VDinamico<T>& origen, const  unsigned int &posicionInicial, const unsigned int &numElementos);

	bool esPotenciaDeDos(int num);
	int potenciaDeDos(int num);

	/**
	* @brief operador asignación
	* @param arr vector al que se le realizará la "copia"
	* @return objeto this, el objeto copia
	*/
	VDinamico<T>& operator=(const VDinamico &arr);

	/**
	 * @brief operador []
	* @param i posicion a devolver
	* @return objeto en posicion i
	* @pre valor i debe ser intervalo [0-tamLog]
	*/
	T& operator[](const unsigned int &i);

	/**
	* @brief inserta un dato en la posicion establecida en parametro
	* @param dato Elemento a insertar
	* @param pos posicion en la que se realiza la insercion. En caso de no ser especificada
	* toma el valor UINT_MAX, lo que significa que haremos la insercion al final del vector
	* @pre pos, en caso de ser especificada, estará en intervalo [0-tamLog]
	* @post valor tamLog incrementa en 1
	*/
	void insertar(const T& dato,  unsigned int pos = UINT_MAX);

	/**
	 * @brief elimina un elemento del vector de una posicion.O(n)
	* @param pos indice donde se hará la eliminación, En caso de no ser especificado se hará en la
	* última posición
	* @return devuelve el objeto eliminado
	*/
	T borrar (unsigned int pos = UINT_MAX);


	/**
	* @brief ordena el vector de menor a mayor
	*/
	void ordenar();

	/**
	 * @brief realiza la busqueda discotomica en el vector
	* @pre Se asume que el vector esta ordenado
	* @param dato dato a buscar dentro del vector
	* @return posicion donde se encuentra el dato
	*/
	int busquedaDicotomica(const T& dato);

	/**
	 *
	* @return devuelve el tamaño lógico del vector
	*/
	unsigned int getLogico() const;

	/**
	* @brief destructor del objeto
	*/
	~VDinamico();

	void aumentarTam();


private:
	void disminuirTam();
};

template<typename T>
VDinamico<T>::VDinamico(): tamlog(0), tamfis(1) {
	v = new T[tamfis];
}

template<typename T>
VDinamico<T>::VDinamico(unsigned int tamLog, T &dato) {

	if(tamLog == 0 ) {
		throw std::out_of_range("[VDinamico] tamaño logico no válido");
	}
	this->tamlog= tamLog;
	tamfis=potenciaDeDos(tamLog);

	v = new T[tamfis];
	for (int i=0;i<tamLog;i++) {
		v[i]=dato;
	}
}

template <typename T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen)
{
	this->tamlog= origen.tamlog;
	this->tamfis = origen.tamfis;

	v = new T[tamfis];
	for (int i=0;i<tamlog;i++) {
		v[i]=origen.v[i];
	}
}

template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen, const unsigned int &posicionInicial, const unsigned int &numElementos)
{
	if (posicionInicial+numElementos>=origen.tamlog) {
		throw out_of_range("[VDinamico::VDinamico]: El numero de elementos supera el rango del vector.");
	}
	tamlog = numElementos;
	tamfis = potenciaDeDos(tamlog);
	v = new T[tamfis];

	for(int i=0;i<tamlog;i++) {
		v[i]=origen.v[i+posicionInicial];
	}
}


template<typename T>
bool VDinamico<T>::esPotenciaDeDos(int num) {
	if(num%2!=0){
		return false;
	}
	int a=1;
	for(int i=0;i<num/2;i++) {
		a=a*2;
		if(a==num) {
			return true;
		}
		if(a>num) {
			return false;
		}
	}
	return false;
}

template<typename T>
int VDinamico<T>::potenciaDeDos(int num) {
	int pot=num+1;
	while(!esPotenciaDeDos(pot)){
		pot++;
	}
	return pot;
}

template<typename T>				//vector=arr
VDinamico<T> & VDinamico<T>::operator=(const VDinamico &arr) {
	if (this != &arr) { //la dirección de memoria debe ser distinta
		delete [] v;					//Forma de eliminar un vector dinamico

		tamfis=arr.tamfis;
		tamlog=arr.tamlog;
		v = new T[tamfis]; //creamos el nuevo vector

		for (int i=0;i<tamlog;i++) { //copiamos los valores
			v[i]=arr.v[i];
		}
	}

	return *this; //devolvemos la referencia del objeto
}


template <typename T>
T& VDinamico<T>::operator[](const unsigned int &i){  //T& para permitir lectura y escritura
	if( (i<0) || (i >= tamfis) ){
		throw  invalid_argument("[operator[]]: se ha intentado acceder a una dirección no válida");
	}
	return v[i];
}

template<typename T>
void VDinamico<T>::insertar(const T &dato, unsigned int pos) {


	if( pos > tamfis && pos != UINT_MAX) {
		throw invalid_argument("[insertar] posicion no valida");
	}
	if (tamfis==tamlog) {
		tamfis=potenciaDeDos(tamfis);
		aumentarTam();
	}
	if (pos==UINT_MAX) {					//Insercion al final del vector
		v[tamlog]=dato;
		tamlog++;
	} else {
		 //Insercion en la posicion dada
		for (int i=tamlog;i>(int)pos;i--) {
			v[i+1]=v[i];
		}
		v[pos]=dato;
		tamlog++;
	}
}
template<typename T>
void VDinamico<T>::disminuirTam() {
	this->tamfis= this->tamfis/2;
	T *nuevo= new T[this->tamfis];
	for(int i=0; i < this->tamlog; i++) {
		nuevo[i] = this->v[i];
	}
	delete [] this->v;
	this->v = nuevo;
}

template<typename T>
T VDinamico<T>::borrar(unsigned int pos) {
	if (pos > tamfis && pos != UINT_MAX) {
		throw out_of_range("[VDinamico<T>::borrar]: La posicion dada no existe en el vector.");
	}
	T eliminado;
	if(this->tamlog *3 < this->tamfis) { //si el vector sufre muchos borrados se debe disminuir el tamaño
		disminuirTam();
	}

	if (pos == UINT_MAX) {				//Eliminar el ultimo dato del vector
		eliminado = v[this->tamlog-1];
		v[tamlog-1]=v[tamlog];
		tamlog--;
	} else {
		eliminado = v[pos];
		for (unsigned int i=pos;i<tamlog;i++) {	//Eliminar la posicion dada del vector
			v[i]=v[i+1];
		}
		tamlog--;
	}

	return eliminado; //se devuelve el elemento eliminado
}

template<typename T>
void VDinamico<T>::ordenar() {
	sort(v,v + tamlog);
}

template<typename T>
int VDinamico<T>::busquedaDicotomica(const T &dato) {
	int inf = 0;   //margen inferior
	int sup = tamlog-1; // margen superior
	int aux;
	while (inf <= sup) {
		aux = (inf+sup)/2;
		if (v[aux]==dato) {
			return aux;
		} else if (v[aux]<dato) {
			inf = aux + 1;			//Se le suma uno pq la posicion aux ya esta comprobada, parte desde la siguiente
		} else {
			sup = aux - 1;			//Lo mismo que antes, pero al ser el limite de arriba, parte desde la posicion anterior
		}
	}
	return -1;						//Sirve para indicar que el elemento dado no existe dentro del vector
}

template<typename T>
unsigned int VDinamico<T>::getLogico() const {
	return tamlog;
}

template<typename T>
VDinamico<T>::~VDinamico() {
	this->tamfis =0;
	this->tamlog=0;
	delete [] v;
	v = nullptr;
}

template<typename T>
void VDinamico<T>::aumentarTam() {

	T *nuevo = new T[this->tamfis];

	for(int i =0; i < tamlog; i++) {
		nuevo[i] = this->v[i];
	}
	delete [] v;

	v = nuevo; //aaaaa
}

#endif //VDINAMICO_H

//
// Created by Maitena on 12/10/2026.
//
#include "Nodo.h"
#include "ListaDE.h"
#ifndef ITERADOR_H
#define ITERADOR_H
template<class T>
class ListaDE;

template<class T>
class Iterador {
	Nodo<T> *nodo;
	friend class ListaDE<T>;
public:
	Iterador(Nodo<T> *nodo): nodo(nodo){}

	bool hayAnterior();

	bool haySiguiente();

	void anterior() { nodo = nodo->ant;}//Desplaza el iterador una posicion hacia atrás. Puntero nodo apunta al nodo anterior

	void siguiente() { nodo = nodo->sig;} //Desplaza el iterador una posicion hacia delante. Puntero nodo apunta al nodo siguiente

	T &dato() { return nodo->dato; }//Devuelve el contenido del nodo
	bool fin();


	template<typename  T>
	bool hayAnterior()
	{           //Comprobar si existe un nodo anterior
		if (nodo->ant != nullptr) {
			return true;
		}
		return false;

	}
	template<typename  T>
	bool haySiguiente(){               //Comprobar si existe un nodo siguiente
		if (nodo->sig != nullptr) {
			return true;
		}
		return false;
	}
	template<typename T>
	bool fin() {
		if(nodo->sig == nullptr) {
			return true;
		}
		return false;
	}
};
#endif //ITERADOR_H

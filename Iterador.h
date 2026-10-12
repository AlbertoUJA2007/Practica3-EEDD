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

	bool hayAnterior() {           //Comprobar si existe un nodo anterior
		if (nodo->ant != nullptr) {
			return true;
		}
		return false;

	}

	bool haySiguiente() {               //Comprobar si existe un nodo siguiente
		if (nodo->sig != nullptr) {
			return true;
		}
		return false;

	}

	void anterior() {               //Desplaza el iterador una posicion hacia atrás. Puntero nodo apunta al nodo anterior
		nodo = nodo->ant;
	}

	void siguiente() {              //Desplaza el iterador una posicion hacia delante. Puntero nodo apunta al nodo siguiente
		nodo = nodo->sig;
	}

	T &dato() {                    //Devuelve el contenido del nodo
		return nodo->dato;
	}
};
#endif //ITERADOR_H

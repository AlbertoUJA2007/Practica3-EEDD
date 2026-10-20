//
// Created by Maitena on 12/10/2026.
//

#ifndef NODO_H
#define NODO_H
template <class T>
class Nodo {
public:
	T dato;

	//Para listasDE
	Nodo<T> *ant,*sig;
	Nodo(const T &dato, Nodo *ant, Nodo *sig):
			dato(dato),ant(ant),sig(sig){}

	//Para arboles AVL
	Nodo<T> *izq,*der;
	char bal; //Factor de equilibrio en cada nodo
	Nodo(Nodo *izq, Nodo *der, const T&dato):
			dato(dato),izq(izq),der(der){}
};
#endif //NODO_H

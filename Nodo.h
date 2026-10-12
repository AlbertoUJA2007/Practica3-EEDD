//
// Created by Maitena on 12/10/2026.
//

#ifndef NODO_H
#define NODO_H
template <class T>
class Nodo {
public:
	T dato;
	Nodo *ant,*sig;
	Nodo(const T &dato, Nodo *ant, Nodo *sig):
			dato(dato),ant(ant),sig(sig){}
};
#endif //NODO_H

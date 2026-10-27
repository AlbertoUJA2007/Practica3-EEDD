//
// Created by Maitena on 27/10/2026.
//

#ifndef NODOARBOL_H
#define NODOARBOL_H

/**
 * @brief Clase que representa un nodo en un árbol AVL.
 * @tparam T Tipo de dato almacenado en el nodo.
 */
template<class T>
class NodoArbol {
public:
	T dato;
	NodoArbol<T> *der,*izq;
	char bal = 0; //factor de equilibrio en un avl, 0: equilibrado; -1 desequilibrado por la izq; 1 por la der

	/**
	 * @brief Constructor del nodo.
	 * @param dato Dato a almacenar en el nodo.
	 * @param izq Puntero al hijo izquierdo (por defecto nullptr).
	 * @param der Puntero al hijo derecho (por defecto nullptr).
	 */
	NodoArbol(const T&dato, NodoArbol *izq, NodoArbol *der);
};
template<class T>
NodoArbol<T>::NodoArbol(const T &dato, NodoArbol *izq, NodoArbol *der) {
	this->dato = dato;
	this->izq = izq;
	this->der = der;
}
#endif //NODOARBOL_H

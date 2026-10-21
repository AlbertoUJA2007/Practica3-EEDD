
#ifndef PRACTICA2_EEDD_AVL_H
#define PRACTICA2_EEDD_AVL_H
#endif //PRACTICA2_EEDD_AVL_H
#include "ListaDE.h"
#include "VDinamico.h"

template<class T>
class NodoArbol {
private:
    T dato;
    NodoArbol<T> *der,*izq;
    char bal = 0;
public:
    NodoArbol(const T&dato, NodoArbol *izq, NodoArbol *der):
            dato(dato),izq(izq),der(der){}
};


template<class T>
class AVL {
private:
    unsigned int numElementos=0;
    Nodo <T> *raiz;

    void rotDer(NodoArbol<T>* &nodo);
    void rotIzq(NodoArbol<T>* &nodo);

    //Metodos auxiliares
    void inorden(NodoArbol<T> *p, VDinamico<T*> vector);
    void preorden(NodoArbol<T> *p, VDinamico<T*> vector);

public:
    AVL<T>();
    AVL<T>(const AVL<T> &origen);   //En preorden y debe crear una copia identica
    AVL<T>& operator=(const AVL<T> &avl);   //Debe crear una copia identica
    bool inserta(T& dato);
    T* buscaRecursiva(T &dato); //busqueda recursiva
    T* buscaIterativa(T &dato); //busqueda iterativa
    VDinamico<T*> recorreInorden();
    unsigned int numElementos();
    unsigned int altura();
    ~AVL(); //En postorden
};

/**
 *
 */
template<class T>
AVL<T>::AVL() {
    raiz = nullptr;
}

template<class T>
AVL<T>::AVL(const AVL<T> &origen) {

    if (origen.raiz) {
        NodoArbol<T> *p = origen.raiz;
        this->raiz = new NodoArbol<T>(raiz);
        NodoArbol<T> *izq,*der;
        izq = raiz->izq;
        der = raiz->der;
        insercionPreorden(izq, p->izq);
        insercionPreorden(der,p->der);
    }
}

template<class T>
void AVL<T>::inorden(NodoArbol<T> *p, VDinamico<T*> &vector) {
    if (p != nullptr) {                 //Vemos si ese nodo existe realmente, sino, va hacia atrás en la recursividad
        inorden(p->izq,vector);         //Hacemos una llamada recursiva al nodo de la izquierda
        vector.insertar(&p->dato);      //Si este existe y es el ultimo, lo insertamos en el vector. Si no existe
                                        //  el nodo de la izquierda, insertamos el nodo padre en el vector
        inorden(p->der,vector);         //hacemos una llamada recursiva al nodo de la derecha
    }
}


template<class T>
VDinamico<T*> AVL<T>::recorreInorden() {
    VDinamico<T*> v;
    inorden(this->raiz,v);
    return v;               //Devuelve un vector de punteros a los elementos del AVL
}

template<class T>
void AVL<T>::preorden(NodoArbol<T> *p, VDinamico<T *> vector) {
    if (p != nullptr) {
        vector.insertar(&p->dato);
        preorden(p->izq,vector);
        preorden(p->der,vector);
    }
}

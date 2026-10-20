
#ifndef PRACTICA2_EEDD_AVL_H
#define PRACTICA2_EEDD_AVL_H
#include "VDinamico.h"

#endif //PRACTICA2_EEDD_AVL_H
#include <Nodo.h>
template<class T>
class AVL {
private:
    //El nodo de un arbol se construye mediante la clase Nodo
    //Se editó para que funcionase para un arbol ademas de para una listaDe
    unsigned int numElementos=0;    //contador del numero de elementos del arbol
    Nodo <T> *raiz;
public:
    AVL<T>();
    AVL<T>(const AVL<T> &origen);   //En preorden y debe crear una copia identica
    AVL<T>& operator=(const AVL<T> &avl);   //Debe crear una copia identica
    void rotDer(Nodo<T>* &nodo);
    void rotIzq(Nodo<T>* &nodo);
    bool inserta(T& dato);
    T* buscaRecursiva(T &dato); //busqueda recursiva
    T* buscaIterativa(T &dato); //busqueda iterativa
    VDinamico<T*> recorreInorden();
    unsigned int numElementos();
    unsigned int altura();
    ~AVL(); //En postorden

    //Metodos auxiliares
    void inorden(Nodo<T> *p, VDinamico<T*> vector);

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
        Nodo<T> *p = origen.raiz;
        this->raiz = new Nodo<T>(raiz);
        Nodo<T> *izq,*der;
        izq = raiz->izq;
        der = raiz->der;
        insercionPreorden(izq, p->izq);
        insercionPreorden(der,p->der);
    }
}

template<class T>
void AVL<T>::inorden(Nodo<T> *p, VDinamico<T*> &vector) {
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



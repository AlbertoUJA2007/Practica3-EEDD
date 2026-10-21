
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
    void copia(NodoArbol<T> *p);

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

template<class T>
AVL<T>::AVL() {
    raiz = nullptr;
}

template<class T>
AVL<T>::AVL(const AVL<T> &origen): raiz(nullptr),numElementos(0)
{
    this->raiz = copia(origen.raiz);
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

template<class T>
NodoArbol<T>* AVL<T>::copia(NodoArbol<T> *p) {
    if (p == nullptr) {             //Si en el arbol orig no existe un nodo, no lo copiamos
        return nullptr;
    }
    NodoArbol<T> *otro = new NodoArbol<T>(p->dato); //Creamos el nodo
    otro->bal = p->bal;             //Copiamos el equilibrio del arbol origen
    numElementos++;                 //Aumentamos el tamaño del nuevo arbol
    otro->izq = copia(p->izq);      //Copia del nodo de la izquierda de forma recursiva
    otro->der = copia(p->der);      //Copia del nodo de la derecha de forma recursiva

    return otro;
}

template<class T>
AVL<T> &AVL<T>::operator=(const AVL<T> &avl) {
    if (this != &avl) {
        if (this->raiz != nullptr) {
            //FALTA BORRAR LOS ELEMENTOS DEL ARBOL
        }
        this->raiz = copia(avl.raiz);
    }
    return *this;
}


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
    char bal = 0; //factor de equilibrio en un avl, 0: equilibrado; -1 desequilibrado por la izq; 1 por la der
public:
    NodoArbol(const T&dato, NodoArbol *izq, NodoArbol *der);
    NodoArbol<T>* getDer();
    NodoArbol<T>* getIzq();
    void setDer(NodoArbol<T> *p);
    void setIzq(NodoArbol<T> *p);
    T& getDato();
};


template<class T>
class AVL {
private:
    unsigned int numElementos=0;
    NodoArbol <T> *raiz;

    void rotDer(NodoArbol<T>* &nodo);
    void rotIzq(NodoArbol<T>* &nodo);

    //Metodos auxiliares
    void inorden_v(NodoArbol<T> *p, VDinamico<T*> &vector);
    void preorden_v(NodoArbol<T> *p, VDinamico<T*> vector);
    NodoArbol<T>* copia(NodoArbol<T> *p);

public:
    AVL<T>();
    AVL<T>(const AVL<T> &origen);   //En preorden y debe crear una copia identica
    AVL<T>& operator=(const AVL<T> &avl);   //Debe crear una copia identica
    bool inserta(T& dato);
    T* buscaRecursiva(T &dato); //busqueda recursiva
    T* buscaIterativa(T &dato); //busqueda iterativa
    VDinamico<T*> recorreInorden_v();
    unsigned int getNumElementos();
    unsigned int altura();
    NodoArbol<T> getIzq(NodoArbol<T> &p);
    NodoArbol<T> getDer(NodoArbol<T> &p);
    char getBal(NodoArbol<T> &p);
    ~AVL<T>() =default; //En postorden
    int calculaAltura(NodoArbol<T> *p, int altura);
};

template<typename T>
AVL<T>::AVL() {
    raiz = nullptr;
}
template<typename T>
NodoArbol<T>* AVL<T>::copia(NodoArbol<T> *p) {
    if (p == nullptr) {             //Si en el arbol orig no existe un nodo, no lo copiamos
        return nullptr;
    }
    NodoArbol<T> *otro = new NodoArbol<T>(p->dato); //Creamos el nodo
    otro->bal = p->bal;             //Copiamos el equilibrio del arbol origen
    numElementos++;                 //Aumentamos el tamaño del nuevo arbol
    otro->getIzq() = copia(p->getIzq());      //Copia del nodo de la izquierda de forma recursiva
    otro->der = copia(p->getDer());      //Copia del nodo de la derecha de forma recursiva

    return otro;
}

template<typename T>
AVL<T>::AVL(const AVL<T> &origen): raiz(nullptr)
{
    this->raiz = copia(origen.raiz);
}

template<class T>
NodoArbol<T>::NodoArbol(const T &dato, NodoArbol *izq, NodoArbol *der) { dato=0; izq=0; der=0;
}

template<class T>
NodoArbol<T>* NodoArbol<T>::getDer() {return izq; }

template<class T>
NodoArbol<T>* NodoArbol<T>::getIzq() { return der; }

template<class T>
void NodoArbol<T>::setDer(NodoArbol<T> *p) {this->der =p; }

template<class T>
void NodoArbol<T>::setIzq(NodoArbol<T> *p) {this->izq = p; }

template<class T>
T & NodoArbol<T>::getDato() {return dato; }

template<class T>
void AVL<T>::rotDer(NodoArbol<T> *&nodo) {
    NodoArbol<T> *y = nodo;
    NodoArbol<T> *z;

    nodo = z = y->izq;
    y->izq = z->der;
    z->der = y;
    y->bal--;
    if (z->bal > 0) y->bal -= z->bal;
    z->bal--;
    if(y->bal < 0) z->bal -= -y->bal;

}

template<class T>
void AVL<T>::rotIzq(NodoArbol<T> *&nodo) {
    NodoArbol<T> *y;
    NodoArbol<T> *z;

    y = nodo;
    nodo = z = y->der;
    y->der = z->izq;
    z->izq = y;
    y->bal++;
    if (z->bal < 0) y->bal += -z->bal;
    z->bal++;
    if(y->bal > 0) z->bal += y->bal;
}

template<typename T>
void AVL<T>::inorden_v(NodoArbol<T> *p, VDinamico<T*> &vector) {
    if (p != nullptr) {                 //Vemos si ese nodo existe realmente, sino, va hacia atrás en la recursividad
        inorden(p->getIzq(),vector);         //Hacemos una llamada recursiva al nodo de la izquierda
        vector.insertar(&p->getDato());      //Si este existe y es el ultimo, lo insertamos en el vector. Si no existe
                                        //  el nodo de la izquierda, insertamos el nodo padre en el vector
        inorden(p->getDer(),vector);         //hacemos una llamada recursiva al nodo de la derecha
    }
}

template<typename T>
VDinamico<T*> AVL<T>::recorreInorden_v() {
    VDinamico<T*> v;
    inorden(this->raiz,v);
    return v;               //Devuelve un vector de punteros a los elementos del AVL
}

template<class T>
unsigned int AVL<T>::getNumElementos() {return this->numElementos; }

template<class T>
unsigned int AVL<T>::altura() {
    return calculaAltura();
}

template<typename T>
NodoArbol<T> AVL<T>::getIzq(NodoArbol<T> &p) {return p.izq;}

template<typename T>
NodoArbol<T> AVL<T>::getDer(NodoArbol<T> &p) {return p.der;}

template<typename T>
char AVL<T>::getBal(NodoArbol<T> &p) {return p.bal; }

template<class T>
int AVL<T>::calculaAltura(NodoArbol<T> *p, int altura) { //PROBABLEMENTE ESTA MAL, NO TOCAR, NECESITO LA INSERCION
        int izq=0;
        int der =0;
        if(!p) return 0;
        if(p->getIzq()) {
            izq = altura+1;
                calculaAltura(p->getIzq(), izq);
        }
        if(p->getDer()) {
             der=altura+1;
                 calculaAltura(p->getDer(), der);

        }
    if(izq > der ) return  izq;
    return der;
}


template<typename T>
void AVL<T>::preorden_v(NodoArbol<T> *p, VDinamico<T *> vector) {
    if (p != nullptr) {
        vector.insertar(&p->dato);
        preorden(p->getIzq(),vector);
        preorden(p->getDer(),vector);
    }
}


template<typename T>
AVL<T> &AVL<T>::operator=(const AVL<T> &avl) {
    if (this != &avl) {
        if (this->raiz != nullptr) {
            //FALTA BORRAR LOS ELEMENTOS DEL ARBOL
        }
        this->raiz = copia(avl.raiz);
    }
    return *this;
}

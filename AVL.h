
#ifndef PRACTICA2_EEDD_AVL_H
#define PRACTICA2_EEDD_AVL_H
#endif //PRACTICA2_EEDD_AVL_H
#include "ListaDE.h"
#include "VDinamico.h"

template<class T>
class NodoArbol {
public:
    T dato;
    NodoArbol<T> *der,*izq;
    char bal = 0; //factor de equilibrio en un avl, 0: equilibrado; -1 desequilibrado por la izq; 1 por la der
    NodoArbol(const T&dato, NodoArbol *izq, NodoArbol *der);
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
    int calculaAltura(NodoArbol<T> *p, int altura);
    bool insertar_preorden(T &dato, NodoArbol<T> *p);
    int alturaNodo(NodoArbol<T> *p);
    T* busquedaAux(NodoArbol<T> *p, T &dato);
    void borrar(NodoArbol<T> *p);

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
    ~AVL<T>(); //En postorden
};

template<typename T>
AVL<T>::AVL():raiz(nullptr),numElementos(0) {}

template<typename T>
NodoArbol<T>* AVL<T>::copia(NodoArbol<T> *p) {
    if (p == nullptr) {             //Si en el arbol orig no existe un nodo, no lo copiamos
        return nullptr;
    }
    NodoArbol<T> *otro = new NodoArbol<T>(p->dato); //Creamos el nodo
    otro->bal = p->bal;             //Copiamos el equilibrio del nodo origen
    otro->izq = copia(p->izq);      //Copia del nodo de la izquierda de forma recursiva
    otro->der = copia(p->der);      //Copia del nodo de la derecha de forma recursiva

    return otro;
}

template<typename T>
AVL<T>::AVL(const AVL<T> &origen): raiz(nullptr)
{
    this->raiz = copia(origen.raiz);
}

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
        inorden(p->izq,vector);         //Hacemos una llamada recursiva al nodo de la izquierda
        vector.insertar(&p->dato);      //Si este existe y es el ultimo, lo insertamos en el vector. Si no existe
                                        //  el nodo de la izquierda, insertamos el nodo padre en el vector
        inorden(p->der,vector);         //hacemos una llamada recursiva al nodo de la derecha
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

template<class T>
int AVL<T>::calculaAltura(NodoArbol<T> *p, int altura) { //PROBABLEMENTE ESTA MAL, NO TOCAR, NECESITO LA INSERCION
        int izq=0;
        int der =0;
        if(!p) return 0;
        if(p->izq) {
            izq = altura+1;
                calculaAltura(p->izq, izq);
        }
        if(p->der) {
             der=altura+1;
                 calculaAltura(p->der, der);

        }
    if( izq > der ) return  izq;
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
            borrar(this->raiz);
            this->raiz = nullptr;
            numElementos = 0;
        }
        this->raiz = copia(avl.raiz);
        this->numElementos = avl.numElementos;
    }
    return *this;
}

template<class T>
bool AVL<T>::inserta(T &dato) {         //ACABAR METODO
    if (this->raiz == nullptr) {
        this->raiz->dato = dato;
        this->raiz->izq = nullptr;
        this->raiz->der = nullptr;
        return true;
    }

    NodoArbol<T> *p = this->raiz;
    insertar_preorden(dato, p);


}

template<class T>
bool AVL<T>::insertar_preorden(T &dato, NodoArbol<T> *p) {      //ACABAR METODO
    if (!p->izq || !p->der) {

        if ( p->dato == dato) {
            return false;
        }
        if (dato < p->dato  && !p->izq) {
            NodoArbol<T> nuevo = new NodoArbol<T>(dato,nullptr,nullptr);
            p->izq = nuevo;
            p->bal-1;

            return true;
        }
        if (dato > p->dato && !p->der) {

            return true;
        }

        //verificamos rotaciones
        if (alturaNodo(p->izq)- alturaNodo(p->der) == -2) { //desbalanceo izq

        }
        if (alturaNodo(p->izq)- alturaNodo(p->der) == 2) {
            // desbalanceo der
        }
    }
    if (dato < p->dato) {
        insertar_preorden(dato, p->izq);
    }if (dato > p->dato ){
        insertar_preorden(dato, p->der);
    }
}

template<class T>
int AVL<T>::alturaNodo(NodoArbol<T> *p) {
    if (!p->izq && !p->der ) return 0; // es nodo hoja
    if ((!p->izq && p->der) || (p->izq && !p->der)) return 1; // solo tiene un hijo

}

template<class T>
T* AVL<T>::buscaIterativa(T &dato) {
    if (this->raiz == nullptr) {
        throw out_of_range("[AVL::buscaIterativa]: El arbol esta vacio.");  //Si el arbol esta vacio, salta excepcion
    }

    NodoArbol<T> *p = this->raiz;

    while ( p != nullptr ) {        //Compruebo si ya pasó un nodo hoja
        if (p->dato == dato) {
            return &p->dato;        //Encuentra el dato
        } else if (p->dato > dato) {
                p = p->izq;         //Si el dato es mayor, me voy a la izquierda
                } else {
                    p = p->der;     //Si el dato es menor, me voy a la derecha
                }
    }

   throw out_of_range("[AVL::buscaIterativa]: El dato no se enuentra en el arbol"); //Si no encuentra el dato, salta excepcion

}

template<class T>
T *AVL<T>::buscaRecursiva(T &dato) {
    if (this->raiz == nullptr) {
        throw out_of_range("[AVL::buscaRecursiva]: El arbol esta vacio.");  //Si el arbol esta vacio, salta excepcion
    }

    return busquedaAux(this->raiz,dato);
}

template<class T>
T *AVL<T>::busquedaAux(NodoArbol<T> *p, T &dato) {

    if (p == nullptr) {
        throw out_of_range("[AVL::busquedaAux]: El dato no esta en el arbol");  //Si al final del nodo hoja todavia no
    }                                                                           //encontró el dato salta la excepcion

    if (p->dato == dato) {                      //Encontró el dato que buscaba
        return &p->dato;
    }

    if (dato > p->dato) {                       //Como el dato es mayor, voy por el camino de la derecha
        return busquedaAux(p->der,dato);
    }

    return busquedaAux(p->izq,dato);         //Como el dato es menor, voy por el camino de la izquierda
}

template<class T>
void AVL<T>::borrar(NodoArbol<T> *p) {
    if (p != nullptr) {        //Si no es un arbol vacio

        borrar(p->izq);
        borrar(p->der);

        delete p;
        p = nullptr;
    }
}

template<class T>
AVL<T>::~AVL() {
    borrar(this->raiz);
    this->raiz = nullptr;
    numElementos = 0;
}

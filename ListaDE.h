//
// Created by almar on 05/10/2026.
//

#ifndef PRACTICA2_EEDD_LISTADE_H
#define PRACTICA2_EEDD_LISTADE_H
#include "Iterador.h"
#include "Nodo.h"
#include <iostream>
using namespace std;

template<class T>
class ListaDE {

private:

    Nodo<T> *cabecera;
    Nodo<T> *cola;

public:

    /**
     * @brief Constructor por defecto de una lista doblemente enlazada
     */
    ListaDE<T>():cabecera(nullptr),cola(nullptr){}

    /**
     * Constructor por copia de uan lista doblemente enlazada
     * @param orig
     */
    ListaDE<T>(const ListaDE<T>& orig);

    /**
     * Operador asignacion de lista doblemente enlazada
     * @param lista
     * @return Devuelve la nueva lista tras la asignacion
     */
    ListaDE<T>& operator=(const ListaDE &lista);

    /**
     * @brief Devuelve el primerdato de la lista
     * @return Devuelve el primer dato de la lista
     */
    T& inicio();

    /**
     * @brief Devuelve el ultimo dato de la lista
     * @return Devuelve el ultimo dato de la lsita
     */
    T& fin();

    /**
     * @brief Devuelve un objeto iterador para iterar sobre una lista bidireccionalmente
     * @return Un objeto iterador
     */
    Iterador<T> iterador();

    /**
     * @brief Insertar un dato al principio de una lista
     * @param dato
     */
    void insertaInicio(const T &dato);

    /**
     * @brief Insertar un dato al final de una lista
     * @param dato
     */
    void insertaFin(const T &dato);

    /**
     * @brief Insertar un dato en la posicion anterior apuntada por un iterador
     * @param i iterador, apunta a la posición a partir de la cual se hará la inserción
     * @param dato objeto a insertar
     */
    void inserta(const Iterador<T> &i,const T &dato);

    /**
     * @brief Borra el primer elemento de la lista
     */
    void borraInicio();

    /**
     * @brief Borra el ultimo elemento de la lista
     */
    void borraFinal();

    /**
     * @brief Borra el elemento de la lista referenciado por un iterador
     * @param i
     */
    void borra(const Iterador<T> &i);

    /**
     * @brief Devuelve de forma eficiente el numero de elementos de la lista
     * @return numero de elementosde la lista
     */
    int tam();


    ListaDE<T> &concatena(const ListaDE<T> &lista);      //Devuelve una copia de las dos listas unidas
    ListaDE<T>& operator+(const ListaDE<T> &lista);      //A la primera lista le agrego la segunda lista

    /**
     * @brief Destructor de la clase ListaDE
     */
    ~ListaDE();
};

template<class T>
ListaDE<T>::ListaDE(const ListaDE<T> &orig) {       //Comprobamos si la lista está vacía
    if (orig.cabecera == nullptr) {
        this->cabecera = nullptr;
        this->cola = nullptr;
    } else if (orig.cabecera == orig.cola) {            //Comprobamos si hay un solo elemento en la lista
        this->cabecera = new Nodo<T>(orig.cabecera->dato,nullptr,nullptr);
        this->cola = cabecera;
    } else { //hay mas de un elemetno
        this->cabecera = new Nodo<T>(orig.cabecera->dato,nullptr,nullptr);
        this->cola = cabecera;
        Iterador<T> i = orig.cabecera->sig;

        while (i.haySiguiente()) {      //La condicion deja fuera al ultimo dato
            insertaFin(i.dato());
            i.siguiente();
        }
        insertaFin(i.dato());       //El ultmo dato hay que hacerlo aparte
    }
}

template<class T>
ListaDE<T> &ListaDE<T>::operator=(const ListaDE &lista) {
    if (this != &lista) {
        while (this->cola != nullptr) {       //Limpiamos la cola antes de sustituir
            this->borraInicio();
        }

        if (lista.cabecera == nullptr) { //no hay elementos
            this->cabecera = nullptr;
            this->cola = nullptr;

        } else if (lista.cabecera == lista.cola) {            //Comprobamos si hay un solo elemento en la lista
            this->cabecera = new Nodo<T>(lista.cabecera->dato,nullptr,nullptr);
            this->cola = cabecera;

        } else {
            this->cabecera = new Nodo<T>(lista.cabecera->dato,nullptr,nullptr);
            this->cola = cabecera;
            Iterador<T> i = lista.cabecera->sig;

            while (i.haySiguiente()) {      //La condicion deja fuera al ultimo dato
                insertaFin(i.dato());
                i.siguiente();
            }
            insertaFin(i.dato());       //El ultmo dato hay que hacerlo aparte
        }

    }
    return *this;
}

template<typename T>
T& ListaDE<T>::inicio() {
    if (cabecera==nullptr) {
        throw invalid_argument("[ListaDE::inicio]: La lista esta vacia");
    }
    return cabecera->dato;
}

template<typename T>
T& ListaDE<T>::fin() {
    if (cola==nullptr) {
        throw invalid_argument("[ListaDE::fin]: La lista esta vacia");
    }
    return cola->dato;
}

template<typename T>
void ListaDE<T>::insertaInicio(const T& dato) {
    Nodo<T> *p = new Nodo<T>(dato,nullptr,nullptr);

    if (cola==nullptr) {        //Comprobar si la lista esta vacia
        cabecera = p;
        cola=p;
    } else {                    //Insertar por la cabecera
        p->sig=cabecera;
        cabecera->ant=p;
        cabecera=p;
    }

}

template<typename T>
void ListaDE<T>::insertaFin(const T &dato) {
    Nodo<T> *p = new Nodo<T>(dato,nullptr,nullptr);

    if (cola==nullptr) {       //Comprobar si la lista esta vacia
        cabecera = p;
        cola=p;
    } else {                   //Insertar por la cola
        p->ant=cola;
        cola->sig=p;
        cola=p;
    }
}

template<typename T>
void ListaDE<T>::inserta(const Iterador<T> &i, const T &dato) {
    if (i.nodo==nullptr) {
        throw invalid_argument("[ListaDE::inserta]: Parametro no valido");
    }
    Nodo<T> *nuevo = new Nodo<T>(dato,nullptr,nullptr);
    if (cabecera==nullptr) {            //Comprobar si la lista esta vacia
        cabecera=nuevo;
        cola=nuevo;

    } else if (i.nodo==cabecera) {      //Comprobar si el iterador apunta a la cabecera
        cabecera->ant=nuevo;
        nuevo->sig=cabecera;
        cabecera=nuevo;

        } else if (i.nodo==cola) {      //Comprobar si el iterador apunta a la cola
            Nodo<T> *t = cola->ant;
            cola->ant=nuevo;
            nuevo->sig=cola;
            nuevo->ant=t;
            t->sig=nuevo;

        } else {                    //Posicion intermedia en lista con varios elementos
            Nodo<T> *anterior = i.nodo->ant;
            i.nodo->ant=nuevo;
            nuevo->sig=i.nodo;
            nuevo->ant=anterior;
            anterior->sig=nuevo;
        }
}

template<typename T>
void ListaDE<T>::borraInicio() {
    if (cabecera == nullptr) {      //Comprobamos si la lista esta vacia
        throw out_of_range("[ListaDE::borraInicio]: No hay elementos para borrar en la lista");
    }

    Nodo<T> *p = cabecera;
    if (cabecera==cola) {           //Comprobamos si solo hay un elemento en la lista
        cabecera=nullptr;
        cola=nullptr;

    } else {                        //Hay mas de un elemento en la lista
        cabecera=cabecera->sig;
        cabecera->ant=nullptr;
    }

    delete p;
}

template<typename T>
void ListaDE<T>::borraFinal() {
    if (cabecera == nullptr) {      //Comprobamos si la lista esta vacia
        throw out_of_range("[ListaDE::borraFinal]: No hay elementos para borrar en la lista");
    }

    Nodo<T> *p = cola;
    if (cabecera == cola) {         //Comprobamos si solo hay un elemento en la lista
        cabecera=nullptr;
        cola=nullptr;

    } else {                        //Hay mas de un elemento en la lista
        cola=cola->ant;
        cola->sig=nullptr;
    }

    delete p;
}

template<class T>
void ListaDE<T>::borra(const Iterador<T> &i) {
    if (i.nodo == nullptr) {        //Comprobamos que el iterador apunte a un nodo
        throw invalid_argument("[ListaDE::borra]: No hay elementos para borrar en la lista");
    }
    if (cabecera == nullptr) {      //Comprobamos si la lista esta vacia
        throw out_of_range("[ListaDE::borra]: no hay elementos en la lista para borrar ");
    }

    Nodo<T> *siguiente = i.nodo->sig;
    Nodo<T> *anterior = i.nodo->ant;
    if (cabecera == cola) {         //Comprobamos si solo hay un elemento en la lista
        cabecera = nullptr;
        cola = nullptr;

    } else if (i.nodo == cabecera) {
        cabecera=siguiente;
        cabecera->ant=nullptr;

    } else if (i.nodo == cola) {
        cola = anterior;
        cola->sig = nullptr;

    } else {
        anterior->sig = siguiente;
        siguiente->ant = anterior;
    }

    delete i.nodo;
}

template<class T>
int ListaDE<T>::tam() {
    int num=0;
    if (cabecera != nullptr) {          //Comprobar si la lista está vacía
        Iterador<T> i = cabecera;

        while (i.haySiguiente() ) {
            i.siguiente();
            num++;
        }
        num++;
    }
    return num;
}

template<class T>
ListaDE<T>::~ListaDE() {
    while (cabecera != nullptr) {
        borraFinal();
    }
}

template<class T>
ListaDE<T>& ListaDE<T>::operator+(const ListaDE<T> &lista) {
    if (lista.cabecera != nullptr) {
        Iterador<T> i = lista.cabecera;
        while (i.nodo != nullptr) {
            this->insertaFin(i.dato());
            i.siguiente();
        }
    }

    return *this;
}

template<class T>
ListaDE<T>& ListaDE<T>::concatena(const ListaDE<T> &lista) {
    ListaDE<T> listaNueva;                       //Creamos una lista nueva por copia que contenga a la primera
    if (this->cabecera == nullptr) { // si la lista actual esta vacia copiamos unicamente los nodos de las lista del parametro
        listaNueva(lista);
    } else if (lista.cabecera == nullptr){ // si la lista del parametro esta vacia copiamos unicamente los valores de la lista actual
        listaNueva(this);
    } else { //ambas tienen valores
        listaNueva(this);
        Iterador<T> i = lista.cabecera;
        while (i.nodo != nullptr) {                 //Añadimos a esta nueva lista, la segunda
            listaNueva.insertaFin(i.dato());
            i.siguiente();
        }
    }

    return *listaNueva;     //Devolvemos una nueva lista con los contenidos tanto de la primera como de la segunda juntos
}

template<class T>
 Iterador<T> ListaDE<T>::iterador() {
    return Iterador<T>(cabecera);
}


#endif //PRACTICA2_EEDD_LISTADE_H

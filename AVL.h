
#ifndef PRACTICA2_EEDD_AVL_H
#define PRACTICA2_EEDD_AVL_H

#include "VDinamico.h"
#include "NodoArbol.h"


/**
 * @brief Clase plantilla que implementa un árbol binario de búsqueda auto-balanceado (AVL).
 * @tparam T Tipo de dato que almacenará el árbol AVL.
 */
template<class T>
class AVL {
private:
    unsigned int numElementos=0;
    NodoArbol <T> *raiz;

    /**
     * @brief Realiza una rotación simple a la derecha en el subárbol dado.
     * @param[in,out] nodo Referencia al puntero del nodo raíz del subárbol a rotar.
     */
    void rotDer(NodoArbol<T>* &nodo);
    /**
     * @brief Realiza una rotación simple a la izquierda en el subárbol dado.
     * @param[in,out] nodo Referencia al puntero del nodo raíz del subárbol a rotar.
     */
    void rotIzq(NodoArbol<T>* &nodo);

    //Metodos auxiliares

    /**
     * @brief Recorre en inorden el subárbol e inserta punteros a sus elementos en un vector dinámico.
     * @param p Nodo raíz del subárbol a recorrer.
     * @param[out] vector Vector dinámico donde se almacenarán los punteros a los datos.
     */
    void inorden_v(NodoArbol<T> *p, VDinamico<T*> &vector);

    /**
     * @brief Recorre en preorden el subárbol e inserta punteros a sus elementos en un vector dinámico.
     * @param p Nodo raíz del subárbol a recorrer.
     * @param[out] vector Vector dinámico donde se almacenarán los punteros a los datos.
     */
    void preorden_v(NodoArbol<T> *p, VDinamico<T*> vector);

    /**
     * @brief Realiza una copia profunda recursiva de una estructura de árbol.
     * @param p Nodo raíz del subárbol a copiar.
     * @return NodoArbol<T>* Puntero a la raíz de la nueva estructura copiada.
     */
    NodoArbol<T>* copia(NodoArbol<T> *p);

    /**
     * @brief Calcula la altura máxima de un subárbol a partir del nodo dado.
     * @param p Nodo desde el que se calcula la altura.
     * @return int Altura total del subárbol.
     */
    int calculaAltura(NodoArbol<T> *p);

    /**
     * @brief Método auxiliar recursivo para insertar un dato en preorden comprobando balanceo.
     * @param[in] dato Dato a insertar.
     * @param p Nodo actual del recorrido.
     * @return true Si se realizó la inserción con éxito.
     * @return false Si no se pudo insertar (por ejemplo, por estar duplicado).
     */
    int insertar_preorden(T &dato, NodoArbol<T> *&p);

    /**
     * @brief Calcula la altura aproximada de un nodo según la presencia de sus hijos.
     * @param p Puntero al nodo a evaluar.
     * @return int Retorna 0 si es hoja o nulo, 1 si tiene un solo hijo.
     */
    int alturaNodo(NodoArbol<T> *p);

    /**
     * @brief Método auxiliar recursivo para la búsqueda de un dato en el árbol.
     * @param p Nodo actual en el recorrido de búsqueda.
     * @param dato Dato a buscar.
     * @return T* Puntero al dato encontrado.
     * @throw std::out_of_range Si el dato no se encuentra en el subárbol.
     */
    T* busquedaAux(NodoArbol<T> *p, T &dato);

    /**
     * @brief Elimina recursivamente en postorden todos los nodos de un subárbol y libera su memoria.
     * @param p Nodo raíz del subárbol a borrar.
     */
    NodoArbol<T> *borrarNodo(NodoArbol<T> *p);

public:

    /**
     * @brief Constructor por defecto de la clase AVL. Crea un árbol vacío.
     */
    AVL<T>();

    /**
     * @brief Constructor de copia. Crea una copia idéntica del árbol origen.
     * @param origen Árbol AVL a copiar.
     */
    AVL<T>(const AVL<T> &origen);   //En preorden y debe crear una copia identica

    /**
         * @brief Operador de asignación. Realiza una copia idéntica del árbol AVL dado.
         * @param avl Árbol AVL a copiar.
         * @return AVL<T>& Referencia al árbol actual asignado.
         */
    AVL<T>& operator=(const AVL<T> &avl);   //Debe crear una copia identica

    /**
         * @brief Inserta un nuevo elemento en el árbol AVL manteniéndolo balanceado.
         * @param dato Dato a insertar.
         * @return true Si la inserción fue exitosa, false en caso contrario.
         */
    bool inserta(T &dato);

    /**
     * @brief Busca un dato en el árbol de forma recursiva.
     * @param dato Referencia al dato a buscar.
     * @return T* Puntero al dato encontrado en el árbol.
     * @throw std::out_of_range Si el árbol está vacío o el elemento no existe.
     */
    T* buscaRecursiva(T &dato); //busqueda recursiva

    /**
     * @brief Busca un dato en el árbol de forma iterativa.
     * @param dato Referencia al dato a buscar.
     * @return T* Puntero al dato encontrado en el árbol.
     * @throw std::out_of_range Si el árbol está vacío o el elemento no existe.
     */
    T* buscaIterativa(T &dato); //busqueda iterativa

    /**
     * @brief Realiza un recorrido en inorden y devuelve un vector dinámico con los elementos.
     * @return VDinamico<T>* Vector dinámico con los punteros a los elementos del AVL.
     */
    VDinamico<T*> *recorreInorden_v();

    /**
     * @brief Obtiene el número total de elementos almacenados en el árbol.
     * @return unsigned int Cantidad de elementos del AVL.
     */
    unsigned int getNumElementos();

    /**
     * @brief Calcula y devuelve la altura máxima del árbol.
     * @return unsigned int Altura del árbol.
     */
    unsigned int altura();

    /**
     * @brief Destructor de la clase AVL. Libera la memoria consumida por todos sus nodos en postorden.
     */
    ~AVL<T>(); //En postorden

    /**
     * @brief Elimina de forma recursiva un nodo con un valor específico dentro de un árbol binario de búsqueda (ABB).
     *
     * @tparam T Tipo de dato almacenado en el árbol.
     * @param dato Referencia al dato que se desea buscar y eliminar.
     * @param[in,out] p Puntero (idealmente pasado por referencia `NodoArbol<T>* &p`) al nodo actual a evaluar.
     * @return NodoArbol<T>* Retorna nullptr al finalizar la operación.
     */
    NodoArbol<T> *borraDato(T &dato, NodoArbol<T> *p);
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



template<typename T>
void AVL<T>::rotDer(NodoArbol<T> *&nodo) {
    NodoArbol<T> *q = nodo, *l;
    nodo = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;

}

template<typename T>
void AVL<T>::rotIzq(NodoArbol<T> *&nodo) {
    NodoArbol<T>*q=nodo, *r;
    nodo=r=q->der;
    q->der=r->izq;
    r->izq=q;
    q->bal++;
    if(r->bal<0)q->bal+= -r->bal;
    r->bal++;
    if(q->bal>0) r->bal +=q->bal;
}

template<typename T>
void AVL<T>::inorden_v(NodoArbol<T> *p, VDinamico<T*> &vector) {
    if (p != nullptr) {                 //Vemos si ese nodo existe realmente, sino, va hacia atrás en la recursividad
        inorden_v(p->izq,vector);         //Hacemos una llamada recursiva al nodo de la izquierda
        vector.insertar(&p->dato);      //Si este existe y es el ultimo, lo insertamos en el vector. Si no existe
        //  el nodo de la izquierda, insertamos el nodo padre en el vector
        inorden_v(p->der,vector);         //hacemos una llamada recursiva al nodo de la derecha
    }
}

template<typename T>
VDinamico<T*>* AVL<T>::recorreInorden_v() {
    VDinamico<T*> *v = new VDinamico<T*>();
    inorden_v(this->raiz,*v);
    return v;               //Devuelve un vector de punteros a los elementos del AVL
}

template<typename T>
unsigned int AVL<T>::getNumElementos() {return this->numElementos; }

template<typename T>
unsigned int AVL<T>::altura() {
    return calculaAltura(this->raiz);
}

template<typename T>
int AVL<T>::calculaAltura(NodoArbol<T> *p) {
        int  h=-1; //no se cuenta el nodo raiz
        if(p) {
            int izq = calculaAltura(p->izq);
            int der=calculaAltura(p->der);

            h = max(izq,der);
            h+=1;
        }

    return h;
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
            borrarNodo(this->raiz);
            this->raiz = nullptr;
            numElementos = 0;
        }
        this->raiz = copia(avl.raiz);
        this->numElementos = avl.numElementos;
    }
    return *this;
}

template<typename T>
bool AVL<T>::inserta(T &dato) {

    if( insertar_preorden(dato, this->raiz) ==-1) {
        return false ;
    }
    return true;
}

template<typename T>
int AVL<T>::insertar_preorden(T &dato, NodoArbol<T> *&p) {
        NodoArbol<T> *c = p;
        int deltaH=0; //medidor de balanceo del arbol

        if(!c) {
            c =  new NodoArbol<T>(dato,0,0);
            p = c;
            deltaH =1;
            this->numElementos++;
        }
        if (dato < c->dato ) { //la inserción se hara por la izq del nodo actual
            if(insertar_preorden(dato, c->izq)) {
                c->bal++;
                if(c->bal == 1) deltaH =1;

                else if(c->bal == 2) { //desequilibrio por la izq
                    if(c->izq->bal == -1) rotIzq(c->izq); // rotacion doble izq-der
                    rotDer(p); //rot simple der
                }
            }
        }
        else if (dato > c->dato ) { //la inserciñon se hace a la derecha del nodo actual
           if(insertar_preorden(dato, c->der)) {
               c->bal--;

               if(c->bal==-1) deltaH =1;

               else if(c->bal ==-2) {
                   if(c->der->bal == 1) rotDer(c->der); //rotacion doble (der-izq)
                   rotIzq(p); //rot simple izq
               }
           }
        }
        if(c->dato == dato && c != raiz) return -1; // indica error en repetidos

         return deltaH;




}

template<typename T>
int AVL<T>::alturaNodo(NodoArbol<T> *p) {
    if(!p) return  0;
    if (!p->izq && !p->der ) return 0; // es nodo hoja
    if ((!p->izq && p->der) || (p->izq && !p->der)) return 1; // solo tiene un hijo
    return 0;

}

template<typename T>
T* AVL<T>::buscaIterativa(T &dato) {
    if (this->raiz == nullptr) {
        throw out_of_range("[AVL::buscaIterativa]: El arbol esta vacio.");  //Si el arbol esta vacio, salta excepcion
    }

    NodoArbol<T> *p = this->raiz;

    while ( p != nullptr ) {        //Compruebo si ya pasó un nodo hoja
        if (p->dato == dato) {
            return &p->dato;        //Encuentra el dato
        }
        if (p->dato > dato) {
                p = p->izq;         //Si el dato es mayor, me voy a la izquierda
                } else {
                    p = p->der;     //Si el dato es menor, me voy a la derecha
                }
    }

   throw out_of_range("[AVL::buscaIterativa]: El dato no se enuentra en el arbol"); //Si no encuentra el dato, salta excepcion

}

template<typename T>
T *AVL<T>::buscaRecursiva(T &dato) {
    if (this->raiz == nullptr) {
        throw out_of_range("[AVL::buscaRecursiva]: El arbol esta vacio.");  //Si el arbol esta vacio, salta excepcion
    }

    return busquedaAux(this->raiz,dato);
}

template<typename T>
T *AVL<T>::busquedaAux(NodoArbol<T> *p, T &dato) {
    if (p == nullptr) {
       return nullptr;
    }                                                                           //encontró el dato salta la excepcion

    if (p->dato == dato) {                      //Encontró el dato que buscaba
        return &p->dato;
    }

    if (dato > p->dato ) {                       //Como el dato es mayor, voy por el camino de la derecha
        return  busquedaAux(p->der,dato);
    }


    return  busquedaAux(p->izq,dato);         //Como el dato es menor, voy por el camino de la izquierda

}
template<typename T>
NodoArbol<T> *AVL<T>::borrarNodo(NodoArbol<T> *p) {
   NodoArbol<T> *borrado;
    if(p) {
        if(p->izq) {
            return borrarNodo(p->izq);
        }else {
            borrado=p;
            p = p->der;
        }
    }
    return borrado;
}

template<typename T>
AVL<T>::~AVL() {
    borrarNodo(this->raiz);
    this->raiz = nullptr;
    numElementos = 0;
}

template<class T>
NodoArbol<T> *AVL<T>::borraDato(T &dato, NodoArbol<T> *p) {

    if(p) {
        if(dato < p->dato) {
            borraDato(dato, p->izq);
        }
        else if(dato> p->dato) {
            borraDato(dato, p->der);
        }
        else { //el dato a eliminar es ese
            NodoArbol<T> *aux =p;
            if(!p->der) p = p->izq;
            else if(p->izq && p->der) {
                aux = borrarNodo(p->der);
                p->dato = aux->dato;
            }
            delete aux;
        }
    }
    return nullptr;
}
#endif //PRACTICA2_EEDD_AVL_H

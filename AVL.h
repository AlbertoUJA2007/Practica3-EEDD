
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

};
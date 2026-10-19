cmake_minimum_required(VERSION 3.29.6)
project(Practica2_EEDD)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Practica2_EEDD
        ListaDE.h
        VDinamico.h
        Especie.h
        Especie.cpp
        LectorCSV.h
        LectorCSV.cpp
        main.cpp
        Parque.cpp
        Parque.h
        ControlParques.cpp
        ControlParques.h
        VDinamico.h
        Iterador.h
        Arbol.cpp
        Arbol.h
        AVL.h
)

#include "Celda.h"
#include <iostream>

using namespace std;

Celda::Celda(int fila, int columna){
    this->fila=fila;
    this->columna=columna;
    tieneMina=false;

    revelada = false;
    conBandera = false;
    minasAdyacentes = 0;
}

void Celda::asignarMina(char MINA){
    this->MINA=MINA;
    tieneMina=true;
}

int Celda::getF(){
    return fila;
}

int Celda::getC(){
    return columna;
}

bool Celda::checkStatus(){
    return tieneMina;
}

void Celda::revelar(){
    revelada = true;
}

bool Celda::estaRevelada(){
    return revelada;
}

void Celda::alternarBandera(){
    conBandera = !conBandera;
}

bool Celda::tieneBandera(){
    return conBandera;
}
void Celda::setMinasAdyacentes(int cant){
    minasAdyacentes = cant;
}

int Celda::getMinasAdyacentes(){
    return minasAdyacentes;
}

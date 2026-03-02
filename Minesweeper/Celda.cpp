#include "Celda.h"
#include <iostream>

using namespace std;

Celda::Celda(int f, int c){
    fila=f;
    columna=c;
    tieneMina=false;

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

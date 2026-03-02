#include "Celda.h"
#include <iostream>

using namespace std;

Celda::Celda(int f, int c){
    fila=f;
    columna=c;
    tieneMina=false;

}

Celda::asignarMina(char MINA){
    this->MINA=MINA;
    tieneMina=true;
}

Celda::getF(){
    return fila;
}

Celda::getC(){
    return columna;
}


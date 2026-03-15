#include "Celda.h"

Celda::Celda(int fila, int columna){
    this->fila = fila;
    this->columna = columna;

    tieneMina = false;
    revelada = false;
    conBandera = false;
    minasAdyacentes = 0;
}

void Celda::setMinasAdyacentes(int cantidad){
    minasAdyacentes = cantidad;
}

void Celda::revelar(){
    revelada = true;
}

void Celda::alternarBandera(){
    conBandera = !conBandera;
}

bool Celda::tieneBandera() const{
    return conBandera;
}

void Celda::asignarMina(){
    tieneMina = true;
}

int Celda::getFila() const{
    return fila;
}

int Celda::getColumna() const{
    return columna;
}

bool Celda::getTieneMina() const{ //getTieneMina me parece mejor nombre tbh
    return tieneMina;
}

int Celda::getMinasAdyacentes() const{
    return minasAdyacentes;
}

bool Celda::estaRevelada() const{
    return revelada;
}

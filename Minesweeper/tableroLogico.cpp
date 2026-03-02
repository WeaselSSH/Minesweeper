#include "tableroLogico.h"
#include <iostream>
#include <vector>

using namespace std;


tableroLogico::tableroLogico(int numFilas, int numColumnas){
    this->numFilas=numFilas;
    this->numColumnas=numColumnas;

    //Ciclo que inicializaria el tablero de juego segun las medidas indicadas
    tablero.reserve(numFilas);
    for(int i=0; i<numFilas; i++){

        //OJO....PRIMERO SE INICIALIZA Y LUEGO RESERVA...NO AL MISMO TIEMPO XD
        vector<Celda> vectorFila;

        vectorFila.reserve(numColumnas);

        for(int j=0; j<numColumnas; j++){
            Celda newCelda(i, j);
            vectorFila.push_back(newCelda);
        }

        tablero.push_back(vectorFila);
    }
}

void tableroLogico::getFilas(){
    return numFilas;
}

void tableroLogico::getColumnas(){
    return numColumnas;
}

Celda tableroLogico::obtenerCelda(int fila, int columna){

    //Ciclo que recorre el vector principal del tablero, el cual controla las filas
    for(int i=0; i<numFilas; i++){

        //se extrae el vector almacenado en cada posicion de fila
        vector<Celda> vectorFila=tablero.at(i);

        //se recorre dicho vector, el cual contendra elementos....las posiciones internas del vectorfila vendrian a ser igual a las columnas
        for(int j=0; j<numColumnas; j++){
            Celda celdatemp = vectorFila.at(j);

            if(celdaColumna.getF()==fila && celdaColumna.getC()==columna){
                return celdatemp;
            }
        }
    }
}



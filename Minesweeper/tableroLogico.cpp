#include "tableroLogico.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


tableroLogico::tableroLogico(int numFilas, int numColumnas, int numMinas){
    this->numFilas=numFilas;
    this->numColumnas=numColumnas;
    this ->numMinas= numMinas;

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

int tableroLogico::getFilas(){
    return numFilas;
}

int tableroLogico::getColumnas(){
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

            if(celdatemp.getF()==fila && celdatemp.getC()==columna){
                return celdatemp;
            }
        }
    }
}


void tableroLogico::colocarMinas(vector<vector<Celda>> &tablero, int cont, int randF, int randC ){

    //este randtime tendria que ir en el main del juego, ¿verda?
    srand(time(0));

    if(cont==numMinas){
        return;
    }

    int f=randF;
    int c= randC;

    //recorrido de tablero para ver colocar mina
    for(int i=0; i<numFilas; i++){
        vector <Celda> vectorFila = tablero.at(i);

        for(int j=0; j<numColumnas; j++){
            Celda celdatemp= vectorFila.at(j);


            int cF=celdatemp.getF();
            int cC=celdatemp.getC();


            //primer indicador= son las mismas coordenadas
            if(f==cF && c==cC){

                //segundo indicador, que la celda obtenida no tiene ya una mina
                if(!celdatemp.checkStatus()){
                    celdatemp.asignarMina('*'); //por el momento la mina se representa por un '*'
                }else{
                    colocarMinas(tablero, cont+1, rand()%numFilas, rand()%numColumnas);
                }
            }else{
                colocarMinas(tablero, cont, rand()%numFilas, rand()%numColumnas);
            }
        }
    }
}


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

Celda &tableroLogico::obtenerCelda(int fila, int columna){

    /*
    Creo que al ponerle paso por referencia no es necesario recorrerlo del todo
    solo es de retonrar el valor de fila y columna igualmente lo dejo comentado por las dudas xd
    */

    // //Ciclo que recorre el vector principal del tablero, el cual controla las filas
    // for(int i=0; i<numFilas; i++){

    //     //se extrae el vector almacenado en cada posicion de fila
    //     vector<Celda> vectorFila=tablero.at(i);

    //     //se recorre dicho vector, el cual contendra elementos....las posiciones internas del vectorfila vendrian a ser igual a las columnas
    //     for(int j=0; j<numColumnas; j++){
    //         Celda celdatemp = vectorFila.at(j);

    //         if(celdatemp.getF()==fila && celdatemp.getC()==columna){
    //             return celdatemp;
    //         }
    //     }
    // }

    return tablero[fila][columna];
}

//Creo que se puede optimizar esto pero aun no se como
void tableroLogico::colocarMinas(vector<vector<Celda>> &tablero){

    // if(cont==numMinas){
    //     return;
    //     cout<<"Se han colocado todas las minas"<<endl;
    // }

    // int f=randF;
    // int c= randC;

    // //recorrido de tablero para ver colocar mina
    // for(int i=0; i<numFilas; i++){
    //     vector <Celda> vectorFila = tablero.at(i);

    //     for(int j=0; j<numColumnas; j++){
    //         Celda celdatemp= vectorFila.at(j);


    //         int cF=celdatemp.getF();
    //         int cC=celdatemp.getC();


    //         //primer indicador= son las mismas coordenadas
    //         if(f==cF && c==cC){

    //             //segundo indicador, que la celda obtenida no tiene ya una mina
    //             if(!celdatemp.checkStatus()){
    //                 celdatemp.asignarMina('*'); //por el momento la mina se representa por un '*'
    //             }else{
    //                 colocarMinas(tablero, cont+1, rand()%numFilas, rand()%numColumnas);
    //             }
    //         }else{
    //             colocarMinas(tablero, cont, rand()%numFilas, rand()%numColumnas);
    //         }
    //     }
    // }


    int colocadas = 0;

    while (colocadas < numMinas) {
        // Generamos coordenadas aleatorias en cada intento
        int f = rand() % numFilas;
        int c = rand() % numColumnas;

        // Accedemos directamente a la celda (sin recorrer todo el tablero)
        // Usamos referencia (&) para modificar la celda real en el tablero
        Celda &celda = tablero.at(f).at(c);

        // Verificamos si ya tiene una mina
        if (!celda.checkStatus()) {
            celda.asignarMina('*');
            cout<<"Mina colocada en "<<f<<","<<c<<endl;
            colocadas++;
        }

    }


    cout<<"Se han colocado todas las minas "<< colocadas<<endl;

}

//FLOOD FILL
void tableroLogico::revelarCelda(int f, int c) {

    // Validar limites del tablero
    if (f < 0 || f >= numFilas || c < 0 || c >= numColumnas){
        return;
    }

    Celda& actual = tablero[f][c];

    // Si ya está revelada o tiene bandera, no hacer nada
    if (actual.estaRevelada() || actual.tieneBandera()){
        return;
    }

    // Revelar
    actual.revelar();

    // Si es una celda vacía expandir a los vecinos como chambre
    if (actual.getMinasAdyacentes() == 0 && !actual.checkStatus()) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                revelarCelda(f + x, c + y);
            }
        }
    }
}





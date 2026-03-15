#include "tableroLogico.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

tableroLogico::tableroLogico(int numFilas, int numColumnas, int numMinas){
    this->numFilas = numFilas;
    this->numColumnas = numColumnas;
    this->numMinas = numMinas;

    //inicializamos conteo de banderas en 0
    numBanderasPuestas = 0; //pues ya que inicia en 0 lo puse en 0 de verdad en vez de numMinas

    //Ciclo que inicializaria el tablero de juego segun las medidas indicadas
    tablero.reserve(numFilas);
    for(int i = 0; i < numFilas; i++){
        //OJO....PRIMERO SE INICIALIZA Y LUEGO RESERVA...NO AL MISMO TIEMPO XDsssssssssss
        vector<Celda> vectorFila;
        vectorFila.reserve(numColumnas);

        for(int j = 0; j < numColumnas; j++){
            Celda newCelda(i, j);
            vectorFila.push_back(newCelda);
        }
        tablero.push_back(vectorFila);
    }
}

int tableroLogico::getFilas() const{
    return numFilas;
}

int tableroLogico::getColumnas() const{
    return numColumnas;
}

Celda &tableroLogico::obtenerCelda(int fila, int columna){

    /*
    Creo que al ponerle paso por referencia no es necesario recorrerlo del todo
    solo es de retonrar el valor de fila y columna igualmente lo dejo comentado por las dudas xd
    */

    //efectivamente solo es de retornar y ya

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
//void tableroLogico::colocarMinas(vector<vector<Celda>> &tablero){
void tableroLogico::colocarMinas(){

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
        int fila = rand() % numFilas;
        int columna = rand() % numColumnas;

        // Accedemos directamente a la celda (sin recorrer todo el tablero)
        // Usamos referencia (&) para modificar la celda real en el tablero
        Celda &celda = tablero.at(fila).at(columna);

        // Verificamos si ya tiene una mina
        if (!celda.getTieneMina()) {
            celda.asignarMina();
            cout<<"Mina colocada en " << fila << "," << columna << endl;
            colocadas++;
        }
    }

    cout<<"Se han colocado todas las minas "<< colocadas<<endl;
}

void tableroLogico::calcularMinasAdyacentes() {
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            Celda& celda = tablero[i][j];

            // Las celdas con mina no necesitan contador
            if (celda.getTieneMina()) continue;

            int contador = 0;

            // Revisar los 8 vecinos
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue; // saltar la celda misma

                    int vecFila = i + x;
                    int vecColumna = j + y;

                    // Validar que el vecino esté dentro del tablero
                    if (vecFila >= 0 && vecFila < numFilas &&
                        vecColumna >= 0 && vecColumna < numColumnas) {
                        if (tablero[vecFila][vecColumna].getTieneMina()) {
                            contador++;
                        }
                    }
                }
            }

            celda.setMinasAdyacentes(contador);
        }
    }
}

//FLOOD FILL
void tableroLogico::revelarCelda(int fila, int columna) {

    // Validar limites del tablero
    if (fila < 0 || fila >= numFilas || columna < 0 || columna >= numColumnas) return;

    Celda &actual = tablero[fila][columna];

    // Si ya está revelada o tiene bandera, no hacer nada
    if (actual.estaRevelada() || actual.tieneBandera()) return;

    // Revelar
    actual.revelar();

    // Si es una celda vacía expandir a los vecinos como chambre
    if (actual.getMinasAdyacentes() == 0 && !actual.getTieneMina()) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                revelarCelda(fila + x, columna + y);
            }
        }
    }
}

bool tableroLogico::verificarVictoria(){
    for(int fila = 0; fila < numFilas; fila++){
        for(int columna = 0; columna < numColumnas; columna++){
            Celda &celda = obtenerCelda(fila, columna);
            if(!celda.getTieneMina() && !celda.estaRevelada()) return false;
        }
    }
    return true;
}

bool tableroLogico::verificarDerrota(int fila, int columna) {
    return tablero[fila][columna].getTieneMina() && tablero[fila][columna].estaRevelada();
}

void tableroLogico::alterarConteoBanderas(Celda &celdaEvaluar){
    //antes la logica estaba al reves pero ya lo arregle (aaa no puedo poner tildes)
    if(celdaEvaluar.tieneBandera()){
        numBanderasPuestas++;
    }else{
        numBanderasPuestas--;
        if (numBanderasPuestas < 0) numBanderasPuestas = 0; // en caso que quede negativo el contador
    }
}

int tableroLogico::getNumBanderasPuestas() const{
    return numBanderasPuestas;
}

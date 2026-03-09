//Esta clase de tableroLogico servira como controlador de todo lo que passa a un nivel logico en el juego
//Ejemplos -> control de generacion de bombas y coordenadas

#ifndef TABLEROLOGICO_H
#define TABLEROLOGICO_H

#include <vector>
#include "Celda.h"
using namespace std;


class tableroLogico{
private:
    int numFilas;
    int numColumnas;
    int numMinas;
    vector<vector<Celda>> tablero;

public:
    tableroLogico(int numFilas, int numColumnas, int numMinas);
    int getFilas();
    int getColumnas();
    Celda &obtenerCelda(int fila, int columna);
    void colocarMinas(vector<vector<Celda>> &tablero);
    void revelarCelda(int f, int c);
    vector<vector<Celda>> &getTablero(){
        return tablero;
    }
};

#endif // TABLEROLOGICO_H

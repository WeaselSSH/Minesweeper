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
    vector<vector<Celda>> tablero;

public:
    tableroLogico(int numFilas, int numColumnas);
    void getFilas();
    void getColumnas();
    Celda obtenerCelda(int fila, int columna);
    void colocarMinas();
};

#endif // TABLEROLOGICO_H

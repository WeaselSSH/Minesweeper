//Esta clase de tableroLogico servira como controlador de todo lo que passa a un nivel logico en el juego
//Ejemplos -> control de generacion de bombas y coordenadas

#ifndef TABLEROLOGICO_H
#define TABLEROLOGICO_H

#include <vector>
#include "celda.h"

class tableroLogico{
private:
    int numFilas;
    int numColumnas;
    vector<vector<celda>> tablero;

public:
    tableroLogico(int numFilas, int numColumnas);
    void getFilas();
    void getColumnas();
    celda obtenerCelda(int fila, int columna);

};

#endif // TABLEROLOGICO_H

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
    vector<vector<Celda>> &getTablero(){
        return tablero;
    }

    void colocarMinas();
    void calcularMinasAdyacentes();
    void revelarCelda(int f, int c);
    bool verificarVictoria();
    bool verificarDerrota(int f, int c);
};

#endif // TABLEROLOGICO_H

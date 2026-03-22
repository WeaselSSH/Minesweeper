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
    int numBanderasPuestas; //nueva variable agregada para llevar control de cuantas banderas se han puesto
    char gameMode;
    vector<vector<Celda>> tablero; //esto es basicamente un array bidimensional pero dinamico

public:
    tableroLogico(int numFilas, int numColumnas, int numMinas);

    int getFilas() const;
    int getColumnas() const;

    Celda &obtenerCelda(int fila, int columna);
    void colocarMinas();
    void calcularMinasAdyacentes();
    void revelarCelda(int fila, int columna);
    bool verificarVictoria();
    bool verificarDerrota(int fila, int columna);

    //metodo que simplemente simplifica la accion de incrementar el counter de banderas
    void alterarConteoBanderas(Celda &mcelda);
    int getNumBanderasPuestas() const;

    void setBanderas(int num);

    void setgameMode(char gameMode);
    char getgameMode();
    int getNumMinas();


};

#endif // TABLEROLOGICO_H

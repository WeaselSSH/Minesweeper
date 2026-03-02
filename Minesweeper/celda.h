#ifndef CELDA_H
#define CELDA_H
using namespace std;


class Celda{

private:
    int fila;
    int columna;
    bool tieneMina;
    char MINA;

public:
    Celda(int f, int c);
    void asignarMina(char MINA);
    int getF();
    int getC();
    bool checkStatus();

};


#endif // CELDA_H

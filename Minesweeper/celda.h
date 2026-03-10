#ifndef CELDA_H
#define CELDA_H
using namespace std;

class Celda{

private:
    int fila;
    int columna;
    bool tieneMina;
    char MINA;

    bool revelada;
    bool conBandera;
    int minasAdyacentes;

public:
    Celda(int fila, int columna);
    void asignarMina(char MINA);
    int getF();
    int getC();
    bool checkStatus();

    void revelar();
    bool estaRevelada();
    void alternarBandera();
    bool tieneBandera();
    void setMinasAdyacentes(int cant);
    int getMinasAdyacentes();
};


#endif // CELDA_H

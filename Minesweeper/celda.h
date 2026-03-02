#ifndef CELDA_H
#define CELDA_H

class celda{

private:
    int x;
    int y;
    bool tieneMina;
    char MINA;

public:
    celda(int x, int y);
    void asignarMina(char MINA);
    int getX();
    int getY();

};


#endif // CELDA_H

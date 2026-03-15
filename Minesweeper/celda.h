#ifndef CELDA_H
#define CELDA_H

class Celda{

private:
    int fila;
    int columna;
    bool tieneMina;

    bool revelada;
    bool conBandera;
    int minasAdyacentes;

public:
    Celda(int fila, int columna);

    void asignarMina();
    int getFila() const;
    int getColumna() const;
    bool getTieneMina() const;

    void revelar();
    bool estaRevelada() const;
    bool tieneBandera() const;
    void alternarBandera();
    void setMinasAdyacentes(int cantidad);
    int getMinasAdyacentes() const;
};


#endif // CELDA_H

#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario {
public:
    //CONSTRUCTORES
    Usuario(const string& username, const string& contrasena);
    Usuario(const string& username, const string& contrasena, int mejorFacil, int mejorMedio, int mejorDificil);

    //GETTERS
    const string& getNombreUsuario() const;
    const string& getContrasena() const;
    int getMejorFacil() const;
    int getMejorMedio() const;
    int getMejorDificil() const;

    //SETTERS
    void setNombreUsuario(const string& username);
    void setContrasena(const string& pin);
    void setMejorFacil(int puntaje);
    void setMejorMedio(int puntaje);
    void setMejorDificil(int puntaje);

private:
    string mNombreUsuario;
    string mContrasena;
    int mMejorFacil;
    int mMejorMedio;
    int mMejorDificil;
};

#endif // USUARIO_H

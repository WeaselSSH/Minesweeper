#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario {
public:
    //CONSTRUCTORES
    Usuario(int id, const string& username, const string& contrasena);
    Usuario(int id, const string& username, const string& contrasena, int mejorFacil, int mejorMedio, int mejorDificil);

    //GETTERS
    int getId() const;
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
    int mId;
    string mNombreUsuario;
    string mContrasena;
    int mMejorFacil;
    int mMejorMedio;
    int mMejorDificil;
};

#endif // USUARIO_H

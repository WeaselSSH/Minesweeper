#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    //CONSTRUCTORES
    Usuario(int id, const std::string& username, const std::string& contrasena);
    Usuario(int id, const std::string& username, const std::string& contrasena, int nivelMaximo, int mejorFacil, int mejorMedio, int mejorDificil);

    //GETTERS
    int getId() const;
    const std::string& getNombreUsuario() const;
    const std::string& getContrasena() const;
    int getNivelMaximo() const;
    int getMejorFacil() const;
    int getMejorMedio() const;
    int getMejorDificil() const;

    //SETTERS
    void setNombreUsuario(const std::string& username);
    void setContrasena(const std::string& pin);
    void setNivelMaximo(int nivelMaximo);
    void setMejorFacil(int puntaje);
    void setMejorMedio(int puntaje);
    void setMejorDificil(int puntaje);

private:
    int mId;
    std::string mNombreUsuario;
    std::string mContrasena;
    int mNivelMaximo;
    int mMejorFacil;
    int mMejorMedio;
    int mMejorDificil;
};

#endif // USUARIO_H

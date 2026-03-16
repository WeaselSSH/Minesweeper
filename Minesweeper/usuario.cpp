#include "Usuario.h"

//CONSTRUCTORES
Usuario::Usuario(int id, const string& username, const string& contrasena)
    : mId(id), mNombreUsuario(username), mContrasena(contrasena), mNivelMaximo(0), mMejorFacil(0), mMejorMedio(0), mMejorDificil(0)
{}

Usuario::Usuario(int id, const string& username, const string& contrasena, int nivelMaximo, int mejorFacil, int mejorMedio, int mejorDificil)
    : mId(id), mNombreUsuario(username), mContrasena(contrasena), mNivelMaximo(nivelMaximo),
    mMejorFacil(mejorFacil), mMejorMedio(mejorMedio), mMejorDificil(mejorDificil)
{}

//GETTERS
const string& Usuario::getNombreUsuario() const {
    return mNombreUsuario;
}

const string& Usuario::getContrasena() const {
    return mContrasena;
}

int Usuario::getNivelMaximo() const {
    return mNivelMaximo;
}

int Usuario::getMejorFacil() const {
    return mMejorFacil;
}

int Usuario::getMejorMedio() const {
    return mMejorMedio;
}

int Usuario::getMejorDificil() const {
    return mMejorDificil;
}

int Usuario::getId() const {
    return mId;
}

//SETTERS
void Usuario::setNombreUsuario(const string& username) {
    mNombreUsuario = username;
}

void Usuario::setContrasena(const string& pin) {
    mContrasena = pin;
}

void Usuario::setNivelMaximo(int nivelMaximo) {
    mNivelMaximo = nivelMaximo;
}

void Usuario::setMejorFacil(int puntaje) {
    mMejorFacil = puntaje;
}

void Usuario::setMejorMedio(int puntaje) {
    mMejorMedio = puntaje;
}

void Usuario::setMejorDificil(int puntaje) {
    mMejorDificil = puntaje;
}

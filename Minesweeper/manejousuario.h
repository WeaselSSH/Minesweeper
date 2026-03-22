#ifndef MANEJOUSUARIO_H
#define MANEJOUSUARIO_H

#include "usuario.h"
#include <vector>
#include <string>

class ManejoUsuario
{
public:
    void cargarDatos();
    void guardarDatos();
    bool registrarse(const std::string &nombre, const std::string &contrasena);
    bool iniciarSesion(const std::string &nombre, const std::string &contrasena);
    int getIdxUsuarioActual() const;
    const std::vector<Usuario> &getListaUsuarios() const;

    Usuario& getUsuarioActual();


private:
    const std::string NOMBRE_ARCHIVO = "listaUsuarios.txt";
    const char DELIMITER = '|';
    std::vector<Usuario> listaUsuarios;
    int idxUsuarioActual = -1;
    int nextId = 1;

    int generarId();
};

#endif // MANEJOUSUARIO_H

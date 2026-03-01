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
    bool registrarse(const string &nombre, const string &contrasena);
private:
    const std::string NOMBRE_ARCHIVO = "listaUsuarios.txt";
    const char DELIMITER = '|';
    std::vector<Usuario> listaUsuarios;
    int idxUsuarioActual = -1;
};

#endif // MANEJOUSUARIO_H

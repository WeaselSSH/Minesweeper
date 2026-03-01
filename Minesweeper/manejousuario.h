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
private:
    const std::string NOMBRE_ARCHIVO = "listaUsuarios.txt";
    const char DELIMITER = '|';
    std::vector<Usuario> listaUsuarios;
};

#endif // MANEJOUSUARIO_H

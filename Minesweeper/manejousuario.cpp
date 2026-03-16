#include "manejousuario.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void ManejoUsuario::cargarDatos() {
    ifstream archivoEntrada(NOMBRE_ARCHIVO.c_str());
    listaUsuarios.clear();
    idxUsuarioActual = -1;
    nextId = 1;

    if (!archivoEntrada.is_open()) return;

    string linea;

    while (getline(archivoEntrada, linea)) {
        if (linea.empty()) continue;

        size_t p1 = linea.find(DELIMITER);
        size_t p2 = (p1 == string::npos) ? string::npos : linea.find(DELIMITER, p1+1);
        size_t p3 = (p2 == string::npos) ? string::npos : linea.find(DELIMITER, p2+1);
        size_t p4 = (p3 == string::npos) ? string::npos : linea.find(DELIMITER, p3+1);
        size_t p5 = (p4 == string::npos) ? string::npos : linea.find(DELIMITER, p4+1);
        size_t p6 = (p5 == string::npos) ? string::npos : linea.find(DELIMITER, p5+1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos || p5 == string::npos || p6 == string::npos)
            continue;

        string idTexto = linea.substr(0, p1);
        string nombreUsuario = linea.substr(p1 + 1, p2 - (p1 + 1));
        string contrasena = linea.substr(p2 + 1, p3 - (p2 + 1));
        string nivelMaximoTexto = linea.substr(p3 + 1, p4 - (p3 + 1));
        string mejorFacilTexto = linea.substr(p4 + 1, p5 - (p4 + 1));
        string mejorMedioTexto = linea.substr(p5 + 1, p6 - (p5+1));
        string mejorDificilTexto = linea.substr(p6 + 1);

        try{
            int id = stoi(idTexto);
            Usuario usuarioLeido(id, nombreUsuario, contrasena, stoi(nivelMaximoTexto),
                                 stoi(mejorFacilTexto), stoi(mejorMedioTexto), stoi(mejorDificilTexto));

            listaUsuarios.push_back(usuarioLeido);

            if (id >= nextId) nextId = id + 1;
        } catch(...) {
            continue;
        }
    }

    archivoEntrada.close();
}

void ManejoUsuario::guardarDatos() {
    ofstream archivoSalida(NOMBRE_ARCHIVO.c_str(), ios::trunc);
    if (!archivoSalida.is_open()) return;

    for (const Usuario& u : listaUsuarios) {
        archivoSalida << u.getId() << DELIMITER
                      << u.getNombreUsuario() << DELIMITER
                      << u.getContrasena() << DELIMITER
                      << u.getNivelMaximo() << DELIMITER
                      << u.getMejorFacil() << DELIMITER
                      << u.getMejorMedio() << DELIMITER
                      << u.getMejorDificil() << "\n";
    }

    archivoSalida.close();
}

bool ManejoUsuario::registrarse(const string &nombre, const string &contrasena) {
    for (const Usuario &u : listaUsuarios) {
        if (u.getNombreUsuario() == nombre) return false;
    }

    int id = generarId();
    Usuario nuevo(id, nombre, contrasena);
    listaUsuarios.push_back(nuevo);

    idxUsuarioActual = (int)listaUsuarios.size() - 1;
    guardarDatos();
    return true;
}

bool ManejoUsuario::iniciarSesion(const string& nombre, const string& contrasena)
{
    idxUsuarioActual = -1; //por si falla iniciar sesion que no apunte a nadie (no deberia influir pero por cualquier cosa)

    for (int i = 0; i < (int)listaUsuarios.size(); i++) {
        if (listaUsuarios[i].getNombreUsuario() == nombre) {
            if (listaUsuarios[i].getContrasena() == contrasena) {
                idxUsuarioActual = i;
                return true;
            }
            return false;
        }
    }
    return false;
}

int ManejoUsuario::generarId() {
    int id = nextId;
    nextId++;

    return id;
}

int ManejoUsuario::getIdxUsuarioActual() const{
    return idxUsuarioActual;
}

const vector<Usuario>& ManejoUsuario::getListaUsuarios() const {
    return listaUsuarios;
}

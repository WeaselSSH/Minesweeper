#include "manejousuario.h"
#include "fstream"
#include <string>
#include <vector>

using namespace std;

void ManejoUsuario::cargarDatos() {
    ifstream archivoEntrada(NOMBRE_ARCHIVO.c_str());
    listaUsuarios.clear();

    if (!archivoEntrada.is_open())
        return;

    string linea;

    while (getline(archivoEntrada, linea)) {
        if (linea.empty())
            continue;

        size_t p1 = linea.find(DELIMITER);
        size_t p2 = (p1 == string::npos) ? string::npos : linea.find(DELIMITER, p1+1);
        size_t p3 = (p2 == string::npos) ? string::npos : linea.find(DELIMITER, p2+1);
        size_t p4 = (p3 == string::npos) ? string::npos : linea.find(DELIMITER, p3+1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos)
            continue; //linea mal formada, se ignora

        string nombreUsuario = linea.substr(0, p1);
        string contrasena = linea.substr(p1 + 1, p2 - (p1 + 1));
        string mejorFacilTexto = linea.substr(p2 + 1, p3 - (p2 + 1));
        string mejorMedioTexto = linea.substr(p3 + 1, p4 - (p3 + 1));
        string mejorDificilTexto = linea.substr(p4 + 1);

        try{
            Usuario usuarioLeido(nombreUsuario, contrasena, stoi(mejorFacilTexto), stoi(mejorMedioTexto), stoi(mejorDificilTexto));
            listaUsuarios.push_back(usuarioLeido);
        } catch(...) {
            continue;
        }
    }

    archivoEntrada.close();
}

void ManejoUsuario::guardarDatos() {
    ofstream archivoSalida(NOMBRE_ARCHIVO.c_str(), ios::trunc);

    for (const Usuario& u : listaUsuarios) {
        archivoSalida << u.getNombreUsuario() << DELIMITER
                      << u.getContrasena() << DELIMITER
                      << u.getMejorFacil() << DELIMITER
                      << u.getMejorMedio() << DELIMITER
                      << u.getMejorDificil() << DELIMITER << "\n";
    }

    archivoSalida.close();
}

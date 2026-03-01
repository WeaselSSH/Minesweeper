#include "menuprincipal.h"
#include "manejousuario.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    ManejoUsuario manejo;
    manejo.cargarDatos();

    MenuPrincipal w(&manejo);
    w.show();
    return a.exec();
}

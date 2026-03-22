#include "menuprincipal.h"
#include "manejousuario.h"
#include <QApplication>

int main(int argc, char *argv[]){
    //eto va aqui el srand ekisde
    srand(time(0));
    QApplication a(argc, argv);

    ManejoUsuario manejo;
    manejo.cargarDatos();

    MenuPrincipal w(&manejo);
    w.show();
    return a.exec();
}

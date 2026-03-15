#include "menuprincipal.h"
#include "manejousuario.h"
#include <QApplication>

int main(int argc, char *argv[]){
    //acceso de ayuda y gestor de documentos que ofrece el juego
    //eto va aqui el srand ekisde
    srand(time(0));
    QApplication a(argc, argv);

    ManejoUsuario manejo;
    manejo.cargarDatos();

    MenuPrincipal w(&manejo);

    //que es manual tecnico y de usuario? xd

    //--------
    // QApplication vent(argc, argv);
    // QWidget ventana;

    // ventana.setWindowTitle("Testeando graficos");
    // ventana.resize(500,600);

    // //organizando widget
    // QVBoxLayout *layout = new QVBoxLayout(&ventana);
    // tableroVisual *miWidget= new tableroVisual ();

    // layout->addWidget(miWidget);
    // ventana.show();

    w.show();
    return a.exec();
    // return vent.exec();
}

#include "Ventana.h"

#include <QApplication>

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

int main(int argc, char *argv[]){// Metodo principal manejador del programa
    QApplication a(argc, argv);
    TWindow w; // Creamos un objeto de tipo TWindow
    w.show();// Mostramos la ventana
    return a.exec();
}

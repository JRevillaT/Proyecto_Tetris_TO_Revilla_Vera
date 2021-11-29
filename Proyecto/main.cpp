#include "TetrixWindow.h"

#include <QApplication>

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrixWindow w;
    w.show();
    return a.exec();
}

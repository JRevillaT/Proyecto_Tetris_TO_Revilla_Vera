#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TTablero;

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

/*
 * Esta clase se utiliza para mostrar la informaciÃ³n del juego y contiene el Ã¡rea de juego
 * en la cual vamos a trabajar.
 */

class TWindow : public QWidget{
    Q_OBJECT

public:
    TWindow(QWidget *parent = nullptr);

/*
 * Usaremos variables miembro privadas para el tablero, algunos widgets de visualizaciÃ³n y
 * botones para permitir al usuario iniciar un nuevo juego, pausar el juego actual o salir.
 */
private:
    QLabel *crearLabel(const QString &text);

    TTablero*tablero;     // Tablero
    QLabel *siguientePieza; // Siguiente pieza
    QLCDNumber *puntuacion;   // Puntaje de juego
    QLCDNumber *nivel;   // Puntaje en nivel
    QLCDNumber *linesLcd;   // lineas en tablero
    QPushButton *botonIniciar;  // Boton de iniciar juego
    QPushButton *botonSalir;   // Boton de cerrar juego
    QPushButton *botonPausar;  // Boton de pausar juego

    QPushButton *botonBastard; // Boton de activar modo Bastard
    QPushButton *botonEasy; // Boton activar modo Easy
    QPushButton *botonAyuda; // Boton ver ayuda
};


#endif

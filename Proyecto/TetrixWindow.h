#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TetrixBoard;

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

/*
 * Esta clase se utiliza para mostrar la información del juego y contiene el área de juego
 * en la cual vamos a trabajar.
 */

class TetrixWindow : public QWidget{
    Q_OBJECT

public:
    TetrixWindow(QWidget *parent = nullptr);

/*
 * Usaremos variables miembro privadas para el tablero, algunos widgets de visualización y
 * botones para permitir al usuario iniciar un nuevo juego, pausar el juego actual o salir.
 */
private:
    QLabel *createLabel(const QString &text);

    TetrixBoard *board;     // Tablero
    QLabel *nextPieceLabel;
    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
};


#endif

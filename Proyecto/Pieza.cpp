#include "Pieza.h"

#include <QtCore>
#include <QDebug>

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

void TPieza::setFormaAleatoria()//7
{
    setForma(formaDeMatriz(QRandomGenerator::global()->bounded(7) + 1));
}

void TPieza::setFormaAleatoriaBastard()//7
{
    setFormaBastard(formaDeMatriz(QRandomGenerator::global()->bounded(7) + 1));
    qDebug() << "Metodo para matriz Bastard ...";
}

void TPieza::setForma(formaDeMatriz shape){
    // Crearemos los valores de las coordenadas del tablero de forma estatica
    /*static constexpr int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
    };*/
    static constexpr int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
    };
    // Corremos en todas las posiciones de las coordenadas de nuestro tablero
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            coordenadas[i][j] = coordsTable[shape][i][j];
    }
    pieza = shape; // Asignamos el nuevo valor

}

void TPieza::setFormaBastard(formaDeMatriz shape){
    // Crearemos los valores de las coordenadas del tablero de forma estatica
    /*static constexpr int coordsTable[8][4][2] = {
        { { 0, 0 },   { 1, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 1, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 1, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 1, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 1, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
    };*/

    static constexpr int coordsTable[8][4][2] = {
        { { 0, 0 },   { 1, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 1, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 1, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 1, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 1, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 1, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 1, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 1, 0 },   { 0, 1 } }
    };

    // Corremos en todas las posiciones de las coordenadas de nuestro tablero
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            coordenadas[i][j] = coordsTable[shape][i][j];
    }
    pieza = shape; // Asignamos el nuevo valor

}

// Valor minimo en cuanto a X en el tablero
int TPieza::minX() const{
    int min = coordenadas[0][0]; // Guardamos el valor minimo de la primera coordenada [0][0]
    for (int i = 1; i < 4; ++i) // Recorremos los tres valores posibles
        min = qMin(min, coordenadas[i][0]); // Asignamos el valor en cuanto al minimo obtenido
    return min; // Retornamos el valor minimo
}

// Valor maximo en cuanto a X en el tablero
int TPieza::maxX() const{
    int max = coordenadas[0][0]; // Guardamos el valor maximo de la primera coordenada [0][0]
    for (int i = 1; i < 4; ++i) // Recorremos los tres valores posibles
        max = qMax(max, coordenadas[i][0]); // Asignamos el valor en cuanto al maximo obtenido
    return max; // Retornamos el valor maximo
}

// Valor minimo en cuanto a Y en el tablero
int TPieza::minY() const{
    int min = coordenadas[0][1]; // Guardamos el valor minimo de la primera coordenada [0][1]
    for (int i = 1; i < 4; ++i) // Recorremos los tres valores posibles
        min = qMin(min, coordenadas[i][1]); // Asignamos el valor en cuanto al minimo obtenido
    return min; // Retornamos el valor minimo
}

// Valor maximo en cuanto a Y en el tablero
int TPieza::maxY() const{
    int max = coordenadas[0][1]; // Guardamos el valor maximo de la primera coordenada [0][1]
    for (int i = 1; i < 4; ++i) // Recorremos los tres valores posibles
        max = qMax(max, coordenadas[i][1]); // Asignamos el valor en cuanto al maximo obtenido
    return max; // Retornamos el valor maximo
}

// Metodo para rotar a la izquierda la pieza
TPieza TPieza::rotarIzquierda() const{
    // Si la pieza a evaluar es igual a "squareShape", retornara el valor de la direccion del puntero
    if (pieza == SquareShape)
        return *this;

    TPieza result;
    result.pieza = pieza; // Asignamos el valor en pieza
    for (int i = 0; i < 4; ++i) { // Recorremos maximo 3 iteraciones para la rotacion
        result.setX(i, y(i)); // Asignamos los valores actuales de la coordenada en la posicion X del tablero
        result.setY(i, -x(i)); // Asignamos los valores actuales de la coordenada en la posicion Y del tablero
    }
    return result; //Retornamos los valores de las coordenadas
}

// Metodo para rotar a la derecha la pieza
TPieza TPieza::rotarDerecha() const{
    // Si la pieza a evaluar es igual a "squareShape", retornara el valor de la direccion del puntero
    if (pieza == SquareShape)
        return *this;

    TPieza result;
    result.pieza = pieza; // Asignamos el valor en pieza
    for (int i = 0; i < 4; ++i) { // Recorremos maximo 3 iteraciones para la rotacion
        result.setX(i, -y(i)); // Asignamos los valores actuales de la coordenada en la posicion X del tablero
        result.setY(i, x(i)); // Asignamos los valores actuales de la coordenada en la posicion Y del tablero
    }
    return result; //Retornamos los valores de las coordenadas
}

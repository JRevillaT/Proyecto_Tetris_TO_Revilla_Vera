#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>

enum formaDeMatriz { NoShape, ZShape, SShape, LineShape, TShape, SquareShape,
                   LShape, MirroredLShape };

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

/*
 * La clase Pieza contiene informacion sobre una pieza en el area de juego,
 * incluyendo su forma, posicion y el rango de posiciones que puede ocupar en el tablero
 * para asi no poder complicarse al momento de que la pieza colisione.
*/
//template <class T> //identificador de tipo: T
class TPieza // Creando clase TPieza
{
public:
    TPieza() { setForma(NoShape); } //Inicializacion

    void setFormaAleatoria();
    void setFormaAleatoriaBastard();
    void setForma(formaDeMatriz shape);
    void setFormaBastard(formaDeMatriz shape);

    formaDeMatriz shape() const { return pieza; }
    // Retorno de Coordenadas de las piezas actuales
    int x(int indice) const { return coordenadas[indice][0]; }
    int y(int indice) const { return coordenadas[indice][1]; }
    // Creacion de metodos constantes de valores minimos y maximos tomando los ejes
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;
    TPieza rotarIzquierda() const; // Metodo que rota la pieza a la izquierda
    TPieza rotarDerecha() const; // Metodo que rota la pieza a la derecha

    //Sobrecarga de Operadores

    friend bool operator==(const TPieza& s, const TPieza& a){
        return s.shape() == a.shape();
    }

    friend bool operator!=(const TPieza& s, const TPieza& a){
        return !(s.shape() == a.shape());
    }

    friend std::ostream& operator<<(std::ostream& output, const TPieza& v){
        output <<""<<v.shape()<<", ";
        return output;
    }

private:
    // Metodo set para edicion de las coordenadas en X
    void setX(int indice, int x) { coordenadas[indice][0] = x; }
    // Metodo set para edicion de las coordenadas en Y
    void setY(int indice, int y) { coordenadas[indice][1] = y; }

    formaDeMatriz pieza;
    int coordenadas[4][2];
};


#endif

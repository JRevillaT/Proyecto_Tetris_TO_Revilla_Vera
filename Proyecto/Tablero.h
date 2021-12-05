#ifndef TABLERO_H
#define TABLERO_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>

//Incluimos nuestro archivo cabecera
#include "Pieza.h"

QT_BEGIN_NAMESPACE

//Usaremos la clase QLabel de QT que nos proporciona una visualizacion tanto de inagen como texto
class QLabel;
QT_END_NAMESPACE

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

class TTablero : public QFrame // Creacion de la clase TTablero
{
    Q_OBJECT

public:
    TTablero(QWidget *parent = nullptr);

    void setPiezaSiguiente(QLabel *label); // Para la pieza que se creara despues del actual
    QSize sizeHint() const override; // Aspecto Virtual de QSize
    // Devuelve un tamaño no válido si no hay diseño para este widget y, de lo contrario, devuelve el
    // tamaño mínimo del diseño.
    QSize minimumSizeHint() const override;

public slots: // Se utiliozara slots para una mejor comunicacion entre objetos.
    void iniciar(); // Funcion de iniciar el juego
    void pausar(); // Funcion de pausar el juego
    void bastard(); // modo bastard
    void easy(); // modo facil
    void ayuda(); // ayuda descripcion

signals: // Se utilizaran signals para una mejor comunicacion entre objetos.
    void puntuacionCambiada(int score);
    void nivelCambiado(int level);
    void lineasEliminadas(int numLines);

protected:
    void paintEvent(QPaintEvent *event) override; // Los eventos de pintura se envían a los widgets que necesitan actualizarse
    void keyPressEvent(QKeyEvent *event) override; // Los eventos clave se envían al widget con el foco de entrada del teclado cuando se presionan o sueltan las teclas.
    void timerEvent(QTimerEvent *event) override; // Los eventos del temporizador se envían a intervalos regulares a los objetos que han iniciado uno o más temporizadores.
private:
    enum { ancho = 13, altura = 25 }; // Atributos de Ancho y Alto de nuestro tablero

    formaDeMatriz &shapeAt(int x, int y) {
        return campoTablero[(y * ancho) + x]; // Redimensionamiento
    }
    int tiempoDeEspera() { // Retorna el tiempo de espera de salida de cada ficha
        return 1000 / (1 + nivel);
    }
    int anchoCuadrado() { // Retorna el valor del ancho del cuadrado
        return contentsRect().width() / ancho;
    }
    int alturaCuadrado() { // Retorna el valor de la altura del cuadrado
        return contentsRect().height() / altura;
    }
    // Nuevos metodos de la clase
    void limpiarTablero();// Limpia los datos de nuestro board
    void despligue(); // Desplegamos toda la interfaz
    void oneLineDown();
    void piezaCaida(int dropHeight); // Pieza en caida
    void removeFullLines();
    void nuevaPieza(); // Generando la nueva pieza
    void mostrarPiezaSiguiente();// Mostrando pieza aleatoria siguiente
    bool movimiento(const TPieza &newPiece, int newX, int newY);
    void dibujar(QPainter &painter, int x, int y, formaDeMatriz shape);

    // Variables de entorno
    QBasicTimer temporizador;
    QPointer<QLabel> siguientePieza;
    bool empezar;
    bool enPausa;
    bool isWaitingAfterLine;
    TPieza curPiece;
    TPieza nextPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int nivel;
    formaDeMatriz campoTablero[ancho * altura];
};

#endif

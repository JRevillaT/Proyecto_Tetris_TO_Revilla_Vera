#include "Tablero.h"

#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

//al reiniciar el juego, el tablero debe estar limpio para la proxima partida, ademas de generar las piezas
TTablero::TTablero(QWidget *parent)
    : QFrame(parent), empezar(false), enPausa(false)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    limpiarTablero();
    //elegimos modo

    if(bastardMode == true)
        nextPiece.setFormaAleatoriaBastard();
    else if(bastardMode == false)
        nextPiece.setFormaAleatoria();
}


//Aqui pasaremos la sgte pieza(del frame de sgte a pieza al tablero de juego)
void TTablero::setPiezaSiguiente(QLabel *label)
{
    siguientePieza = label;
}

//Aqui definimos tanto el largo como el acho del cubito que forma la figura
QSize TTablero::sizeHint() const
{
    return QSize(ancho * 15 + frameWidth() * 2,
                 altura * 15 + frameWidth() * 2);
}

QSize TTablero::minimumSizeHint() const

{
    return QSize(ancho * 5 + frameWidth() * 2,
                 altura * 5 + frameWidth() * 2);
}


//Al iniciar el juego todos los valores se deben iniciar en 0, asi como definir las cantidades como la puntuacion o lineas eliminadas iniciales en 0
void TTablero::iniciar()
{
    if (enPausa)
        return;

    empezar = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    nivel = 1;
    limpiarTablero();

    emit lineasEliminadas(numLinesRemoved);
    emit puntuacionCambiada(score);
    emit nivelCambiado(nivel);

    nuevaPieza();
    temporizador.start(tiempoDeEspera(), this);
}


//Matodo para pausar el tablero
void TTablero::pausar()
{
    if (!empezar)
        return;

    enPausa= !enPausa;
    if (enPausa) {
        temporizador.stop();
    } else {
        temporizador.start(tiempoDeEspera(), this);
    }
    update();

}

void TTablero::bastard(){
    if (enPausa)
        return;

    empezar = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    nivel = 1;
    limpiarTablero();
    bastardMode=true;

    emit lineasEliminadas(numLinesRemoved);
    emit puntuacionCambiada(score);
    emit nivelCambiado(nivel);

    nuevaPiezaBastard();
    temporizador.start(tiempoDeEspera(), this);
}

// Modo easy para cambiar la ficha a conveniencia del usuario
void TTablero::easy(){
    bastardMode=false;
    if (enPausa)
        return;

    empezar = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    nivel = 1;
    limpiarTablero();

    emit lineasEliminadas(numLinesRemoved);
    emit puntuacionCambiada(score);
    emit nivelCambiado(nivel);

    nuevaPieza();
    temporizador.start(tiempoDeEspera(), this);
}


// Funcion para mostrar el mensaje de ayuda al hacer click
void TTablero::ayuda(){
    QString text = "Ventana de Ayuda\nPara saber mas acerca de como usar este juego y su implementacion vaya al siguiente enlace:\nhttps://acortar.link/3dfsZb";
    QMessageBox::information(this, "Ayuda de Tetris", text, QMessageBox::Ok);
}

void TTablero::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();

    if (enPausa) {
        painter.drawText(rect, Qt::AlignCenter, tr("Juego Pausado"));
        return;
    }


    int boardTop = rect.bottom() - altura*alturaCuadrado();

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < ancho; ++j) {
            formaDeMatriz shape = shapeAt(j, altura - i - 1);
            if (shape != NoShape)
                dibujar(painter, rect.left() + j * anchoCuadrado(),
                           boardTop + i * alturaCuadrado(), shape);
        }
    }

    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            dibujar(painter, rect.left() + x * anchoCuadrado(),
                       boardTop + (altura - y - 1) * alturaCuadrado(),
                       curPiece.shape());
        }

    }

}


//Con este metodo controlamos los eventos que suceden cuando presionamos las teclas de juego
void TTablero::keyPressEvent(QKeyEvent *event)
{
    if (!empezar || enPausa || curPiece.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        movimiento(curPiece, curX - 1, curY);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        movimiento(curPiece, curX + 1, curY);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        movimiento(curPiece.rotarDerecha(), curX, curY);
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        movimiento(curPiece.rotarIzquierda(), curX, curY);
        break;
    case Qt::Key_Space:
        despligue();
        break;
    case Qt::Key_X:
        oneLineDown();
        break;

    //Teclas para modos especiales especiales
    case Qt::Key_Z:
        nuevaPieza();
        break;
    default:
        QFrame::keyPressEvent(event);
    }

}


void TTablero::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == temporizador.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            nuevaPieza();
            temporizador.start(tiempoDeEspera(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);

    }

}


//Con este metodo limpiamos el tablero(frames)
void TTablero::limpiarTablero()
{
    for (int i = 0; i < altura * ancho; ++i)
        campoTablero[i] = NoShape;
}

void TTablero::despligue()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!movimiento(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    piezaCaida(dropHeight);

}


void TTablero::oneLineDown()
{
    if (!movimiento(curPiece, curX, curY - 1))
        piezaCaida(0);
}



void TTablero::piezaCaida(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        shapeAt(x, y) = curPiece.shape();
    }

    ++numPiecesDropped;
    if (numPiecesDropped == 25) {
        ++nivel;
        temporizador.start(tiempoDeEspera(), this);
        emit nivelCambiado(nivel);
    }

    score += dropHeight + 7;
    emit puntuacionCambiada(score);
    removeFullLines();

    if (!isWaitingAfterLine)
        nuevaPieza();

}


//Con este metodo removemos una linea que este llena, osea que el jugar logro conseguir completarla
void TTablero::removeFullLines()
{
    int numFullLines = 0;

    //Recorremos el board como una matriz, fila por fila
    for (int i = altura - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < ancho; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }
        //Si encuentra una fila llena, entonces
        if (lineIsFull) {

            ++numFullLines;
            for (int k = i; k < altura - 1; ++k) {
                for (int j = 0; j < ancho; ++j)
                    //Entonces reemplazamos en la sgte fila
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }

            for (int j = 0; j < ancho; ++j)
                shapeAt(j, altura - 1) = NoShape;
        }

    }



    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit lineasEliminadas(numLinesRemoved);
        emit puntuacionCambiada(score);

        temporizador.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setForma(NoShape);
        update();
    }

}


//Con este metodo generamos la nueva pieza que para al frame de sgte pieza
void TTablero::nuevaPieza()
{
    curPiece = nextPiece;

    if(bastardMode == true)
        nextPiece.setFormaAleatoriaBastard();
    else if(bastardMode == false)
        nextPiece.setFormaAleatoria();

    //nextPiece.setFormaAleatoria();
    mostrarPiezaSiguiente();
    curX = ancho / 2 + 1;
    curY = altura - 1 + curPiece.minY();

    if (!movimiento(curPiece, curX, curY)) {
        curPiece.setForma(NoShape);
        temporizador.stop();
        empezar = false;
    }

}

void TTablero::nuevaPiezaBastard()
{
    curPiece = nextPiece;
    nextPiece.setFormaAleatoriaBastard();
    mostrarPiezaSiguiente();
    curX = ancho / 2 + 1;
    curY = altura - 1 + curPiece.minY();

    if (!movimiento(curPiece, curX, curY)) {
        curPiece.setFormaBastard(NoShape);
        temporizador.stop();
        empezar = false;
    }
//! [30] //! [31]
}
//! [31]


void TTablero::mostrarPiezaSiguiente()
{
    //En caso que la ventana de sgte pieza este vacia, generaremos una
    /*if (!siguientePieza)
        return;*/

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * anchoCuadrado(), dy * alturaCuadrado());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), siguientePieza->palette().window());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        dibujar(painter, x * anchoCuadrado(), y * alturaCuadrado(),
                   nextPiece.shape());
    }
    siguientePieza->setPixmap(pixmap);
}



bool TTablero::movimiento(const TPieza &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= ancho || y < 0 || y >= altura)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}


void TTablero::dibujar(QPainter &painter, int x, int y, formaDeMatriz shape)
{
    //Matriz de colores hexadecimales
    static constexpr QRgb colorTable[8] = {
        0x000000, 0xbd1111, 0x24d424, 0x1c1cd9,
        0xa8a832, 0xbd17bd, 0x24d6d6, 0x5C5353
    };

    //Una vez se haya seleccionado el color, procederemos a crear el rectangulo para los colores
    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, anchoCuadrado() - 2, alturaCuadrado() - 2,
                     color);

    painter.setPen(color.lighter());
    painter.drawLine(x, y + alturaCuadrado() - 1, x, y);
    painter.drawLine(x, y, x + anchoCuadrado() - 1, y);

    painter.setPen(color.darker());
    painter.drawLine(x + 1, y + alturaCuadrado() - 1,
                     x + anchoCuadrado() - 10, y + alturaCuadrado() - 1);
    painter.drawLine(x + anchoCuadrado() - 1, y + alturaCuadrado() - 1,
                     x + anchoCuadrado() - 1, y + 1);
}

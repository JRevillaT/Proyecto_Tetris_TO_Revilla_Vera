#include "Tablero.h"

#include <QKeyEvent>
#include <QLabel>
#include <QPainter>

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

    nextPiece.setFormaAleatoria();
}
//! [0]

//Aqui pasaremos la sgte pieza(del frame de sgte a pieza al tablero de juego)
void TTablero::setPiezaSiguiente(QLabel *label)
{
    siguientePieza = label;
}
//! [1]

//Aqui definimos tanto el largo como el acho del cubito que forma la figura
QSize TTablero::sizeHint() const
{
    return QSize(ancho * 15 + frameWidth() * 2,
                 altura * 15 + frameWidth() * 2);
}

QSize TTablero::minimumSizeHint() const
//! [2] //! [3]
{
    return QSize(ancho * 5 + frameWidth() * 2,
                 altura * 5 + frameWidth() * 2);
}
//! [3]

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
//! [4]

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
//! [5]
}

void TTablero::bastard(){

}

// Modo easy para cambiar la ficha a conveniencia del usuario
void TTablero::easy(){
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
//! [6]

//! [7]
void TTablero::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();
//! [7]

    if (enPausa) {
        painter.drawText(rect, Qt::AlignCenter, tr("Juego Pausado"));
        return;
    }

//! [8]
    int boardTop = rect.bottom() - altura*alturaCuadrado();

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < ancho; ++j) {
            formaDeMatriz shape = shapeAt(j, altura - i - 1);
            if (shape != NoShape)
                dibujar(painter, rect.left() + j * anchoCuadrado(),
                           boardTop + i * alturaCuadrado(), shape);
        }
//! [8] //! [9]
    }
//! [9]

//! [10]
    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            dibujar(painter, rect.left() + x * anchoCuadrado(),
                       boardTop + (altura - y - 1) * alturaCuadrado(),
                       curPiece.shape());
        }
//! [10] //! [11]
    }
//! [11] //! [12]
}
//! [12]

//Con este metodo controlamos los eventos que suceden cuando presionamos las teclas de juego
void TTablero::keyPressEvent(QKeyEvent *event)
{
    if (!empezar || enPausa || curPiece.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }
//! [13]

//! [14]
    switch (event->key()) {
    case Qt::Key_Left:
        movimiento(curPiece, curX - 1, curY);
        break;
    case Qt::Key_Right:
        movimiento(curPiece, curX + 1, curY);
        break;
    case Qt::Key_Down:
        movimiento(curPiece.rotarDerecha(), curX, curY);
        break;
    case Qt::Key_Up:
        movimiento(curPiece.rotarIzquierda(), curX, curY);
        break;
    case Qt::Key_Space:
        despligue();
        break;
    case Qt::Key_D: // Para cambiar aleatoriamente la pieza en modo easy
        oneLineDown();
        break;

    // POR APROBARSE-----------------------------------------------------
    case Qt::Key_A:
        nuevaPieza();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
//! [14]
}

//! [15]
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
//! [15] //! [16]
    }
//! [16] //! [17]
}
//! [17]

//Con este metodo limpiamos el tablero(frames)
void TTablero::limpiarTablero()
{
    for (int i = 0; i < altura * ancho; ++i)
        campoTablero[i] = NoShape;
}
//! [18]

//! [19]
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
//! [19] //! [20]
}
//! [20]

//! [21]
void TTablero::oneLineDown()
{
    if (!movimiento(curPiece, curX, curY - 1))
        piezaCaida(0);
}
//! [21]

//! [22]
void TTablero::piezaCaida(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        shapeAt(x, y) = curPiece.shape();
    }

    ++numPiecesDropped;
    if (numPiecesDropped % 25 == 0) {
        ++nivel;
        temporizador.start(tiempoDeEspera(), this);
        emit nivelCambiado(nivel);
    }

    score += dropHeight + 7;
    emit puntuacionCambiada(score);
    removeFullLines();

    if (!isWaitingAfterLine)
        nuevaPieza();
//! [22] //! [23]
}
//! [23]

//Con este metodo removemos una linea que este llena, osea que el jugar logro conseguir completarla
void TTablero::removeFullLines()
{
    int numFullLines = 0;

    for (int i = altura - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < ancho; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
//! [24] //! [25]
            ++numFullLines;
            for (int k = i; k < altura - 1; ++k) {
                for (int j = 0; j < ancho; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }
//! [25] //! [26]
            for (int j = 0; j < ancho; ++j)
                shapeAt(j, altura - 1) = NoShape;
        }
//! [26] //! [27]
    }
//! [27]

//! [28]
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
//! [28] //! [29]
}
//! [29]

//Con este metodo generamos la nueva pieza que para al frame de sgte pieza
void TTablero::nuevaPieza()
{
    curPiece = nextPiece;
    nextPiece.setFormaAleatoria();
    mostrarPiezaSiguiente();
    curX = ancho / 2 + 1;
    curY = altura - 1 + curPiece.minY();

    if (!movimiento(curPiece, curX, curY)) {
        curPiece.setForma(NoShape);
        temporizador.stop();
        empezar = false;
    }
//! [30] //! [31]
}
//! [31]

//! [32]
void TTablero::mostrarPiezaSiguiente()
{
    //En caso que la ventana de sgte pieza este vacia, generaremos una
    if (!siguientePieza)
        return;

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
//! [32] //! [33]
}
//! [33]

//! [34]
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
//! [34]

//! [35]
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}
//! [35]

//! [36]
void TTablero::dibujar(QPainter &painter, int x, int y, formaDeMatriz shape)
{
    //Matriz de colores hexadecimales
    static constexpr QRgb colorTable[8] = {
        //0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        //0xCCCC66, 0xCC66CC, 0x66CCCC, 0x5C5353
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
//! [36]
///////////////////Cambio -10

#include "Tablero.h"
#include "Ventana.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>

/*
 * Nombres:
 *  -Jimy Gabriel Revilla Tellez
 *  -Jose Miguel Vera Mamani
 *
 *  Repositorio: https://github.com/JRevillaT/Proyecto_Tetris_TO_Revilla_Vera
 */

TWindow::TWindow(QWidget *parent)
    :QWidget(parent), tablero(new TTablero){
    // Creando el campo de la siguiente pieza
    siguientePieza = new QLabel;
    siguientePieza->setFrameStyle(QFrame::Box | QFrame::Raised);
    siguientePieza->setAlignment(Qt::AlignCenter);
    // Asignando la siguiente pieza en el rectangulo del tablero
    tablero->setPiezaSiguiente(siguientePieza);

    // Creando el campo de puntuacion
    puntuacion = new QLCDNumber(5);
    puntuacion->setSegmentStyle(QLCDNumber::Filled);

    // Creando el campo de nivel
    nivel = new QLCDNumber(2);
    nivel->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    // Creando el boton de iniciar
    botonIniciar = new QPushButton(tr("&Start"));
    botonIniciar->setFocusPolicy(Qt::NoFocus);

    // Creando el boton de salir
    botonSalir = new QPushButton(tr("&Quit"));
    botonSalir->setFocusPolicy(Qt::NoFocus);

    // Creando el boton de pausar
    botonPausar = new QPushButton(tr("&Pause"));
    botonPausar->setFocusPolicy(Qt::NoFocus);

    // Conexion de click del teclado con el boton de iniciar del tablero
    connect(botonIniciar, &QPushButton::clicked, tablero, &TTablero::iniciar);

    // Conexion de click del teclado con el boton de salir del tablero
    connect(botonSalir , &QPushButton::clicked, qApp, &QCoreApplication::quit);

    // Conexion de click del teclado con el boton de pausar del tablero
    connect(botonPausar, &QPushButton::clicked, tablero, &TTablero::pausar);

#if __cplusplus >= 201402L
    connect(tablero, &TTablero::puntuacionCambiada,
            puntuacion, qOverload<int>(&QLCDNumber::display));
    connect(tablero, &TTablero::nivelCambiado,
            nivel, qOverload<int>(&QLCDNumber::display));
    connect(tablero, &TTablero::lineasEliminadas,
            linesLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, QOverload<int>::of(&QLCDNumber::display));
#endif

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(crearLabel(tr("NEXT")), 0, 0);
    layout->addWidget(siguientePieza, 1, 0);
    layout->addWidget(crearLabel(tr("LEVEL")), 2, 0);
    layout->addWidget(nivel, 3, 0);
    layout->addWidget(botonIniciar, 4, 0);
    layout->addWidget(tablero, 0, 1, 6, 1);
    layout->addWidget(crearLabel(tr("SCORE")), 0, 2);
    layout->addWidget(puntuacion, 1, 2);
    layout->addWidget(crearLabel(tr("LINES REMOVED")), 2, 2);
    layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(botonSalir, 4, 2);
    layout->addWidget(botonPausar, 5, 2);
    setLayout(layout);

    setWindowTitle(tr("Tetrix"));
    resize(550, 370);
}

QLabel *TWindow::crearLabel(const QString &text){
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}


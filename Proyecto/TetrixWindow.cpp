#include "TetrixBoard.h"
#include "tetrixwindow.h"

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

TetrixWindow::TetrixWindow(QWidget *parent)
    :QWidget(parent), tablero(new TetrixBoard){
//! [0]
    siguientePieza = new QLabel;
    siguientePieza->setFrameStyle(QFrame::Box | QFrame::Raised);
    siguientePieza->setAlignment(Qt::AlignCenter);
    tablero->setNextPieceLabel(siguientePieza);
//! [1]
    puntuacion = new QLCDNumber(5);
    puntuacion->setSegmentStyle(QLCDNumber::Filled);
//! [1]
    nivel = new QLCDNumber(2);
    nivel->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

//! [2]
    botonIniciar = new QPushButton(tr("&Start"));
    botonIniciar->setFocusPolicy(Qt::NoFocus);
    botonSalir = new QPushButton(tr("&Quit"));
    botonSalir->setFocusPolicy(Qt::NoFocus);
    botonPausar = new QPushButton(tr("&Pause"));
//! [2] //! [3]
    botonPausar->setFocusPolicy(Qt::NoFocus);
//! [3] //! [4]

    connect(botonIniciar, &QPushButton::clicked, tablero, &TetrixBoard::start);
//! [4] //! [5]
    connect(botonSalir , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(botonPausar, &QPushButton::clicked, tablero, &TetrixBoard::pause);
#if __cplusplus >= 201402L
    connect(tablero, &TetrixBoard::scoreChanged,
            puntuacion, qOverload<int>(&QLCDNumber::display));
    connect(tablero, &TetrixBoard::levelChanged,
            nivel, qOverload<int>(&QLCDNumber::display));
    connect(tablero, &TetrixBoard::linesRemovedChanged,
            linesLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, QOverload<int>::of(&QLCDNumber::display));
#endif
//! [5]

//! [6]
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("NEXT")), 0, 0);
    layout->addWidget(siguientePieza, 1, 0);
    layout->addWidget(createLabel(tr("LEVEL")), 2, 0);
    layout->addWidget(nivel, 3, 0);
    layout->addWidget(botonIniciar, 4, 0);
    layout->addWidget(tablero, 0, 1, 6, 1);
    layout->addWidget(createLabel(tr("SCORE")), 0, 2);
    layout->addWidget(puntuacion, 1, 2);
    layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 2);
    layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(botonSalir, 4, 2);
    layout->addWidget(botonPausar, 5, 2);
    setLayout(layout);

    setWindowTitle(tr("Tetrix"));
    resize(550, 370);
}
//! [6]

//! [7]
QLabel *TetrixWindow::createLabel(const QString &text){
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
//! [7]

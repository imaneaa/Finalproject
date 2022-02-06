#ifndef BOARDGAME_H
#define BOARDGAME_H
#include <QObject>
#include <QLabel>
#include <QSpacerItem>
#include <QTextFormat>
#include <QFont>
#include <QString>
#include <cmath>
#include <QKeyEvent>
#include <QMessageBox>
#include "menubuttons.h"
#include <QGuiApplication>

#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QVector>
#include <QMainWindow>
#include <QWidget>

class boardgame : public QWidget
{
 Q_OBJECT
public:
    boardgame( QWidget* = nullptr);
    ~boardgame();
    void reset();
    void settingBoardgame();
signals:
    void Mergenumbers(int = 0);// fusionner deux valeurs
protected:
    void keyPressEvent(QKeyEvent* );// Pour les bouttons du clavier

private:

    QGridLayout *newgrid;
    QVector<QLabel*> Qlabels;
    QString changerlacouleur(int);// calculer la degradation de la couleur
    void créerboardgame();
    void ajouterNouveauNombre();
    void caseUp();
    void caseDown();
    void caseRight();
    void caseLeft();
    void passerleselementsUp();
    void passerleselementsDown();
    void passerleselementsLeft();
    void passerleselementsRight();
    bool MovetoUp();
    bool MovetoDown();
    bool MovetoLeft();
    bool MovetoRight();
    bool youcanMove();
    bool Novalue();
    bool hasSpace();
    bool youWon();
    const int SCREENHEIGHT = 1000;
     const int SCREENLWIDTH= 800; //hauteur de screen
    const int COLORRGB = 242; // valeur constante pour rgb-conversion
    int table[4][4] = {}; // Board initialiser avec des zéros


};

#endif // BOARDGAME_H

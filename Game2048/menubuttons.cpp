#include "menubuttons.h"
#include <boardgame.h>
#include<mainwindow.h>
MenuButtons::MenuButtons(int num, QWidget* window) : QWidget(window)
{
    this->setFixedSize(600,400);// fixer la taille du layout
    VLayout = new QVBoxLayout(this);// créer un nouveau layout
    QHBoxLayout *touches = new QHBoxLayout(this);// box pour des boutons horizontales
    touches->setSpacing(100);// espace
    QFont font("Arial Black", (20));//font des boutons

    QPushButton *sortir = new QPushButton("Quitter le jeu ", this);// bouton pour quitter le jeu
   sortir->setStyleSheet("background:rgb(242,177,121);");// couleur
   sortir->setFont(font);// ajouter font
   sortir->setFixedSize(200, 60);//taille
    touches->addWidget(sortir, 0, Qt::AlignTop | Qt::AlignTop);// ajouter au box
    connect(sortir,  &QPushButton::clicked, this, &QApplication::quit);// faire la connection

    QPushButton *newGameButton = new QPushButton("New game", this);//bouton du new game
    newGameButton->setStyleSheet("background:rgb(242,177,121);");// couleur du buton
    newGameButton->setFont(font);//ajouter font
    newGameButton->setFixedSize(200, 60);//size
   touches->addWidget(newGameButton, 0, Qt::AlignTop | Qt::AlignTop);//ajouter le bouton au box
    connect(newGameButton, &QPushButton::clicked, this, &MenuButtons::newGame);// faire la connection entre le bouton et la fonction (newgameslot)




    VLayout->addLayout(ajusterlescore(num));//ajouter la fonction du score
    VLayout->addLayout(touches);     // ajouter le box des butons au layout verticale
   VLayout->setSpacing(200);

}

MenuButtons::~MenuButtons() = default;

QHBoxLayout* MenuButtons::ajusterlescore(int scoreValue) {// fonction et  buton du score
    QFont font("Arial Black", (20));// font
    scorebutton = new QLabel;//
    QString scoreString = "Score: " + QString::number(scoreValue);// ajouter la fonction du score
    scorebutton->setText(scoreString);
    scorebutton->setFixedSize(200, 60);// fixer la taille
    scorebutton->setStyleSheet("background:rgb(242,177,121);");// couleur
    scorebutton->setFont(font);//font
    scorebutton->setAlignment(Qt::AlignCenter);//positionnement
    QHBoxLayout *boxForScore = new QHBoxLayout(this);//crée un layout horizontal
    boxForScore->addWidget(scorebutton);// ajouter le bouton au layout
    VLayout->addLayout(boxForScore);//ajouter au layout vertical
    return boxForScore; // rendre la valeur du score
}

void MenuButtons:: miseàjourduscore(int newScore) { // mettre en a jour le score du game
    QString scoreString = "Score: " + QString::number(newScore);
    scorebutton->setText(scoreString);
}

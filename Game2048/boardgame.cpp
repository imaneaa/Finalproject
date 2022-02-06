#include "boardgame.h"
#include<mainwindow.h>

boardgame::boardgame(QWidget* window) : QWidget(window){
    this->setFixedSize(SCREENHEIGHT * 0.5, SCREENHEIGHT* 0.5);// fixer la taille
     this->setStyleSheet("background:rgb(192,192,192);");
   newgrid = new QGridLayout();// nouveau grid layout
     ajouterNouveauNombre();// fonction 1
     créerboardgame();// fonction 2
     settingBoardgame();// fonction 3
     this->setLayout(newgrid);// ajouter le grid

}
boardgame::~boardgame() = default;
void boardgame::reset(){
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            table[i][j]=NULL;// chaque case du tableau il faut la rendre null
}
void boardgame::ajouterNouveauNombre(){ // calculer l'espace vide et ajouter 2  au cell
    int a, b, valeur;
    b = rand() % 4;
    a = rand() % 4;
    while (table[a][b] != NULL) {
         b = rand() % 4;
        a = rand() % 4;
    }
    if(rand() % 100 < 90) // minimiser les chances pour avoir le numéro 4
        valeur = 2;
    else
        valeur = 4;
  table[a][b] = valeur;
}

void boardgame::créerboardgame() { //creer 16 labels  pour les ajouter au vecteur
    for (int i = 0, k = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++, k++) {
            QLabel *label = new QLabel();
            Qlabels.push_back(label);
           Qlabels[k]->setFixedSize( (SCREENHEIGHT * 0.5 / 4) - 10, // definir la taille de chaque label tel que cette dernière est le 1/4 de la taille du screen -10(pour un petit espace libre)
                                     (SCREENHEIGHT * 0.5 / 4) - 10);
           Qlabels[k]->setAlignment(Qt::AlignCenter); //positionnement au centre
            QFont font("Arial Black", (SCREENHEIGHT * 0.5 / 4) / 3); // donner le nombre 1/4 de la taille du label avec un font
            Qlabels[k]->setFont(font);
            Qlabels[k]->setStyleSheet("background:rgb(178,255,0);");// ajuster la couleur du background
        }
    }
}
void boardgame::settingBoardgame() { // ajouter un nouveau cell pour chaque mouvement et apparaitre un board
   ajouterNouveauNombre();
    for (int i = 0, k = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++, k++) {
            if(table[i][j] == 0)
                Qlabels[k]->setText("");
            else
                Qlabels[k]->setNum(table[i][j]); // ajouter le nombre au label
            QString color = "QLabel { background-color : " + changerlacouleur(table[i][j]) + ";}";// calculer la couleur du label
           Qlabels[k]->setStyleSheet(color);//ajouter la couleur
            newgrid->addWidget(Qlabels[k],i, j, Qt::AlignCenter);// ajouter le label au grid
        }
    }
    if(youWon()) { // fonction si le joueur gagne
        QMessageBox message;
        message.setFixedSize(800,800);// fixer la taille
        message.information(this, ":)", "Congratulations (^_^)");// afficher le message
    }
    else if(!youcanMove()) { // si il échoue
        QMessageBox message;
        message.setFixedSize(800,800);// fixer la taille
        message.information(this, ":(", "OUPS YOU LOST (0_0)");// afficher ce message
    }
}

bool boardgame::Novalue() { // pour savoir si une case est vide
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(table[i][j] != NULL)// tester si  il y a une valeur
                return false;// retour 0
        }
    }
    return true;// retour 1
}

bool boardgame::youWon() { // succes si le score est 2048
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(table[i][j] == 2048)// si la valeur est égal à 2048
                return true;// retour 1
        }
    }
    return false;// retour 0
}

bool boardgame::youcanMove() { // savoir si le joueur a une possibilité de faire un autre mouvement
    if(MovetoDown() || MovetoUp() || MovetoRight() || MovetoLeft() || Novalue())// si l'une des fonctions est  vrai
        return true;// retour 1
    else
        return false;// sinon 0
}

QString boardgame::changerlacouleur(int element){ // calculer la couleur (chaque multiplication par 2 - 50 alpha)
    int log, B = COLORRGB, G = COLORRGB, R = COLORRGB;
    if(element == NULL)
        log = 0;
    else
        log = std::log2(element);
    if(log < 5) {// si  log< 5
        B -= 40*log;
    }
    else if (log < 10){// si log < 10
       G -= 40*(log % 4);
       B -= 40*4;
    }
    else {
        R -= 40*(log % 4);//sinon
        G -= 40*4;
        B -= 40*4;
    }
    return "rgb("+ QString::number(R) + ',' + QString::number(G) + ','+ QString::number(B) + ')';// retourner la valeur finale
}

void boardgame::passerleselementsUp() { // faire augmenter vers le haut
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 3; k++) {
            for (int i = 3; i >= 1; i--) {
                if (table[i][j] != NULL && table[i - 1][j] == NULL) {//si la case actuelle et du haut sont vide
                   table[i - 1][j] = table[i][j];//changer les valeurs
                    table[i][j] = NULL;
                }
            }
        }
    }
}

void boardgame::passerleselementsDown() { // faire baisser vers le bas
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++) {
                if (table[i][j] != NULL && table[i + 1][j] == NULL) {//si la case actuelle et du bas sont vide
                    table[i + 1][j] = table[i][j];// changer les valeurs
                    table[i][j] = NULL;
                }
            }
        }
    }
}

void boardgame::passerleselementsLeft() { // faire passer à gauche
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 3; j >= 1; j--) {
                if (table[i][j] != NULL && table[i][j - 1] == NULL) {//si la case actuelle et gauche sont vide
                    table[i][j - 1] = table[i][j];//changer les couleurs
                    table[i][j] = NULL;//rendre 0
                }
            }
        }
    }
}

void boardgame::passerleselementsRight() { // faire passer à droite
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                if (table[i][j] != NULL && table[i][j + 1] == NULL) {//si la case actuelle et droite sont vide
                    table[i][j + 1] = table[i][j];//changer les couleurs
                   table[i][j] = NULL;
                }
            }
        }
    }
}

void boardgame::caseUp(){ // si 2 valeurs sont égaux ,il faut les ajouter
passerleselementsUp();// changer les élements
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (table[i][j] == table[i + 1][j] && table[i][j] != NULL)// si il y a une égalité
            {
                emit Mergenumbers(table[i][j] * 2);
               table[i][j] *= 2;// multiplier par 2
                table[i + 1][j] = NULL;
            }
        }
    }
   passerleselementsUp();
}

void boardgame::caseDown(){ // si 2 valeurs sont égaux ,il faut les ajouter
  passerleselementsDown();// changer les élements
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i > 0; i--) {
            if (table[i][j] == table[i - 1][j] && table[i][j] != NULL)// si il y a une égalité
            {
                emit Mergenumbers(table[i][j] * 2);
               table[i][j] *= 2;
               table[i - 1][j] = NULL;
            }
        }
    }
   passerleselementsDown();
}

void boardgame::caseRight(){ // si 2 valeurs sont égaux ,il faut les ajouter
    passerleselementsRight();
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (table[i][j] == table[i][j - 1] && table[i][j] != NULL)// si il y a une égalité
            {
                emit Mergenumbers(table[i][j] * 2);
               table[i][j] *= 2;
               table[i][j - 1] = NULL;
            }
        }
    }

  passerleselementsRight();
}

void boardgame::caseLeft(){ // si 2 valeurs sont égaux ,il faut les ajouter
   passerleselementsLeft();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if ( table[i][j] ==  table[i][j + 1] &&  table[i][j] != NULL)// si il y a une égalité
            {
                emit Mergenumbers( table[i][j] * 2);
                table[i][j] *= 2;
                table[i][j + 1] = NULL;
            }
        }
    }
  passerleselementsLeft();
}

bool boardgame::MovetoUp() { // retourner vrai si il ya la possibilité d'un autre mouvement vers le haut
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 1; i--) {
            if (( table[i][j] != NULL &&  table[i - 1][j] == NULL) || ((  table[i][j] ==  table[i - 1][j]) &&  table[i][j] != NULL)) {// si une vrai il faut changer les élements
                return true;
            }
        }
    }
    return false;
}

bool boardgame::MovetoDown() { // retourner vrai si il ya la possibilité d'un autre mouvement vers le bas
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (( table[i][j] != NULL && table[i + 1][j] == NULL) || (( table[i][j] == table[i + 1][j]) && table[i][j] != NULL)) {// si une vrai il faut changer les élements
                return true;
            }
        }
    }
    return false;
}

bool boardgame::MovetoLeft() {// retourner vrai si il ya la possibilité d'un autre mouvement vers la gauche
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 1; j--) {
            if ((table[i][j] != NULL && table[i][j - 1] == NULL) || (( table[i][j] == table[i][j - 1]) && table[i][j] != NULL)) {// si une vrai il faut changer les élements
                return true;
            }
        }
    }
    return false;
}

bool boardgame::MovetoRight() { // retourner vrai si il ya la possibilité d'un autre mouvement vers la droite
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if ((table[i][j] != NULL && table[i][j + 1] == NULL) || (( table[i][j] == table[i][j + 1]) && table[i][j] != NULL)) {// si une vrai il faut changer les élements
                return true;
            }
        }
    }
    return false;
}

void boardgame::keyPressEvent(QKeyEvent * e) { // l'évenement du clavier
    if(!youWon()) {
        if(MovetoUp() &&( e->key() == Qt::Key_Up)) {
            caseUp();
            settingBoardgame();
        }
        if(MovetoUp() &&( e->key() == Qt::Key_Z)) {
            caseUp();
            settingBoardgame();
        }
        if(MovetoRight() &&( e->key() == Qt::Key_Right)) {
            caseRight();
            settingBoardgame();
        }
        if(MovetoRight() &&( e->key() == Qt::Key_S)) {
            caseRight();
            settingBoardgame();
        }
        if(MovetoLeft() &&( e->key() == Qt::Key_Left)) {
            caseLeft();
           settingBoardgame();
        }
        if(MovetoLeft() &&( e->key() == Qt::Key_Q)) {
            caseLeft();
           settingBoardgame();
        }
        if(MovetoDown() &&( e->key() == Qt::Key_Down)) {
            caseDown();
           settingBoardgame();
        }
        if(MovetoDown() &&( e->key() == Qt::Key_W)) {
            caseDown();
           settingBoardgame();
        }

        if(e->key() == Qt::Key_P ){// Clicker la lettre p pour new game
            reset();
          //  miseàjourduscore(scoreValue = 0);
            settingBoardgame();
        }
        if (e->key() == Qt::Key_A)
               qApp->exit();

    }
}

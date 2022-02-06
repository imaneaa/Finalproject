#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowTitle("2048 Game"); // titre de la fenetre
    this->setWindowIcon(QIcon(":/../Downloads/2048.ico")); // icon
    this->setStyleSheet("background:rgb(204,192,172);");
   // this->setStyleSheet("background-image: url(:/../Desktop/Mail/back.jpg)");
    //this->setStyleSheet("{background-image: url(qrc:/../Desktop/Mail/new game.jpg);}");
    Tab = new boardgame;
    But = new MenuButtons;


    LayoutPrincipale = new QVBoxLayout(this);//créer nouveau layout
    LayoutPrincipale->setAlignment(Qt::AlignCenter);
   LayoutPrincipale->addWidget(Tab); // ajouter board à mainwindow
   Tab->setFocusPolicy(Qt::StrongFocus);// interaction avec le clavier
   LayoutPrincipale->addWidget(But); // ajouter les buttons à mainwindow
    ui->centralwidget->setLayout(  LayoutPrincipale);//ajouter le mainlayout
    connect(But, &MenuButtons::newGame, this, &MainWindow::nouvelleGameSlot);
 //    connect(bar, &MenuButtons::newGame, this, &MainWindow::howtoplay); // faire la connection
    connect(Tab, &boardgame::Mergenumbers, this, &MainWindow::combinerSlot);// connection
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::nouvelleGameSlot() {  //fonction pour regenerer le jeu
      But->miseàjourduscore( 0);
    Tab->reset();// refaire boardgame à zero
    Tab->settingBoardgame();// créer à  nouveau boardgame
 //update du score

}
//void MainWindow::howtoplay(){
//    QMessageBox message;
  //  message.setFixedSize(800,800);
 //   message.information(this, ":(", "use your keyboard and start moving the lables to add equal numbers  ");
//}


void MainWindow::combinerSlot(int num) { //mise a jour de score
    scoreValue += num;//ajouter au score
    But->miseàjourduscore(scoreValue);
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include<QVBoxLayout>
#include "boardgame.h"
#include "menubuttons.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
       int scoreValue = 0;
public slots:
        void combinerSlot(int);
        void nouvelleGameSlot();
       // void howtoplay();

private:

    boardgame *Tab;
    MenuButtons* But;
    QVBoxLayout* LayoutPrincipale;
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H

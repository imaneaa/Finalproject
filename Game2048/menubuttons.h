#ifndef MENUBUTTONS_H
#define MENUBUTTONS_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QObject>
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QVector>
#include <QMainWindow>
#include <QSpacerItem>
#include <QTextFormat>
#include <QFont>
#include <QString>
#include <QKeyEvent>
#include <QMessageBox>

class MenuButtons : public QWidget
{
    Q_OBJECT

private:
    const int SCREENHEIGHT = 1000;
    const int SCREENLWIDTH= 800;

signals:
        void newGame();
public:
    MenuButtons(int = 0, QWidget* = nullptr);
    ~MenuButtons();
    QHBoxLayout* ajusterlescore(int val = 0);
    QVBoxLayout *VLayout;
    QLabel* scorebutton;
    void miseàjourduscore(int = 0);

};

#endif // MENUBUTTONS_H

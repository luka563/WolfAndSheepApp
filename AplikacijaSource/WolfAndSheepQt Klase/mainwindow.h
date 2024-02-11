#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playAsWolfButton_clicked();
    void on_playAsSheepButton_clicked();
    void on_ResetGame_clicked();


    void on_computerVscomputer_clicked();

private:
    Ui::MainWindow *ui;
    void playGame(int i,int j);
    void disconnectSlot();
    void connectSlot();
    void printBoard();
    void reset();
    void setValues(QString player,double duration,double evaluations, double eps, int depth);
    void computerVScomputer();
    void disableElements();
    void setEvaluation();
    void startProgressBar();

    void resolution1600();
    void resolution800();
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "clickhandle.h"
#include <QMessageBox>
#include "gamelogic.h"
#include <QElapsedTimer>
#include <QThread>
#include <QRandomGenerator>
#define SIZE 8
ClickHandle* clickHandle;
QList<QLabel*> list;
double totalEvaluations = 0;
int startX=9,startY=9,player,picSize = 95;
int offsetY=21,offsetX=0;
char Board[SIZE][SIZE];
GameLogic game;
Move bestMove;
bool firstInputDone = false;
CELL firstCELL;
QLabel *labelRed;
QElapsedTimer timer;
std::chrono::duration<double> duration;
QString debugText;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    game.initialize(Board);
    clickHandle = new ClickHandle(this);
    startX = 9;
    startY = 9;
    QPixmap board("board");
    ui->label->setPixmap(board);
    ui->label->setGeometry(startX,startY,50,50);
    QLabel* labelSheep = new QLabel(this);
    QLabel* labelWolf1 = new QLabel(this);
    QLabel* labelWolf2 = new QLabel(this);
    QLabel* labelWolf3 = new QLabel(this);
    QLabel* labelWolf4 = new QLabel(this);
    list << labelSheep << labelWolf1<<labelWolf2<<labelWolf3<<labelWolf4;

    labelRed = new QLabel(this);
    labelRed->setObjectName("myLabel");
    labelRed->setStyleSheet("QLabel#myLabel { background-color: rgba(255, 0, 0, 0.2); }");

    for(int i=18;i>0;i--)
    {
        ui->comboBox->addItem("Depth "+ QString::number(i));
    }
    ui->comboBox->setCurrentIndex(0);

    QAction *resolution800Action = ui->action800x600;
    QAction *resolution1600Action = ui->action1600x900;
    connect(resolution800Action, &QAction::triggered, this, &MainWindow::resolution800);
    connect(resolution1600Action, &QAction::triggered, this, &MainWindow::resolution1600);


    QPixmap imageSheep("sheep");
    QPixmap imageWolf("wolf");
    for(int i=0;i< list.length();i++)
    {
        list[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
        list[i]->setScaledContents(true);
        if(i == 0)
            list[i]->setPixmap(imageWolf);
        else
            list[i]->setPixmap(imageSheep);
        list[i]->hide();
    }
    printBoard();
    connectSlot();
    ui->label->installEventFilter(clickHandle);
    ui->ResetGame->setEnabled(false);
}
void MainWindow::startProgressBar()
{
    ui->progressBar->setValue(100);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::playGame(int i,int j)
{    
    disconnectSlot();
    if(player == 1)
    {
        CELL wolf = game.coordinatesOfWolf(Board);
        if(game.isValid(wolf.i,wolf.j,i,j) && game.isFree(Board,CELL{i,j}))
        {
            game.makeMoveForWolf(Board,Move{wolf.i,wolf.j,i,j});

            if (game.isGameOver(Board) == 999)
            {
                printBoard();
                QMessageBox::information(this, "Game over", "You won");
                disconnectSlot();
            }else{


                startProgressBar();
                auto start = std::chrono::steady_clock::now();
                bestMove = game.BestMoveMinimizing(Board, game.DEPTH);               
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> duration = end - start;                
                qDebug()<< "Sheep Time(s):"<< duration.count() <<" Evaluations: " << game.totalEvaluations <<"Evaluations per second: "<< game.totalEvaluations/duration.count() <<"DEPTH: "<<game.getDepth();
                /*
                debugText = QString("Sheep Time(s): %1 Evaluations: %2 Evaluations per second: %3 DEPTH: %4")
                                        .arg(duration.count())
                                        .arg(game.totalEvaluations)
                                        .arg(static_cast<double>(game.totalEvaluations) / duration.count())
                                        .arg(game.getDepth());
                */
                setValues("Sheep",duration.count(),game.totalEvaluations,static_cast<double>(game.totalEvaluations) / duration.count(),game.getDepth());
                game.makeMove(Board, bestMove);
                ui->progressBar->setValue(0);
                printBoard();

                int numMoves = 0;
                Move* moves = game.LegalSheepsMoves(Board,&numMoves);
                if(numMoves==0)
                {
                    QMessageBox::information(this, "Game over", "You won");
                    delete moves;
                    disconnectSlot();
                }
                else
                {
                delete moves;
                connectSlot();
                }

            }
            if(game.isGameOver(Board) == -999){
                QMessageBox::information(this, "Game over", "You lost");
                disconnectSlot();
            }
        }else
        {
            QMessageBox::information(this, "Invalid move", "Please select valid move");
            connectSlot();
        }
    }else{
        if(player == 2)
        {
            if(firstInputDone == false)
            {
                int numMoves;
                CELL* sheeps = game.coordinatesOfSheeps(Board);
                for(int w=0;w<4;w++)
                {

                    if(sheeps[w].i == i && sheeps[w].j==j && (Board[i-1][j-1]==' ' || Board[i-1][j+1]==' '))
                    {
                        firstInputDone = true;
                        firstCELL={i,j};
                        printBoard();
                        connectSlot();
                        return;
                    }
                }
                QMessageBox::information(this, "Invalid move", "Invalid move,select wolf");
                connectSlot();
            }else
            {
                if(firstCELL.i - 1 == i && abs(firstCELL.j - j)==1 && game.isFree(Board,CELL{i,j}))
                {
                    disconnectSlot();
                    //
                    game.makeMove(Board,Move{firstCELL.i,firstCELL.j,i,j});
                    printBoard();
                    if(game.isGameOver(Board)==-999)
                    {
                        QMessageBox::information(this, "Game over", "You won");
                        disconnectSlot();
                        return;
                   }
                    startProgressBar();
                    auto start = std::chrono::steady_clock::now();
                    bestMove = game.BestMoveMaximizing(Board,game.DEPTH+1);
                    auto end = std::chrono::steady_clock::now();
                    std::chrono::duration<double> duration = end - start;
                    qDebug()<< "Wolf Time(s):"<< duration.count() <<" Evaluations: " << game.totalEvaluations <<"Evaluations per second: "<< game.totalEvaluations/duration.count() <<"DEPTH: "<<game.getDepth()+1;
                    /*
                    debugText = QString("Wolf Time(s): %1 Evaluations: %2 Evaluations per second: %3 DEPTH: %4")
                                            .arg(duration.count())
                                            .arg(game.totalEvaluations)
                                            .arg(static_cast<double>(game.totalEvaluations) / duration.count())
                                            .arg(game.getDepth()+1);
                    */
                    setValues("Wolf",duration.count(),game.totalEvaluations,static_cast<double>(game.totalEvaluations) / duration.count(),game.getDepth()+1);
                    game.makeMoveForWolf(Board,bestMove);
                    firstInputDone = false;
                    ui->progressBar->setValue(0);
                    printBoard();
                    if(game.isGameOver(Board)==999)
                        QMessageBox::information(this, "Game over", "You lost");                    
                    connectSlot();
                    return;
                }
                QMessageBox::information(this, "Invalid move", "select free square in front of wolf");
                connectSlot();
            }
        }
    }

}
void MainWindow::disconnectSlot()
{
    disconnect(clickHandle, &ClickHandle::clicked, this, nullptr);
}
void MainWindow::connectSlot()
{
    connect(clickHandle, &ClickHandle::clicked, this, [=](int x, int y) {
        int i=y/picSize;
        int j=x/picSize;
        playGame(i,j);
    });
}
void MainWindow::printBoard()
{
    ui->label->setGeometry(startX,startY,50,50);
    if(firstInputDone)
    {
    labelRed->setGeometry(startX+firstCELL.j*picSize+offsetX ,startY+firstCELL.i*picSize + offsetY,picSize,picSize); //5
    labelRed->show();
    }else
    labelRed->hide();
    int sheep = 1;
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(Board[i][j] == '0')
            {
                list[0]->setGeometry(startX+j*picSize+offsetX,startY+i*picSize + offsetY,picSize,picSize);
                list[0]->show();
            }else
                if(Board[i][j]=='1')
                {
                    list[sheep]->setGeometry(startX+j*picSize+offsetX,startY+i*picSize + offsetY,picSize,picSize);
                    list[sheep]->show();
                    sheep++;
                }
    ui->label->setGeometry(startX,startY,50,50);//5
    QApplication::processEvents();
}
void MainWindow::computerVScomputer()
{
    while(game.isGameOver(Board) == 0)
    {
        startProgressBar();
        auto start = std::chrono::steady_clock::now();
        bestMove = game.BestMoveMaximizing(Board,game.DEPTH+1);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        qDebug()<< "Wolf Time(s):"<< duration.count() <<" Evaluations: " << game.totalEvaluations <<"Evaluations per second: "<< game.totalEvaluations/duration.count() <<"DEPTH: "<<game.getDepth()+1;
        ui->progressBar->setValue(0);

        int remainingTime = 1000 - std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        if (remainingTime > 0) {
                QThread::msleep(remainingTime);
        }
        game.makeMoveForWolf(Board,bestMove);
        /*
        debugText = QString("Wolf Time(s): %1 Evaluations: %2 Evaluations per second: %3 DEPTH: %4")
                                .arg(duration.count())
                                .arg(game.totalEvaluations)
                                .arg(static_cast<double>(game.totalEvaluations) / duration.count())
                                .arg(game.getDepth()+1);
        */
        setValues("Wolf",duration.count(),game.totalEvaluations,static_cast<double>(game.totalEvaluations) / duration.count(),game.getDepth());

        printBoard();
        if(game.isGameOver(Board)!= 0)
                break;
        startProgressBar();
        start = std::chrono::steady_clock::now();
        bestMove = game.BestMoveMinimizing(Board,game.DEPTH);
        end = std::chrono::steady_clock::now();
        duration = end - start;
        qDebug()<< "Sheep Time(s):"<< duration.count() <<" Evaluations: " << game.totalEvaluations <<"Evaluations per second: "<< game.totalEvaluations/duration.count() <<"DEPTH: "<<game.getDepth();
        remainingTime = 1000 - std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        ui->progressBar->setValue(0);

        if (remainingTime > 0) {
                QThread::msleep(remainingTime);
        }
        /*
        debugText = QString("Sheep Time(s): %1 Evaluations: %2 Evaluations per second: %3 DEPTH: %4")
                                .arg(duration.count())
                                .arg(game.totalEvaluations)
                                .arg(static_cast<double>(game.totalEvaluations) / duration.count())
                                .arg(game.getDepth());
       \*/
        setValues("Sheep",duration.count(),game.totalEvaluations,static_cast<double>(game.totalEvaluations) / duration.count(),game.getDepth());

        game.makeMove(Board,bestMove);
        printBoard();

        int numMoves = 0;
        Move* moves = game.LegalSheepsMoves(Board,&numMoves);
        if(numMoves==0)
        {
                delete moves;
                disconnectSlot();
                break;
        }
    }
    ui->ResetGame->setEnabled(true);
}

void MainWindow::on_playAsWolfButton_clicked()
{
    disableElements();
    player = 1;
    connectSlot();


}
void MainWindow::disableElements()
{
    ui->playAsWolfButton->setEnabled(false);
    ui->playAsSheepButton->setEnabled(false);
    ui->ResetGame->setEnabled(true);
    ui->computerVscomputer->setEnabled(false);
    ui->comboBox->setEnabled(false);

    ui->groupBox->setEnabled(false);

    int selectedIndexDepth = ui->comboBox->count() - ui->comboBox->currentIndex();
    game.setDepth(selectedIndexDepth);
    setEvaluation();
    if(ui->AlphaBeta->isChecked())
        game.allowAlphaBeta();
    else
        game.denyAlphaBeta();
    ui->AlphaBeta->setEnabled(false);
}

void MainWindow::on_playAsSheepButton_clicked()
{
    disableElements();
    player = 2;
    firstInputDone = false;
    setEvaluation();
    disconnectSlot();
    startProgressBar();
    auto start = std::chrono::steady_clock::now();
    bestMove = game.BestMoveMaximizing(Board,game.DEPTH);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    qDebug()<< "Wolf Time(s):"<< duration.count() <<" Evaluations: " << game.totalEvaluations <<"Evaluations per second: "<< game.totalEvaluations/duration.count() <<"DEPTH: "<<game.getDepth()+1;
    ui->progressBar->setValue(0);
    /*
    debugText = QString("Wolf Time(s): %1 Evaluations: %2 Evaluations per second: %3 DEPTH: %4")
                            .arg(duration.count())
                            .arg(game.totalEvaluations)
                            .arg(static_cast<double>(game.totalEvaluations) / duration.count())
                            .arg(game.getDepth()+1);
    */
    setValues("Wolf",duration.count(),game.totalEvaluations,static_cast<double>(game.totalEvaluations) / duration.count(),game.getDepth()+1);


    game.makeMoveForWolf(Board,bestMove);
    printBoard();
    connectSlot();
}
void MainWindow::reset()
{
    game.initialize(Board);
    firstInputDone = false;
    printBoard();
    ui->playAsWolfButton->setEnabled(true);
    ui->playAsSheepButton->setEnabled(true);
    ui->ResetGame->setEnabled(false);    
    ui->computerVscomputer->setEnabled(true);
    ui->AlphaBeta->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->groupBox->setEnabled(true);
    disconnectSlot();
    qDebug()<< "---------------------------------- Reset -----------------------------------";
    setValues(" ",0,0,0,0);
    ui->progressBar->setValue(0);

}

void MainWindow:: setEvaluation()
{
    if(ui->radioButton_1->isChecked())
        game.SPEED = 0;
    if(ui->radioButton_2->isChecked())
        game.SPEED = 1;
    if(ui->radioButton_3->isChecked())
        game.SPEED = 2;
}

void MainWindow::on_ResetGame_clicked()
{
    reset();
}
void MainWindow::setValues(QString player,double duration,double evaluations, double eps, int depth)
{
    ui->label_5->setText("Player : "+player);
    ui->label_3->setText(QString("Time in seconds : %1").arg(duration));
    ui->label_6->setText(QString("Number of evaluations : %1").arg(evaluations));
    ui->label_4->setText(QString("Evaluations per second : %1").arg(eps));
    ui->label_7->setText(QString("Depth : %1").arg(depth));
}


void MainWindow::on_computerVscomputer_clicked()
{
    disableElements();
    setEvaluation();
    ui->ResetGame->setEnabled(false);
    computerVScomputer();
}

void MainWindow::resolution800()
{
    int newWidth = 800;
    int newHeight = 600;
    setMaximumSize(800,521);
    setMinimumSize(800,521);
    ui->label->setMaximumSize(440,440);
    ui->label->setMinimumSize(440,440);
    QFont font;
    font.setPointSize(12);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);
    startX=9;
    startY= 19;
    offsetY = 23;
    offsetX = 0;
    player,picSize = 55;
    resize(newWidth, newHeight);
    ui->label->setGeometry(startX,startY,50,50);
    printBoard();
}

void MainWindow::resolution1600()
{
    int newWidth = 1600;
    int newHeight = 800;
    setMaximumSize(1300,821);
    setMinimumSize(1300,821);
    ui->label->setMaximumSize(760,760);
    ui->label->setMinimumSize(760,760);
    QFont font;
    font.setPointSize(18);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);
    startX=9;
    startY=9;
    offsetY = 21;
    offsetX = 0;
    player,picSize = 95;    
    resize(newWidth, newHeight);
    ui->label->setGeometry(startX,startY,50,50);
    printBoard();
}

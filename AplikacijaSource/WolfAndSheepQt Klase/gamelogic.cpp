#include "gamelogic.h"

GameLogic::GameLogic()
{
    DEPTH = 18;
    allowAlphaBeta();    
    SPEED = 0;
}
GameLogic::~GameLogic()
{    
}


int GameLogic::getDepth()
{
    return DEPTH;
}
void GameLogic::setDepth(int depth)
{
    DEPTH = depth;
    return;
}
int GameLogic::Min(int a, int b) {
    return (a < b) ? a : b;
}
int GameLogic::Max(int a, int b) {
    return (a > b) ? a : b;
}
void GameLogic::initialize(char board[][SIZE]) {   
    int i, j;
    for (i = 0;i < SIZE;i++)
        for (j = 0;j < SIZE;j++)
            if ((j + i) % 2 == 0)
                board[i][j] = 'X';
            else
                board[i][j] = ' ';
    board[0][3] = '0';
    wolf.i = 0;
    wolf.j = 3;
    int br=0;
    for (i = 0; i < SIZE; i += 2)
    {
        board[7][i] = '1';        
    }
}
int GameLogic::MinimaxValue(char state[][SIZE], int depth, int alpha, int beta, int isMaximizingPlayer) {    
    if (depth == 0 || isGameOver(state) != 0)
    {
        totalEvaluations++;        
        if (isMaximizingPlayer)
            return evaluate(state) + DEPTH - depth;
        return evaluate(state) - DEPTH + depth;
    }
    if (isMaximizingPlayer)
    {
        int bestScore = INT_MIN,numMoves;
        struct Move* possibleMoves = LegalWolfMoves(state,&numMoves);

        for (int i = 0;i < numMoves;i++)
        {
            makeMoveForWolf(state, possibleMoves[i]);
            bestScore = Max(bestScore, MinimaxValue(state, depth - 1, alpha, beta, 0));
            revertMoveForWolf(state, possibleMoves[i]);


            if(AlphaBeta)
            {
            alpha = Max(alpha, bestScore);
            if (beta <= alpha)
            {
                break;
            }
            }
        }
        delete[] possibleMoves;
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX,numMoves;
        struct Move* possibleMoves = LegalSheepsMoves(state,&numMoves);

        for (int i = 0;i < numMoves;i++)
        {
            makeMoveForSheep(state, possibleMoves[i]);
            bestScore = Min(bestScore, MinimaxValue(state, depth - 1, alpha, beta, 1));
            revertMoveForSheep(state, possibleMoves[i]);

            if(AlphaBeta)
            {
            beta = Min(beta, bestScore);
            if (beta <= alpha)
            {
                break;
            }
            }
        }
        delete[] possibleMoves;
        return bestScore;
    }
}
struct Move GameLogic::BestMoveMinimizing(char state[][SIZE], int depth) {
    totalEvaluations = 0;
    int bestScore = INT_MAX;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    struct Move bestMove;
    bool bestMoveFound = false;
    int numMoves;
    struct Move* possibleMoves = LegalSheepsMoves(state,&numMoves);
    if(numMoves == 1)
    {
        bestMove = possibleMoves[0];
        delete[] possibleMoves;

        return bestMove;
    }
    for (int i = 0;i < numMoves;i++)
    {
        makeMoveForSheep(state, possibleMoves[i]);
        int score = MinimaxValue(state, depth - 1, alpha, beta, 1);
        revertMoveForSheep(state, possibleMoves[i]);
        if (score < bestScore)
        {
            bestScore = score;
            bestMove = possibleMoves[i];
            bestMoveFound = true;
        }
        if(AlphaBeta)
        {
        beta = Min(beta, bestScore);
        if (beta <= alpha)
        {
            break;
        }
        }
    }
    if(bestMoveFound == false)
        bestMove = possibleMoves[0];
    delete[] possibleMoves;

    return bestMove;
}


struct Move* GameLogic::LegalSheepsMoves(char board[][SIZE], int* numMoves) {
    int z;
    *numMoves = 0;
    struct Move* moves = new Move[8];
    struct CELL* wolves = coordinatesOfSheeps(board);

    for (z = 0; z < 4; z++) {
        int i = wolves[z].i;
        int j = wolves[z].j;

        //gore levo
        if (board[i - 1][j - 1] == ' ')
            moves[(*numMoves)++] = Move{ i, j, i - 1, j - 1 };

        //gore desno
        if (board[i - 1][j + 1] == ' ')
            moves[(*numMoves)++] = Move{ i, j, i - 1, j + 1 };
    }

    if (*numMoves < 8) {
        Move* temp = new Move[*numMoves];
        std::copy(moves, moves + *numMoves, temp);
        delete[] moves;
        moves = temp;
    }

    delete[] wolves;
    return moves;
}



struct CELL*  GameLogic::coordinatesOfSheeps(char board[][SIZE]) {
    int br = 0,i,j;
    struct CELL* cells = new CELL[4];

    for (i = SIZE-1; i >=0; i--)
        if(wolf.j<4)
        for (j = (i+1)%2; j < SIZE; j+=2)
        //for(j=0;j<SIZE;j++)
        {           
            if (board[i][j] == '1')
            {
                cells[br++] = CELL{ i, j };
                if(br == 4)
                    return cells;
            }
        }

    else
        for (j = (SIZE-1) - (i%2) ; j >=0; j-=2)
        //for (j = SIZE-1; j >=0; j--)
        {           
            if (board[i][j] == '1')
            {
                cells[br++] = CELL{ i, j };
                if(br == 4)
                    return cells;
            }
        }

    return cells;
}
void GameLogic::makeMoveForWolf(char board[][SIZE], struct Move m) {
    board[m.endI][m.endJ] = board[m.startI][m.startJ];
    board[m.startI][m.startJ]=' ';
    wolf.i = m.endI;
    wolf.j = m.endJ;
}

void GameLogic::makeMoveForSheep(char board[][SIZE], struct Move m) {
    board[m.endI][m.endJ] = board[m.startI][m.startJ];
    board[m.startI][m.startJ]=' ';

}
void GameLogic::revertMoveForSheep(char board[][SIZE], struct Move m) {
    board[m.startI][m.startJ]=board[m.endI][m.endJ];
    board[m.endI][m.endJ] = ' ';

}


void GameLogic::revertMoveForWolf(char board[][SIZE], struct Move m) {
    //char pom = board[m.startI][m.startJ];
    //board[m.startI][m.startJ] = board[m.endI][m.endJ];
    //board[m.endI][m.endJ]=pom;

    board[m.startI][m.startJ]=board[m.endI][m.endJ];
    board[m.endI][m.endJ] = ' ';
    wolf.i = m.startI;
    wolf.j = m.startJ;
}



void GameLogic::makeMove(char board[][SIZE], struct Move m) {
    //char pom = board[m.startI][m.startJ];
    //board[m.startI][m.startJ] = board[m.endI][m.endJ];
    //board[m.endI][m.endJ]=pom;

    board[m.endI][m.endJ] = board[m.startI][m.startJ];
    board[m.startI][m.startJ]=' ';


    //zasto radi i bez ovoga
    if(m.startI == wolf.i && m.startJ == wolf.j)
    {
    wolf.i = m.endI;
    wolf.j = m.endJ;
    }

}

    void GameLogic::revertMove(char board[][SIZE], struct Move m) {
    //char pom = board[m.startI][m.startJ];
    //board[m.startI][m.startJ] = board[m.endI][m.endJ];
    //board[m.endI][m.endJ]=pom;

    board[m.startI][m.startJ]=board[m.endI][m.endJ];
    board[m.endI][m.endJ] = ' ';
    /*
    if(m.endI == sheep.i && m.endJ == sheep.j)
    {
    sheep.i = m.startI;
    sheep.j = m.startJ;
    }
    */
}

    struct Move* GameLogic::LegalWolfMoves(char board[][SIZE], int* numMoves) {

    int i = wolf.i;
    int j = wolf.j;
    *numMoves = 0;
    struct Move* moves = new Move[4];

    // dole desno
    if (board[i + 1][j + 1] == ' ')
    moves[(*numMoves)++] = Move{ i, j, i + 1, j + 1 };


    // dole levo
    if (board[i + 1][j - 1] == ' ')
    moves[(*numMoves)++] = Move{ i, j, i + 1, j - 1 };


    // gore desno
    if (board[i - 1][j + 1] == ' ')
    moves[(*numMoves)++] = Move{ i, j, i - 1, j + 1 };


    // gore levo
    if (board[i - 1][j - 1] == ' ')
    moves[(*numMoves)++] = Move{ i, j, i - 1, j - 1 };


    if (*numMoves < 4) {
    Move* temp = new Move[*numMoves];
    std::copy(moves, moves + *numMoves, temp);
    delete[] moves;
    moves = temp;
    }

    return moves;
    }

int GameLogic::isGameOver( char board[][SIZE]) {   
    if (!canWolfMove(wolf.i, wolf.j, board))
        return -999;
    else
        if (wolf.i == SIZE - 1)
            return 999;
    return 0;
}
int GameLogic::isValid(int startI, int startJ, int destI, int destJ) {
    //if (destI >= SIZE || destI < 0 || destJ >= SIZE || destJ < 0 || startI >= SIZE || startI < 0 || startJ >= SIZE || startJ < 0)
    //    return 0;
    if (abs(destJ - startJ) != 1 || abs(startI - destI) != 1)
        return 0;
    //if ( abs(startI - destI) != 1)
    //    return 0;
    return 1;
}

bool GameLogic::canWolfMove(int i, int j, char board[][SIZE]) {

    if (board[i + 1][j + 1] == ' ')
        return true;

    if (board[i + 1][j - 1] == ' ')
        return true;

    if (board[i - 1][j - 1] == ' ')
        return true;

    if (board[i - 1][j + 1] == ' ')
        return true;

    return false;
}
struct CELL GameLogic::coordinatesOfWolf(char board[][SIZE]) {
    struct CELL c ={0,0};
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = (i+1)%2; j < SIZE; j+=2)
            if (board[i][j] == '0')
            {
                c.i = i;
                c.j = j;
                return c;
            }
    return c;
}
struct Move GameLogic::BestMoveMaximizing(char state[][SIZE], int depth) {
    totalEvaluations = 0;
    int bestScore = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    struct Move bestMove;
    bool bestMoveFound = false;
    int numMoves;
    struct Move* possibleMoves = LegalWolfMoves(state,&numMoves);
    if(numMoves == 1)
    {
        bestMove = possibleMoves[0];
        delete[] possibleMoves;        
        return bestMove;
    }


    for (int i = 0;i < numMoves;i++)
    {
        makeMoveForWolf(state, possibleMoves[i]);
        int score = MinimaxValue(state, depth - 1, alpha, beta, 0);
        revertMoveForWolf(state, possibleMoves[i]);

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = possibleMoves[i];
            bestMoveFound = true;
        }
        if(AlphaBeta)
        {
        alpha = Max(alpha, bestScore);
        if (beta <= alpha)
        {
            break;
        }
        }
    }
    if(bestMoveFound == false)
        bestMove = possibleMoves[0];
    delete[] possibleMoves;
    return bestMove;
}
bool GameLogic::isFree(char board[][SIZE],CELL cell)
{
    return board[cell.i][cell.j]==' ';
}
void GameLogic::allowAlphaBeta()
{
    AlphaBeta = true;
}
void GameLogic::denyAlphaBeta()
{
    AlphaBeta = false;
}

int GameLogic::evaluate(char board[][SIZE]) {

    if(SPEED == 0)
        return evaluateSimple(board);
    else
    if(SPEED == 1)
        return evaluateFast(board);
    else
        return evaluateSmart(board);
}
int GameLogic::evaluateSimple(char board[][SIZE])
{
    if (!canWolfMove(wolf.i, wolf.j, board))
        return INT_MIN;
    else
        if (wolf.i == SIZE - 1)
        return INT_MAX;
    return wolf.i;
}

int GameLogic::evaluateFast(char board[][SIZE])
{
    if (!canWolfMove(wolf.i, wolf.j, board))
        return INT_MIN;
    else
        if (wolf.i == SIZE - 1)
        return INT_MAX;


    struct CELL* sheep = coordinatesOfSheeps(board);

    if(sheep[0].i == sheep[1].i && sheep[1].i == sheep[2].i &&
        sheep[2].i == sheep[3].i && wolf.i < sheep[0].i)
    {
        int ret = INT_MIN/(sheep[0].i +1);
        delete[] sheep;
        return ret;
    }
    if(wolf.i >= sheep[0].i)
    {
        delete[] sheep;
        return INT_MAX/2;
    }
    int left = 0,i;

    for( i = 0;i<4;i++)
        if(sheep[i].j<4)
        left++;
    if(left == 2)
    {
        delete[] sheep;
        return wolf.i * 2 + INT_MIN/4;
    }

    int volvesSum = 0;
    for ( i = 0; i < 4; i++)
        volvesSum += abs(sheep[i].i - wolf.i);

    delete[] sheep;
    return wolf.i * 2 - volvesSum;
}
int GameLogic::evaluateSmart(char board[][SIZE]) {
    if (!canWolfMove(wolf.i, wolf.j, board))
        return INT_MIN;
    else
        if (wolf.i == SIZE - 1)
        return INT_MAX;

    struct CELL* sheep = coordinatesOfSheeps(board);
    if(wolf.i >= sheep[0].i)
    {
        delete[] sheep;
        return INT_MAX/(7 - wolf.i);
    }
    int eval = 0;


    if(sheep[0].i == sheep[1].i && sheep[1].i == sheep[2].i &&
        sheep[2].i == sheep[3].i && wolf.i < sheep[0].i)
        eval+=INT_MIN/(sheep[0].i +5);

    int left = 0,i;

    for( i = 0;i<4;i++)
        if(sheep[i].j<4)
        left++;
    if(left == 2)
        eval+= INT_MIN/4;

    int sum = 0;
    for ( i = 0; i < 4; i++)
        eval += abs(sheep[i].i - wolf.i)+abs(sheep[i].j - wolf.j);

    int SheepMoves;
    int WolvesMoves;

    struct Move* possibleWolvesMoves = LegalWolfMoves(board,&WolvesMoves);
    struct Move* possibleSheepMoves = LegalSheepsMoves(board,&SheepMoves);

    delete possibleSheepMoves;
    delete possibleWolvesMoves;

    eval+= 10* WolvesMoves;
    eval-= SheepMoves;

    delete[] sheep;
    return wolf.i - eval;
}


#include <stdio.h>
#include <stdlib.h>

/*char mainGrid[9][7]=
{
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {'1','1','1','1','1',' ',' '}
};*/


typedef struct {
    char name[9];
    int score;
    int moves;
    _Bool identifier;
}playerData;

//initialized after game mode selection:
playerData player1 = {"player 1", 0, 0, 0};
playerData player2 = {"player 2", 0, 0, 1};

int main()
{
    /*printf("%d \n",countHorizontally(0,5,3));
    printf("%d \n",countVertically(0,5,3));
    printf("%d",countDiagonally(0,5,3));*/
    updateScore(&player1,5,3);
    printf("%d \n",player1.score);
    addMoves(&player2);
    addMoves(&player2);
    addMoves(&player2);
    printf("%d",player2.moves);

    return 0;
}

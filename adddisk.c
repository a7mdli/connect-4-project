#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#define ROW 9
#define COL 7

time_t start_time;

int lastMove;

int moves;

char figures[2] = {'x','o'};

char gridarr[ROW][COL];

typedef struct
{
    char name[9];
    int score;
    int moves;
    _Bool identifier;
} playerData;

playerData player1 = {"player 1",0,0,0};
playerData player2 = {"player 2",0,0,1};

typedef struct {
    int i;
    int j;
    playerData movingPlayer;
}gameInfo;

gameInfo undoList[ROW*COL+1];

void updateUndoList (playerData playerMoved, int i, int j, int moveNumber) {
    undoList[moveNumber].i = i;
    undoList[moveNumber].j = j;
    undoList[moveNumber].movingPlayer = playerMoved;
}

void undo (int *move) {
    gridarr[(undoList[*move-1]).i][(undoList[*move-1]).j] = '-';
    playerData *movedPlayer;
    if (undoList[*move-1].movingPlayer.identifier == player1.identifier) {
        movedPlayer = &player1;
        (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
        (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;
    }
    else if (undoList[*move-1].movingPlayer.identifier == player2.identifier) {
        movedPlayer = &player2;
        (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
        (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;
    }
    *move=*move - 1;
    //print(gridarr);
}

void redo (int *move) {
    gridarr[undoList[*move+1].i][undoList[*move+1].j] = undoList[*move+1].movingPlayer.identifier;
    playerData *movedPlayer;
    if (undoList[*move+1].movingPlayer.identifier == player1.identifier) {
        movedPlayer = &player1;
        (*movedPlayer).moves = undoList[*move+1].movingPlayer.moves;
        (*movedPlayer).score = undoList[*move+1].movingPlayer.score;
    }
    else if (undoList[*move+1].movingPlayer.identifier == player2.identifier) {
        movedPlayer = &player2;
        (*movedPlayer).moves = undoList[*move+1].movingPlayer.moves;
        (*movedPlayer).score = undoList[*move+1].movingPlayer.score;
    }
    *move = *move + 1;
    //print(gridarr);
}

void openMenu () {
    short int option;
    printf("Enter 1 to undo\n");
    printf("Enter 2 to redo\n");
    printf("Enter 3 to save\n");
    printf("Enter 4 to exit\n");
    scanf("%hi",&option);

    if (option == 1) {
        if (moves>0) {
            undo(&moves);
        }
    }
    else if (option == 2) {
        if (moves<lastMove) {
            redo(&moves);
        }
        /*else {
            printf("There is no move to redo");
        }*/
    }
}

void display_time(){

int minutes;
int timer;
timer=(clock()-start_time)/1000;

if(timer>59){
    minutes=timer/60;
    timer=timer%60;
    }

printf("\n\t%02d:%02d\n",minutes,timer);
}


void addMoves(playerData *player) {
    (player->moves)++;
}



int countHorizontally (_Bool counted, int i, int j)
{
    int sum = 0;
    if (j-3>=0)
    {
        if ((gridarr[i][j-3] + gridarr[i][j-2] + gridarr[i][j-1] + gridarr[i][j]) == counted * 4 )
        {
            sum++;
        }
    }
    if (j-2>=0 && j+1<7)
    {
        if ((gridarr[i][j-2] + gridarr[i][j-1] + gridarr[i][j] +  gridarr[i][j+1]) == counted * 4)
        {
            sum++;
        }
    }
    if (j-1>=0 && j+2<7)
    {
        if ((gridarr[i][j-1] + gridarr[i][j] +  gridarr[i][j+1] + gridarr[i][j+2]) == counted * 4)
        {
            sum++;
        }
    }
    if (j+3<7)
    {
        if ((gridarr[i][j] +  gridarr[i][j+1] + gridarr[i][j+2] + gridarr[i][j+3]) == counted * 4)
        {
            sum++;
        }
    }
    return sum;
}

//replace the number 9 with the hight variable of the grid
int countVertically(_Bool counted,int i, int j)
{
    if (i+3<9)
    {
        return (gridarr[i][j] + gridarr[i+1][j] + gridarr[i+2][j] + gridarr[i+3][j] == counted * 4);
    }
    else
    {
        return 0;
    }
}

int countDiagonally(_Bool counted, int i, int j)
{
    int sum = 0;
    //checks the main diagonal
    if (i-3>=0 && j+3<7)
    {
        if (gridarr[i][j] + gridarr[i-1][j+1] + gridarr[i-2][j+2] + gridarr[i-3][j+3] == counted * 4)
        {
            sum++;
        }
    }
    if (i+1<9 && i-2>=0 && j-1>=0 && j+2 <7)
    {
        if (gridarr[i+1][j-1] + gridarr[i][j] + gridarr[i-1][j+1] + gridarr[i-2][j+2] == counted * 4)
        {
            sum++;
        }
    }
    if (i-1>=0 && i+2<9 && j-2 >=0 && j+1<7)
    {
        if (gridarr[i+2][j-2] + gridarr[i+1][j-1] + gridarr[i][j] + gridarr[i-1][j+1] == counted * 4)
        {
            sum++;
        }
    }
    if (i+3 < 9 && j-3 >=0)
    {
        if (gridarr[i+3][j-3] + gridarr[i+2][j-2] + gridarr[i+1][j-1] + gridarr[i][j] == counted * 4)
        {
            sum++;
        }
    }
    //checks the other diagonal
    if (i-3>=0 && j-3>=0)
    {
        if (gridarr[i][j] + gridarr[i-1][j-1] + gridarr[i-2][j-2] + gridarr[i-3][j-3] == counted * 4)
        {
            sum++;
        }
    }
    if (i+1<9 && i-2>=0 && j+1<7 && j-2 >=0)
    {
        if (gridarr[i+1][j+1] + gridarr[i][j] + gridarr[i-1][j-1] + gridarr[i-2][j-2] == counted * 4)
        {
            sum++;
        }
    }
    if (i-1>=0 && i+2<9 && j+2<7 && j-1>=0)
    {
        if (gridarr[i+2][j+2] + gridarr[i+1][j+1] + gridarr[i][j] + gridarr[i-1][j-1] == counted * 4)
        {
            sum++;
        }
    }
    if (i+3 < 9 && j+3 < 7)
    {
        if (gridarr[i+3][j+3] + gridarr[i+2][j+2] + gridarr[i+1][j+1] + gridarr[i][j] == counted * 4)
        {
            sum++;
        }
    }
    return sum;
}

void updateScore(playerData *player, int i, int j)
{
    player->score += countHorizontally(player->identifier,i,j) + countVertically(player->identifier,i,j) + countDiagonally(player->identifier,i,j);
}



void original_grid( char gridarr[ROW][COL])
{
    int j,i;
    for(i=0; i<ROW; i++) {
        for(j=0; j<COL; j++) {
            gridarr[i][j]='-';
        }
    }
}


void print(char gridarr[ROW][COL]) {
    int j,i;

    printf("\t1\t2\t3\t4\t5\t6\t7\t\n");

    for(i=0; i<ROW; i++) {
        for(j=0; j<COL; j++) {
            if(gridarr[i][j]=='-') {
                if(i==0&&j==0) {
                    printf("\t%c\t",gridarr[i][j]);
                }
                else {
                    printf("%c\t",gridarr[i][j]);
                }
            }

            else {
                if(i==0&&j==0) {
                    printf("\t%c\t",figures[(int)gridarr[i][j]]);
                }
                else {
                    printf("%c\t",figures[(int)gridarr[i][j]]);
                }
            }
        }
        printf("\n\n\t" );
    }
    printf("Score of player 1:%d\n",player1.score);
    printf("\tmoves of player 1:%d\n",player1.moves);
    printf("\t-------------------------------------------\n");
    printf("\tScore of player 2:%d\n",player2.score);
    printf("\tmoves of player 2:%d\n",player2.moves);
    display_time();
}


void putDisk(char gridarr[ROW][COL],int j,_Bool *identify,int *moves)
{
    int i = ROW -1;
    while(1) {
        if(gridarr[i][j]=='-') {
            if(*identify==0) {
                gridarr[i][j]=0;
                updateUndoList(player1,i,j,*moves);
                updateScore(&player1,i,j);
                addMoves(&player1);
                (*moves)++;
                break;
            }

            else if(*identify==1) {
                gridarr[i][j]=1;
                updateUndoList(player2,i,j,*moves);
                updateScore(&player2,i,j);
                addMoves(&player2);
                (*moves)++;
                break;
            }
        }
        else {
            i--;
        }
    }
}

void play(char gridarr[ROW][COL],int *moves,_Bool *identify)
{
    int enteredColumn;
    //clear console and update it with previous action
    system("cls");
    print(gridarr);

    //decide which player is about to play
    *identify = ((*moves)%2);

    printf("\n\tplayer %d your turn now :\n\t",*identify+1);
    scanf("%d",&enteredColumn);
    if (enteredColumn==0) {
            openMenu();
            return;
    }
    while(!(enteredColumn>0&&enteredColumn<=COL))
    {
        printf("enter valid columns between 1:%d:\n",COL);
        scanf("%d",&enteredColumn);

    }

    while(gridarr[0][enteredColumn-1]!='-')
    {
        printf("column  is full \n please enter another column:\n");
        scanf("%d",&enteredColumn);
    }

    putDisk(gridarr,enteredColumn-1,identify,moves);
    int *lastMovePlayed = &lastMove;
    *lastMovePlayed = *moves;
}


int main()
{
    _Bool playerIdentifer=0;
    lastMove=0;
    moves=0;
    original_grid(gridarr);
    start_time=clock();
    while (1) {
        play(gridarr,&moves,&playerIdentifer);
    }


    return 0;
}

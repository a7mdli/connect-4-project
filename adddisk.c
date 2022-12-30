#include <stdio.h>
//#include "undo_redo.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "top_rank.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "parseXML.h"
#define ROW 4
#define COL 4

_Bool playerIdentifer=0;
time_t start_time;

_Bool inLoadedGame = 0;

int lastMove;
int choose;
int moves;

char figures[2] = {'x','o'};

char gridarr[ROW][COL];
int ii;
typedef struct
{
    char name[100];
    int score;
    int moves;

} winner_players ;
winner_players  *rank;

FILE *rank_file;

typedef struct
{

    char gridArr[ROW][COL];

    int score1;
    int moves1;
    int score2;
    int moves2;

} storeGrid;

storeGrid grid;

typedef struct
{

    int score;
    int moves;
    _Bool identifier;
} playerData;
typedef struct
{
    int i;
    int j;
    playerData movingPlayer;
} gameInfo;

gameInfo undoList[ROW*COL+2] = {{0,0,{0,0,0}},{0,0,{0,0,1}}};

playerData player1 = {0,0,0};
playerData player2 = {0,0,1};


void load_game()
{
    _Bool playerIdentifer=0;
    int i,j,number_game;
    long long x;
    FILE*address_file;
    address_file=fopen("st.bin","rb");


    printf("enter number game you stored:\n",number_game);

    scanf("%d",&number_game);
    while(number_game>3)
    {
        printf("number between 1:3 :\n");
        scanf("%d",&number_game);
    }

    for(i=1; i<=10; i++)
    {

        if(i==number_game)
        {
            x =sizeof(grid)*(number_game-1);
            fseek(address_file,x,SEEK_SET);
            fread(&grid, sizeof(grid), 1, address_file);
        }
    }


    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            gridarr[i][j]=grid.gridArr[i][j];
        }
    }
    player1.score=grid.score1;
    player1.moves=grid.moves1;

    player2.score=grid.score2;
    player2.moves=grid.moves2;

    if (grid.moves1<=grid.moves2) {
        moves = 0;
        lastMove = 0;
        inLoadedGame = 0;
    }
    else {
        moves = 1;
        lastMove = 1;
        inLoadedGame = 1;
    }


    undoList[0].movingPlayer = player1;
    undoList[1].movingPlayer = player2;
    undoList[2].movingPlayer = player1;

    fclose(address_file);

    system("cls");

    load_player();
}



void save_game(char gridarr[ROW][COL],playerData player1,playerData  player2)
{
    int i,j;

    FILE *address_file;

    address_file=fopen("st.bin","ab");

    if(address_file==NULL)
    {

        printf("not find file");

    }

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            grid.gridArr[i][j]=gridarr[i][j];
        }
    }
    grid.score1= player1.score;
    grid.moves1=player1.moves;

    grid.score2=player2.score;
    grid.moves2= player2.moves;


    fwrite(&grid, sizeof(grid), 1, address_file);


    fclose(address_file);

}
void chooseMenu ( int enteredColumn)
{


    if ( enteredColumn == 11)
    {
        if (!inLoadedGame) {
          if (moves>0)
            {
                undo(&moves);
            }
        }
        else {
            if (moves>1) {
                undo(&moves);
            }
        }
    }
    else if ( enteredColumn == 22)
    {
        if (moves<lastMove)
        {
            redo(&moves);
        }
    }


    else if(enteredColumn == 33)
    {

        save_game(gridarr,player1,player2);
    }
    else if(enteredColumn == 44)
    {
        main_manu();
    }

}
void printMenu()
{


    printf("Enter 1 to undo press 11\n");
    printf("Enter 2 to redo press 22\n");
    printf("Enter 3 to save press 33\n");
    printf("Enter 4 to exit prss 44\n");




}


void updateUndoList (playerData playerMoved, int i, int j, int moveNumber)
{
    undoList[moveNumber].i = i;
    undoList[moveNumber].j = j;
    undoList[moveNumber+2].movingPlayer = playerMoved;
}

void undo (int *move)
{
    gridarr[(undoList[*move-1]).i][(undoList[*move-1]).j] = '-';
    playerData *movedPlayer;
    if (undoList[*move-1].movingPlayer.identifier == player1.identifier)
    {
        movedPlayer = &player1;
        (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
        (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;
    }
    else if (undoList[*move-1].movingPlayer.identifier == player2.identifier)
    {
        movedPlayer = &player2;
        (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
        (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;
    }
    *move=*move - 1;
}

void redo (int *move)
{
    gridarr[undoList[*move].i][undoList[*move].j] = undoList[*move].movingPlayer.identifier;
    playerData *movedPlayer;
    if (undoList[*move].movingPlayer.identifier == player1.identifier)
    {
        movedPlayer = &player1;
        (*movedPlayer).moves = undoList[*move+2].movingPlayer.moves;
        (*movedPlayer).score = undoList[*move+2].movingPlayer.score;
    }
    else if (undoList[*move].movingPlayer.identifier == player2.identifier)
    {
        movedPlayer = &player2;
        (*movedPlayer).moves = undoList[*move+2].movingPlayer.moves;
        (*movedPlayer).score = undoList[*move+2].movingPlayer.score;
    }
    *move = *move + 1;
}



void display_time()
{

    int minutes;
    int timer;
    timer=(clock()-start_time)/1000;

    if(timer>59)
    {
        minutes=timer/60;
        timer=timer%60;
    }

    printf("\n\t%02d:%02d\n",minutes,timer);
}


void addMoves(playerData *player)
{
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
    if (j-2>=0 && j+1<COL)
    {
        if ((gridarr[i][j-2] + gridarr[i][j-1] + gridarr[i][j] +  gridarr[i][j+1]) == counted * 4)
        {
            sum++;
        }
    }
    if (j-1>=0 && j+2<COL)
    {
        if ((gridarr[i][j-1] + gridarr[i][j] +  gridarr[i][j+1] + gridarr[i][j+2]) == counted * 4)
        {
            sum++;
        }
    }
    if (j+3<COL)
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
    if (i+3<ROW)
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
    if (i-3>=0 && j+3<COL)
    {
        if (gridarr[i][j] + gridarr[i-1][j+1] + gridarr[i-2][j+2] + gridarr[i-3][j+3] == counted * 4)
        {
            sum++;
        }
    }
    if (i+1<ROW && i-2>=0 && j-1>=0 && j+2 <COL)
    {
        if (gridarr[i+1][j-1] + gridarr[i][j] + gridarr[i-1][j+1] + gridarr[i-2][j+2] == counted * 4)
        {
            sum++;
        }
    }
    if (i-1>=0 && i+2<ROW && j-2 >=0 && j+1<COL)
    {
        if (gridarr[i+2][j-2] + gridarr[i+1][j-1] + gridarr[i][j] + gridarr[i-1][j+1] == counted * 4)
        {
            sum++;
        }
    }
    if (i+3 < ROW && j-3 >=0)
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
    if (i+1<ROW && i-2>=0 && j+1<COL && j-2 >=0)
    {
        if (gridarr[i+1][j+1] + gridarr[i][j] + gridarr[i-1][j-1] + gridarr[i-2][j-2] == counted * 4)
        {
            sum++;
        }
    }
    if (i-1>=0 && i+2<ROW && j+2<COL && j-1>=0)
    {
        if (gridarr[i+2][j+2] + gridarr[i+1][j+1] + gridarr[i][j] + gridarr[i-1][j-1] == counted * 4)
        {
            sum++;
        }
    }
    if (i+3 < ROW && j+3 < COL)
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
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            gridarr[i][j]='-';
        }
    }
}


void print(char gridarr[ROW][COL])
{
    int j,i;
    for(i=1; i<=COL; i++)
    {

        printf("\t%d",i);
    }
    printf("\n" );


    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            if(gridarr[i][j]=='-')
            {
                if(i==0&&j==0)
                {
                    printf("\t%c\t",gridarr[i][j]);
                }
                else
                {
                    printf("%c\t",gridarr[i][j]);
                }
            }

            else
            {
                if(i==0&&j==0)
                {
                    printf("\t%c\t",figures[(int)gridarr[i][j]]);
                }
                else
                {
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
    printMenu();
}


void putDisk(char gridarr[ROW][COL],int j,_Bool *identify,int *moves)
{
    int i = ROW -1;
    while(1)
    {
        if(gridarr[i][j]=='-')
        {
            if(*identify==0)
            {
                gridarr[i][j]=0;
                updateScore(&player1,i,j);
                addMoves(&player1);
                updateUndoList(player1,i,j,*moves);
                (*moves)++;
                break;
            }

            else if(*identify==1)
            {
                gridarr[i][j]=1;
                updateScore(&player2,i,j);
                addMoves(&player2);
                updateUndoList(player2,i,j,*moves);
                (*moves)++;
                break;
            }
        }
        else
        {
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

    if ((enteredColumn==11)||(enteredColumn==22)||(enteredColumn==33)||(enteredColumn==44))
    {
        chooseMenu(enteredColumn);
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
void new_game()
{
    lastMove=0;
    moves=0;
    original_grid(gridarr);
    player1.moves = 0;
    player1.score = 0;
    player2.moves = 0;
    player2.score = 0;

    play(gridarr,&moves,&playerIdentifer);
}
void load_player( )
{

    while(1)
    {

        if((player1.moves+player2.moves)==(COL*ROW))
        {
            system("cls");
            print(gridarr);
            printf("game end\n");
            //deleted xx = 1 and replaced first parameter with 1 instead of xx
            top_rank(1,player1.score,player2.score);
            printf("    1->main.\n");
            printf("    2->exit.\n");
            scanf("%d",&choose);

            if(choose==1)
            {
                main_manu();
            }
            else if(choose==2)
            {
                return;
            }
        }
        play(gridarr,&moves,&playerIdentifer);
    }

}
void main_manu()
{

    char choose_manu;

    printf("-------------------------MAIN MANU--------------------------\n");
    printf("    1->start a new game.\n");

    printf("    2->load a game last games.\n");
    printf("    3->Top players.\n");
    printf("    4->Quit\n");
    fscanf(stdin, " ");
    scanf("%c",&choose_manu);
    while((choose_manu!=49)&&(choose_manu!=50)&&(choose_manu!=51)&&(choose_manu!=52))
    {

        printf("please enter number between 1:4\n");
        fscanf(stdin, " ");
        scanf("%c",&choose_manu);

    }
    if(choose_manu==49)
    {
        inLoadedGame = 0;
        new_game();
        load_player( );

    }
    if(choose_manu==50)
    {

        load_game();

    }
    if(choose_manu==51)
    {
        int xx=0;
        top_rank(xx,player1.score,player2.score);

    }
    if(choose_manu==52)
    {
        exit(0);
    }




}
int main()
{

    lastMove=0;
    moves=0;
    original_grid(gridarr);
    start_time=clock();

    main_manu();

    return 0;
}


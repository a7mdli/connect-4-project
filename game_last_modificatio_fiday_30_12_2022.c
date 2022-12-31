int ii;
typedef struct
{
    char name[100];
    int score;
    int moves;

} winner_players ;
winner_players  *rank;


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

playerData player1 = {0,0,0};
playerData player2 = {0,0,1};

int lastMove;
int choose;
int moves;
_Bool inLoadedGame = 0;


#include <stdio.h>
FILE *rank_file;
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
#include "load_save.h"
//#define ROW 4
//#define COL 4

_Bool playerIdentifer=0;
time_t start_time;




char figures[2] = {'x','o'};




void updateUndoList (int ROW,int COL,char gridarr[ROW][COL],playerData playerMoved, int i, int j, int moveNumber,gameInfo undoList[])
{
    undoList[moveNumber].i = i;
    undoList[moveNumber].j = j;
    undoList[moveNumber+2].movingPlayer = playerMoved;
}

void undo (int ROW, int COL, char gridarr[ROW][COL],int *move, gameInfo undoList[])
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

void redo (int ROW,int COL,char gridarr[ROW][COL],int *move, gameInfo undoList[])
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



int countHorizontally (int ROW,int COL,char gridarr[ROW][COL],_Bool counted, int i, int j)
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
int countVertically(int ROW,int COL,char gridarr[ROW][COL],_Bool counted,int i, int j)
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

int countDiagonally(int ROW,int COL,char gridarr[ROW][COL],_Bool counted, int i, int j)
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

void updateScore(int ROW,int COL,char gridarr[ROW][COL],playerData *player, int i, int j)
{
    player->score += countHorizontally(ROW,COL,gridarr,player->identifier,i,j) + countVertically(ROW,COL,gridarr,player->identifier,i,j) + countDiagonally(ROW,COL,gridarr,player->identifier,i,j);
}



void original_grid(int ROW,int COL, char gridarr[ROW][COL])
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


void print(int ROW,int COL,char gridarr[ROW][COL])
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
    printf("\tGAME MANU\n");
    display_time();

}
void chooseMenu ( int ROW,int COL,char gridarr[ROW][COL],int enteredColumn,gameInfo undoList[])
{
    char  usrx;
     printMenu();
     fscanf(stdin," ");
     scanf("%c",&usrx);
     while((usrx!='u')&&(usrx!='r')&&(usrx!='s')&&(usrx!='x')){
        printf("---->enter valid charachter\n");
           scanf("%c",&usrx);
     }

    if ( usrx== 'u')
    {
        if (!inLoadedGame) {
          if (moves>0)
            {
                undo(ROW,COL,gridarr,&moves,undoList);
            }
        }
        else {
            if (moves>1) {
                undo(ROW,COL,gridarr,&moves,undoList);
            }
        }
    }
    else if ( usrx == 'r')
    {
        if (moves<lastMove)
        {
            redo(ROW,COL,gridarr,&moves,undoList);
        }
    }


    else if(usrx == 's')
    {

        save_game(ROW,COL,gridarr,player1,player2,undoList);
    }
    else if( usrx == 'x')
    {
        main_manu(ROW,COL,gridarr);
    }

}
void printMenu()
{
    printf("Enter 1 to undo press u\n");
    printf("Enter 2 to redo press r\n");
    printf("Enter 3 to save press s\n");
    printf("Enter 4 to exit prss x\n");
}


void putDisk(int ROW,int COL,char gridarr[ROW][COL],int j,_Bool *identify,int *moves, gameInfo undoList[])
{
    int i = ROW -1;
    while(1)
    {
        if(gridarr[i][j]=='-')
        {
            if(*identify==0)
            {
                gridarr[i][j]=0;
                updateScore(ROW, COL,gridarr,&player1,i,j);
                addMoves(&player1);
                updateUndoList( ROW, COL,gridarr,player1,i,j,*moves,undoList);
                (*moves)++;
                break;
            }

            else if(*identify==1)
            {
                gridarr[i][j]=1;
                updateScore(ROW, COL,gridarr,&player2,i,j);
                addMoves(&player2);
                updateUndoList(ROW, COL,gridarr,player2,i,j,*moves,undoList);
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

void play(int ROW,int COL,char gridarr[ROW][COL],int *moves,_Bool *identify, gameInfo undoList[])
{
    int check_char;
    int enteredColumn;
    //clear console and update it with previous action
    system("cls");
    print(ROW, COL,gridarr);

    //decide which player is about to play
    *identify = ((*moves)%2);

    printf("\n\tplayer %d your turn now :\n\t",*identify+1);
   while(1)
    {
        beging:

         check_char=scanf("%d",&enteredColumn);
         if(check_char!=1){
         gets(&enteredColumn);

          printf("enter valid columns between 0:%d:\n",COL);


         }

         else if(!(enteredColumn>=0&&enteredColumn<=COL)){
            printf("enter valid columns between 0:%d:\n",COL);
            goto beging;

         }
         else{

            break;
         }


    }

    if (enteredColumn==0)
    {
        chooseMenu(ROW,COL,gridarr,enteredColumn,undoList);
        return;
    }

    while(gridarr[0][enteredColumn-1]!='-')
    {
        printf("column  is full \n please enter another column:\n");
        scanf("%d",&enteredColumn);
    }

    putDisk(ROW, COL,gridarr,enteredColumn-1,identify,moves,undoList);

    int *lastMovePlayed = &lastMove;
    *lastMovePlayed = *moves;
}
void new_game(int ROW,int COL,char gridarr[ROW][COL],gameInfo undoList[])
{
    lastMove=0;
    moves=0;
    original_grid(ROW, COL,gridarr);
    player1.moves = 0;
    player1.score = 0;
    player2.moves = 0;
    player2.score = 0;

    play(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);
}
void load_player(int ROW,int COL,char gridarr[ROW][COL], gameInfo undoList[],int high_score)
{
int check_char;
    while(1)
    {

        if((player1.moves+player2.moves)==(COL*ROW))
        {
            system("cls");
            print(ROW, COL,gridarr);
            printf("    game end\n");
            //deleted xx = 1 and replaced first parameter with 1 instead of xx
            top_rank(1,player1.score,player2.score,high_score);
            printf("    1->main.\n");
            printf("    2->exit.\n");
              while(1)
    {
        beging:

         check_char=scanf("%d",&choose);
         if(check_char!=1){
         gets(&choose);

          printf("enter valid columns between 1:2:\n");


         }

         else if(!(choose>0&&choose<=2)){
            printf("enter valid columns between 1:2:\n");
            goto beging;

         }
         else{

            break;
         }


    }

            if(choose==1)
            {
                main_manu(ROW,COL,gridarr);
                return;
            }
            else if(choose==2)
            {
                return;
            }
        }
        play(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);
    }

}
void main_manu(int ROW,int COL,char gridarr[ROW][COL],int high_score)
{
    int check_char;
    int return_value;
    gameInfo undoList[ROW*COL+2]; //= {{0,0,{0,0,0}},{0,0,{0,0,1}}};
    //initializing undo list
    undoList[0].i=0;
    undoList[0].j=0;
    undoList[0].movingPlayer.identifier=0;
    undoList[0].movingPlayer.moves=0;
    undoList[0].movingPlayer.score=0;
    undoList[1].i=0;
    undoList[1].j=0;
    undoList[1].movingPlayer.identifier=1;
    undoList[1].movingPlayer.moves=0;
    undoList[1].movingPlayer.score=0;

    char choose_manu;

    printf("-------------------------MAIN MANU--------------------------\n");
    printf("    1->start a new game.\n");
    printf("    2->load a game last games.\n");
    printf("    3->Top players.\n");
    printf("    4->Quit\n");
    fscanf(stdin, " ");
    scanf("%d",&choose_manu);
    while((choose_manu!=1)&&(choose_manu!=2)&&(choose_manu!=3)&&(choose_manu!=4))
    {

        printf("please enter number between 1:4\n");
              while(1)
    {
        beging:

         check_char=scanf("%d",&choose_manu);
         if(check_char!=1){
         gets(&choose_manu);

          printf("--->enter number between 1:4 :\n");


         }

         else if(!(choose_manu>0&&choose_manu<=4)){
            printf("---->enter  number between 1:4\n",COL);
            goto beging;

         }
         else{

            break;
         }


    }


    }
    if(choose_manu==1)
    {
        inLoadedGame = 0;
        new_game(ROW,COL,gridarr,undoList);
        load_player(ROW,COL,gridarr,undoList,high_score);

    }
    if(choose_manu==2)
    {


        return_value=load_game(ROW,COL,gridarr,undoList);
       if(return_value==0){

        load_player(ROW,COL,gridarr,undoList,high_score);


        return;
         }
        if(return_value==1){

             main_manu(ROW,COL,gridarr,high_score);
            return;
        }


    }
    if(choose_manu==3)
    {


        top_rank(0,player1.score,player2.score,high_score);
        printf("    1->main.\n");
        printf("    2->exit.\n");
        scanf("%d",&choose);
         if(choose==1)
            {
                main_manu(ROW,COL,gridarr,high_score);
                return;
            }
            else if(choose==2)
            {

                return;
            }


    }
    if(choose_manu==4)
    {
        exit(0);
    }

  return;


}
int main()
{

    int ROW=9,COL=7,highScores=10;
    char gridArr[ROW][COL];
    char configFilePath[1000] = "configure.xml";

    for (int i=0; i<3; i++) {
        _Bool recieved = readParametars(&COL,&ROW,&highScores,configFilePath);
        if (recieved) break;
        else {
            printf("Configuration file is corrupted or doesn't exist, please enter a path for a valid file\n");
            gets(configFilePath);
        }
    }

    lastMove=0;
    moves=0;
    original_grid(ROW,COL,gridArr);
    start_time=clock();

    main_manu(ROW,COL,gridArr,highScores);

    return 0;
}

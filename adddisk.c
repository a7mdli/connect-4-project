#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <time.h>
#include <conio.h>
#define ROW 9
#define COL 7
time_t start_time;

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

void display_time(){


int count,minutes;

int timer;



timer=(clock()-start_time)/1000;
if(timer>59){


    minutes=timer/60;
    timer=timer%60;


}
printf("\n\t%02d:%02ld\n",minutes,timer);



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
    int j,i,symbol;

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {

            gridarr[i][j]='-';

        }

    }



}
void print(char gridarr[ROW][COL],int* identify)
{

    int j,i,symbol;

    printf("\t1\t2\t3\t4\t5\t6\t7\t8\t9\t\n");


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
                    printf("\t%c\t",figures[gridarr[i][j]]);
                }
                else
                {
                    printf("%c\t",figures[gridarr[i][j]]);
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

void putDisk(char gridarr[ROW][COL],int i,int j,int *identify,int *moves)
{

    while(1)
    {




        if(gridarr[i][j]=='-')
        {
            if(*identify==1)
            {
                gridarr[i][j]=0;
                updateScore(&player1,i,j);
                addMoves(&player1);
                (*moves)++;
                break;

            }
            else if(*identify==2)
            {

                gridarr[i][j]=1;
                updateScore(&player2,i,j);
                addMoves(&player2);
                (*moves)++;
                break;
            }

        }
        else
        {

            i--;

        }
    }

    play(gridarr,moves,identify);

    //system("cls");


}

void play(char gridarr[ROW][COL],int *moves,int *identify)
{
    int j,i,symbol,score;
    system("cls");

    print(gridarr,identify);

    if(*moves%2==0)
    {

        *identify=1;

    }
    else if(*moves%2==1)
    {
        *identify=2;
    }
    printf("\n\tplayer %d your turn now :\n\t",*identify);
    scanf("%d",&symbol);
    while(gridarr[0][symbol-1]!='-')
    {

        printf("column  is full \n please enter another column:\n");

        scanf("%d",&symbol);

    }


    while(!(symbol>0&&symbol<=COL))
    {

        printf("enter valid columns between 1:%d:\n",COL);

        scanf("%d",&symbol);





    }


    i=ROW-1;
    j=symbol-1;
    putDisk(gridarr,i,j,identify,moves);


}


int main()
{
    int j,i,symbol;
    int identif=0,playe=0;
    int *moves=playe;
    int *identify=identif;


    // char symbol;


    original_grid(gridarr);

       start_time=clock();
    play(gridarr,&playe,&identif);




    return 0;
}



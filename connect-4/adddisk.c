#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <time.h>
#include <conio.h>
#define ROW 7
#define COL 9

char figures[2] = {'x','o'};

void store_underscore( char gridarr[ROW][COL]){
 int jj,ii,symbol;

 for(ii=0; ii<ROW; ii++)
    {
        for(jj=0; jj<COL; jj++)
        {

            gridarr[ii][jj]='-';

        }

    }



}
void print(char gridarr[ROW][COL])
{

    int jj,ii,symbol;

    printf("\t1\t2\t3\t4\t5\t6\t7\t8\t9\t\n");


    for(ii=0; ii<ROW; ii++)
    {
        for(jj=0; jj<COL; jj++)
        {

            if(gridarr[ii][jj]=='-')
            {

                if(ii==0&&jj==0)
                {
                    printf("\t%c\t",gridarr[ii][jj]);
                }
                else
                {
                    printf("%c\t",gridarr[ii][jj]);
                }

            }




            else
            {
                if(ii==0&&jj==0)
                {
                    printf("\t%c\t",figures[gridarr[ii][jj]]);
                }
                else
                {
                    printf("%c\t",figures[gridarr[ii][jj]]);
                }


            }

        }
        printf("\n\n\t" );
    }







}

void putDisk(char gridarr[ROW][COL],int ii,int jj,int *identify,int *moves)
{

    while(1)
    {




        if(gridarr[ii][jj]=='-')
        {
            if(*identify==1)
            {
                gridarr[ii][jj]=0;
                 (*moves)++;
                break;

            }
            else if(*identify==2)
            {

                gridarr[ii][jj]=1;
                (*moves)++;
                break;
            }

        }
        else
        {

            ii--;

        }
    }
    play(gridarr,moves,identify);

    //system("cls");


}

void play(char gridarr[ROW][COL],int *moves,int *identify)
{
    int jj,ii,symbol;
    system("cls");
    print(gridarr);

    if(*moves%2==0)
    {

        *identify=1;

    }
    else if(*moves%2==1)
    {
        *identify=2;
    }
    printf("\n moves %d your turn now :\n",*identify);
    scanf("%d",&symbol);
    while(gridarr[0][symbol-1]!='-')
    {

        printf("column is full \n please enter another column:\n",COL);

        scanf("%d",&symbol);

    }


    while(!(symbol>0&&symbol<=COL))
    {

        printf("enter valid columns between 1:%d:\n",COL);

        scanf("%d",&symbol);





    }


    ii=ROW-1;
    jj=symbol-1;
    putDisk(gridarr,ii,jj,identify,moves);


}


int main()
{
    int jj,ii,symbol;
    int identif=0,playe=0;
    int *moves=playe;
    int *identify=identif;


    // char symbol;
    char gridarr[ROW][COL];

store_underscore(gridarr);

    play(gridarr,&playe,&identif);




    return 0;
}



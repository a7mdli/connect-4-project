void playComputerMode(int ROW,int COL,char gridarr[ROW][COL],int *moves,_Bool *identify, gameInfo undoList[])
{
    int enteredColumn;
    //clear console and update it with previous action
    system("cls");
    print(ROW, COL,gridarr);

    //decide which player is about to play
    *identify = ((*moves)%2);

    if (*identify==0) {
        printf("\n\tyour turn now :\n\t");
        scanf("%d",&enteredColumn);
    }

    else {
        srand(time(0));
        enteredColumn = (rand()%COL+1);
        if (gridarr[0][enteredColumn-1]!='-') {
            int i = 0;
            while (gridarr[0][(i+enteredColumn-1)%COL]!='-') i++;
            enteredColumn += i;
        }
    }

    if ((enteredColumn==11)||(enteredColumn==22)||(enteredColumn==33)||(enteredColumn==44))
    {
        chooseMenu(ROW,COL,gridarr,enteredColumn,undoList);
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

    putDisk(ROW, COL,gridarr,enteredColumn-1,identify,moves,undoList);
    int *lastMovePlayed = &lastMove;
    *lastMovePlayed = *moves;
}

void undoComputerMode (int ROW, int COL, char gridarr[ROW][COL],int *move, gameInfo undoList[]) {
    gridarr[(undoList[*move-1]).i][(undoList[*move-1]).j] = '-';
    gridarr[(undoList[*move-2]).i][(undoList[*move-2]).j] = '-';
    playerData *movedPlayer;

    movedPlayer = &player1;
    (*movedPlayer).moves = undoList[(*move)-2].movingPlayer.moves;
    (*movedPlayer).score = undoList[(*move)-2].movingPlayer.score;

    movedPlayer = &player2;
    (*movedPlayer).moves = undoList[(*move)-1].movingPlayer.moves;
    (*movedPlayer).score = undoList[(*move)-1].movingPlayer.score;

    *move=*move - 2;
}

void redoComputerMode (int ROW, int COL, char gridarr[ROW][COL],int *move, gameInfo undoList[]) {
    gridarr[undoList[*move].i][undoList[*move].j] = undoList[*move].movingPlayer.identifier;
    gridarr[undoList[*move+1].i][undoList[*move+1].j] = undoList[*move+1].movingPlayer.identifier;
    playerData *movedPlayer;

    movedPlayer = &player1;
    (*movedPlayer).moves = undoList[*move+2].movingPlayer.moves;
    (*movedPlayer).score = undoList[*move+2].movingPlayer.score;

    movedPlayer = &player2;
    (*movedPlayer).moves = undoList[*move+3].movingPlayer.moves;
    (*movedPlayer).score = undoList[*move+3].movingPlayer.score;

    *move = *move + 2;
}

void new_game_vs_computer(int ROW,int COL,char gridarr[ROW][COL],gameInfo undoList[])
{
    lastMove=0;
    moves=0;
    original_grid(ROW, COL,gridarr);
    player1.moves = 0;
    player1.score = 0;
    player2.moves = 0;
    player2.score = 0;

    playComputerMode(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);                     //here
}
void load_player_computer_mode(int ROW,int COL,char gridarr[ROW][COL], gameInfo undoList[])
{

    while(1)
    {

        if((player1.moves+player2.moves)==(COL*ROW))
        {
            system("cls");
            print(ROW, COL,gridarr);
            printf("game end\n");
            //deleted xx = 1 and replaced first parameter with 1 instead of xx
            top_rank(1,player1.score,player2.score);
            printf("    1->main.\n");
            printf("    2->exit.\n");
            scanf("%d",&choose);

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
        playComputerMode(ROW,COL,gridarr,&moves,&playerIdentifer,undoList);
    }

}

char mainGrid[9][7]=
{
    {' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' '},
    {0,' ',' ',' ',' ',' ',0},
    {' ',0,' ',' ',' ',0,' '},
    {' ',' ',0,' ',0,' ',' '},
    {' ',0,0,0,0,' ',' '},
    {' ',' ',' ',0,' ',' ',' '},
    {' ',' ',' ',0,' ',' ',' '},
    {1,1,1,0,0,0,0}
};

typedef struct {
    char name[9];
    int score;
    int moves;
    _Bool identifier;
}playerData;

//initialized after game mode selection:
/*playerData player1 = {"player 1", 0, 0, 0};
playerData player2 = {"player 2", 0, 0, 1};*/

//replace the number 7 with the width variable of the grid
int countHorizontally (_Bool counted, int i, int j) {
    int sum = 0;
    if (j-3>=0) {
        if ((mainGrid[i][j-3] + mainGrid[i][j-2] + mainGrid[i][j-1] + mainGrid[i][j]) == counted * 4 ) {
            sum++;
        }
    }
    if (j-2>=0 && j+1<7) {
        if ((mainGrid[i][j-2] + mainGrid[i][j-1] + mainGrid[i][j] +  mainGrid[i][j+1]) == counted * 4) {
            sum++;
        }
    }
    if (j-1>=0 && j+2<7) {
        if ((mainGrid[i][j-1] + mainGrid[i][j] +  mainGrid[i][j+1] + mainGrid[i][j+2]) == counted * 4) {
            sum++;
        }
    }
    if (j+3<7) {
        if ((mainGrid[i][j] +  mainGrid[i][j+1] + mainGrid[i][j+2] + mainGrid[i][j+3]) == counted * 4) {
            sum++;
        }
    }
    return sum;
}

//replace the number 9 with the hight variable of the grid
int countVertically(_Bool counted ,int i, int j) {
    if (i+3<9) {
        return (mainGrid[i][j] + mainGrid[i+1][j] + mainGrid[i+2][j] + mainGrid[i+3][j] == counted * 4);
    }
    else {
        return 0;
    }
}

int countDiagonally(_Bool counted, int i, int j) {
    int sum = 0;
    //checks the main diagonal
    if (i-3>=0 && j+3<7) {
        if (mainGrid[i][j] + mainGrid[i-1][j+1] + mainGrid[i-2][j+2] + mainGrid[i-3][j+3] == counted * 4) {
            sum++;
        }
    }
    if (i+1<9 && i-2>=0 && j-1>=0 && j+2 <7) {
        if (mainGrid[i+1][j-1] + mainGrid[i][j] + mainGrid[i-1][j+1] + mainGrid[i-2][j+2] == counted * 4) {
            sum++;
        }
    }
    if (i-1>=0 && i+2<9 && j-2 >=0 && j+1<7) {
        if (mainGrid[i+2][j-2] + mainGrid[i+1][j-1] + mainGrid[i][j] + mainGrid[i-1][j+1] == counted * 4) {
            sum++;
        }
    }
    if (i+3 < 9 && j-3 >=0) {
        if (mainGrid[i+3][j-3] + mainGrid[i+2][j-2] + mainGrid[i+1][j-1] + mainGrid[i][j] == counted * 4) {
            sum++;
        }
    }
    //checks the other diagonal
    if (i-3>=0 && j-3>=0) {
        if (mainGrid[i][j] + mainGrid[i-1][j-1] + mainGrid[i-2][j-2] + mainGrid[i-3][j-3] == counted * 4) {
            sum++;
        }
    }
    if (i+1<9 && i-2>=0 && j+1<7 && j-2 >=0) {
        if (mainGrid[i+1][j+1] + mainGrid[i][j] + mainGrid[i-1][j-1] + mainGrid[i-2][j-2] == counted * 4) {
            sum++;
        }
    }
    if (i-1>=0 && i+2<9 && j+2<7 && j-1>=0) {
        if (mainGrid[i+2][j+2] + mainGrid[i+1][j+1] + mainGrid[i][j] + mainGrid[i-1][j-1] == counted * 4) {
            sum++;
        }
    }
    if (i+3 < 9 && j+3 < 7) {
        if (mainGrid[i+3][j+3] + mainGrid[i+2][j+2] + mainGrid[i+1][j+1] + mainGrid[i][j] == counted * 4) {
            sum++;
        }
    }
    return sum;
}

void updateScore(playerData *player, int i, int j) {
    player->score += countHorizontally(player->identifier,i,j) + countVertically(player->identifier,i,j) + countDiagonally(player->identifier,i,j);
}

void addMoves(playerData *player) {
    (player->moves)++;
}


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#define ROW 3
#define COLUMN 3
#define COMPUTER 0
#define COMPUTERMOVE 'X'
#define PLAYERONE 1
#define PLAYERONEMOVE 'O'
#define PLAYERTWO 2
#define PLAYERTWOMOVE 'X'

void Display();
void Rules();
void OriginalTable();
void UpdatedTable(char table[][COLUMN]);
bool InRow(char table[][COLUMN]);
bool InColumn(char table[][COLUMN]);
bool Diagonally(char table[][COLUMN]);
bool GameEnd(char table[][COLUMN]);
void OnePlayer(char table[][COLUMN], char player1[]);
void TwoPlayer(char table[][COLUMN], char player1[], char player2[]);

int main(){
    char choice;
    char table[ROW][COLUMN]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char player1[50], player2[50];

    Rules();
    Display();

    do{
        choice=toupper(getch());
        switch(choice){
        case 'S':
            OriginalTable();
            printf("\nEnter your name : ");
            scanf("%s", player1);
            OnePlayer(table,player1);
            break;
        case 'P':
            OriginalTable();
            printf("\nEnter name of player 1 : ");
            scanf("%s", player1);
            printf("\nEnter name of player 2 : ");
            scanf("%s", player2);
            TwoPlayer(table,player1,player2);
            break;
        case 'Q':
            printf("\n\n\t\tYou ended the game\n");
            break;
        }
    } while(choice!='S' && choice!='P' && choice!='Q');


    return 0;
}

void Display(){
    printf("\n\n\t\t\t  Tic-Tac-Toe  ");
    printf("\n\t\t_________________________");
    printf("\n\t\t <S> Start 1 player game");
    printf("\n\t\t <P> Start 2 player game");
    printf("\n\t\t <Q> Quit the game");
    printf("\n\t\t Press any key : ");
}

void Rules(){
    printf("\n\n\t\t\t Rules for Tic-Tac-Toe ");
    printf("\n\t 1 - The game is played on a grid that's 3 squares by 3 squares");
    printf("\n\t 2 - You are X, your friend/computer is O. Players take turns putting their marks in empty squares");
    printf("\n\t 3 - The first player to get 3 marks in a row (up, down, across, or diagonally) is the winner");
    printf("\n\t 4 - When all 9 squares are full. the game is over. If no player has 3 marks in a row, the game ends in a tie\n");
}

void OriginalTable(){
    system("cls");
    printf("\n\n\t\tCells are marked from 1 to 9 as shown \n\n");

    printf("\t\t\t  0 |  1  | 2  \n");
    printf("\t\t\t---------------\n");
    printf("\t\t\t  3 |  4  | 5  \n");
    printf("\t\t\t---------------\n");
    printf("\t\t\t  6 |  7  | 8  \n");

    printf("\n\n\t\tPlayers should enter the number of the cell\n");
}

void UpdatedTable(char table[][COLUMN]){

    printf("\n\n\t\t\t  %c |  %c  | %c  \n", table[0][0], table[0][1], table[0][2]);
    printf("\t\t\t---------------\n");
    printf("\t\t\t  %c |  %c  | %c  \n", table[1][0], table[1][1], table[1][2]);
    printf("\t\t\t---------------\n");
    printf("\t\t\t  %c |  %c  | %c  \n", table[2][0], table[2][1], table[2][2]);
}

bool InRow(char table[][COLUMN]) {
    int i;
    for(i=0; i<ROW; i++)
        if(table[i][0]!=' ' && table[i][0]==table[i][1] && table[i][1]==table[i][2])
            return 1;
    return 0;
}

bool InColumn(char table[][COLUMN]){
    int i;
    for(i=0; i<COLUMN; i++)
        if(table[0][i]!=' ' && table[0][i]==table[1][i] && table[1][i]==table[2][i])
            return 1;
    return 0;
}

bool Diagonally(char table[][COLUMN]){
    if(table[0][0]!=' ' && table[0][0]==table[1][1] && table[1][1]==table[2][2])
        return 1;
    if(table[0][2]!=' ' && table[0][2]==table[1][1] && table[1][1]==table[2][0])
        return 1;
    return 0;
}

bool GameEnd(char table[][COLUMN]){
    return(InRow(table) || InColumn(table) || Diagonally(table));
}

void OnePlayer(char table[][COLUMN], char player1[]){
    int moveNum=0, r=0,c=0;
    int cell[ROW*COLUMN];
    int turn=COMPUTER;

    printf("\nComputer starts the game\n\n");

    while(GameEnd(table)==0 && moveNum!=ROW*COLUMN){
        if(turn==COMPUTER){
            srand(time(NULL));
            int cellNum=rand()%9;
            r=cellNum/ROW;
            c=cellNum%COLUMN;
            while(table[r][c]!=' '){
                cellNum=rand()%9;
                r=cellNum/ROW;
                c=cellNum%COLUMN;
            }
            table[r][c]=COMPUTERMOVE;
            OriginalTable();
            UpdatedTable(table);
            printf("\nComputer put %c in the cell %d\n", COMPUTERMOVE,cellNum);
            if(GameEnd(table)==1 && moveNum!=ROW*COLUMN){
                printf("\n\t\tComputer is the winner!\n");
                return;
            }
            moveNum++;
            turn=PLAYERONE;
        }

        if(turn==PLAYERONE && moveNum!=ROW*COLUMN){
            int cellNum1;
            printf("\n%s, where do you want to place %c ? : ", player1, PLAYERONEMOVE);
            scanf("%d", &cellNum1);
            r=cellNum1/ROW;
            c=cellNum1%COLUMN;
            while(cellNum1<0 || cellNum1>8 || table[r][c]!=' '){
                printf("\nInvalid input, enter again : ");
                scanf("%d", &cellNum1);
                r=cellNum1/ROW;
                c=cellNum1%COLUMN;
            }
            r=cellNum1/ROW;
            c=cellNum1%COLUMN;
            table[r][c]=PLAYERONEMOVE;
            OriginalTable();
            UpdatedTable(table);
            printf("\n%s put %c in the cell %d\n", player1, PLAYERONEMOVE,cellNum1);
            if(GameEnd(table)==1 && moveNum!=ROW*COLUMN){
                printf("\n\t\t%s is the winner!\n", player1);
                return;
            }
            moveNum++;
            turn=COMPUTER;
        }
    }
        if(GameEnd(table)==0 && moveNum==ROW*COLUMN)
        printf("\n\t\tIt is a draw!\n");



}

void TwoPlayer(char table[][COLUMN], char player1[], char player2[]){
    int moveNum=0, r=0,c=0;
    int cell[ROW*COLUMN];
    int turn=PLAYERONE;

    printf("\n%s starts the game\n\n", player1);

    while(GameEnd(table)==0 && moveNum!=ROW*COLUMN){
        if(turn==PLAYERONE){
            int cellNum1;
            printf("\n%s, where do you want to place %c ? : ", player1, PLAYERONEMOVE);
            scanf("%d", &cellNum1);
            r=cellNum1/ROW;
            c=cellNum1%COLUMN;
            while(cellNum1<0 || cellNum1>8 || table[r][c]!=' '){
                printf("\nInvalid input, enter again : ");
                scanf("%d", &cellNum1);
                r=cellNum1/ROW;
                c=cellNum1%COLUMN;
            }
            r=cellNum1/ROW;
            c=cellNum1%COLUMN;
            table[r][c]=PLAYERONEMOVE;
            OriginalTable();
            UpdatedTable(table);
            printf("\n%s put %c in the cell %d\n", player1, PLAYERONEMOVE,cellNum1);
            if(GameEnd(table)==1 && moveNum!=ROW*COLUMN){
                printf("\n\t\t%s is the winner!\n", player1);
                return;
            }
            moveNum++;
            turn=PLAYERTWO;
        }

        if(turn==PLAYERTWO && moveNum!=ROW*COLUMN){
            int cellNum2;
            printf("\n%s, Where do you want to place %c ? : ", player2, PLAYERTWOMOVE);
            scanf("%d", &cellNum2);
            r=cellNum2/ROW;
            c=cellNum2%COLUMN;
            while(cellNum2<0 || cellNum2>8 || table[r][c]!=' '){
                printf("\nInvalid input, enter again : ");
                scanf("%d", &cellNum2);
                r=cellNum2/ROW;
                c=cellNum2%COLUMN;
            }
            r=cellNum2/ROW;
            c=cellNum2%COLUMN;
            table[r][c]=PLAYERTWOMOVE;
            OriginalTable();
            UpdatedTable(table);
            printf("\n%s put %c in the cell %d\n", player2, PLAYERTWOMOVE,cellNum2);
            if(GameEnd(table)==1 && moveNum!=ROW*COLUMN){
                printf("\n\t\t%s is the winner!\n", player2);
                return;
            }
            moveNum++;
            turn=PLAYERONE;
        }
    }

    if(GameEnd(table)==0 && moveNum==ROW*COLUMN)
        printf("\n\t\tIt is a draw!\n");

}

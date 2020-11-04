#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define resetColor textcolor(15,0);
/*UPDATES:
    -removed unnecessary comments
    -finalize functions (standardized)
    -fix minor bugs
    -add exit selection at choosing level
    ADDED FEATURES:
        -instructions of the game
        -reveal color when game is over
        -displaying the count of mines nearby inside the box when opened(just like the real minesweeper)

*/
void clrscr(void);
void textcolor(int,int);
int randomNum(int);
void instruct(void);
void chooseLevel(int*,int*,int*,int*);
int startGame(int,int,int,int);
void gameOver(int);
int playAgain(void);
int exitGame(void);
int printMine(int,int,int);

int main(){
    int result;
    int row,col,mines_count,lives;
    while(1){
        chooseLevel(&row,&col,&lives,&mines_count);
        result = startGame(mines_count,col,row,lives);
        gameOver(result);
        if(result==-1)
            break;
        else if(playAgain())
            continue;
        else
            break;
    }
    printf("\n\nTHANKS FOR PLAYING...");
    return 0;
}
void instruct(void){
    clrscr();
    textcolor(15,4);
    printf("GAME DESCRIPTION:\n");
    resetColor
    printf("    The Mines are planted inside the boxes [  ]\n");
    printf("    Be careful to choose what box to open, \n");
    printf("    use the TIP or the indicators to guide you in game.\n    GOODLUCK SOLDIER !\n\n");
    textcolor(15,2);
    printf("INSTRUCTIONS: \n");
    resetColor;
    printf("    -You can choose level, or make your own by PRESET.\n");
    printf("-   -In the game, you will choose the number of the box to open.\n");
    printf("    -The mines are randomly placed and hidden in the boxes.\n");
    printf("    -When you select box, a number with asterisk will appear,\n");
    printf("     the number indicates how many mines are randomly hidden nearby.\n");
    printf("    -When you lost the all your lives, the game will over.\n");
    printf("    -Each mine opened(Box with RED color), you life will decrease by one (1).\n");
    printf("    -When you open all the safe box(GREEN COLOR) without\n");
    printf("     losing all lives, you will WIN the game.\n");
    getch();
}
int randomNum(int max){
    return rand()%max;
}
void clrscr(void){
    system("cls");
}
void textcolor(int ForgC, int BackC){
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
int printMine(int mine,int count, int mines_nearby){
    if(mine==1){
        textcolor(15,4);
        if(count)
            printf("[*%2d ]",mines_nearby);
        else
            printf("[    ]");
        return 0;
    }
    if(mine==0){
        textcolor(15,2);
        if(count)
            printf("[*%2d ]",mines_nearby);
        else
            printf("[    ]");
        return 1;//will return to decrement remaining safes by 1
    }
}
void chooseLevel(int *row, int *col, int *lives, int *mines){
    int ch;
    int max;
    int max_cell = 10;
    while(1){
        clrscr();
        textcolor(15,4);
        printf("WELCOME TO SIMPLE MINESWEEPER GAME (BETA)\n\n");
        resetColor;
        printf("CHOOSE LEVEL\n");
        printf("[1]-EASY\n[2]-MODERATE\n[3]-HARD\n[4]-PRESET\n[5]-INSTRUCTIONS\n[0]-EXIT\n");
        switch(getch()){
            case '1':
                *row = 3;
                *col = 3;
                break;
            case '2':
                *row = 5;
                *col = 5;
                break;
            case '3':
                *row = 7;
                *col = 7;
                break;
            case '4':
            default:
                printf("\nINPUT ROWS: ");
                scanf("%d",row);
                if(*row > max_cell)
                    *row = max_cell;
                printf("INPUT COLUMNS: ");
                scanf("%d",col);
                if(*col > max_cell)
                    *col = max_cell;
                printf("INPUT MINES: ");
                scanf("%d",mines);
                max = (*row) * (*col);
                if(*mines>max)
                    *mines = max - 1;
                printf("INPUT LIVES: ");
                scanf("%d",lives);
                if(*lives>= max - *mines)
                    *lives = max - *mines - 1;
                if(*lives<1)
                    *lives = 1;
                return;
            case '5':
                instruct();
                continue;
            case '0':
                if(exitGame()){
                    printf("\nMAYBE PLAY A GAME LATER, GOODBYE...\n\n");
                    exit(0);
                }
                else
                    continue;
        }
        *mines = *col * 2 - 2;
        *lives = *col * 2 - 3;
        return;
    }
}
void gameOver(int result){
    if(result==1)
        printf("\nYOU WIN");
    else if(result==0)
        printf("\nYOU LOSE");
    if(result == -1)
        printf("\nYOU EXIT THE GAME");
    printf("   |   GAME OVER\n");
    return;
}
int exitGame(void){
    printf("Are you sure to EXIT Game? \nPress Y to EXIT, Otherwise NOT");
    switch(getch()){
    case 'y':
    case 'Y':
        return 1;
    default:
        return 0;
    }
}
int startGame(int mines_count,int col, int row, int lives){
    srand(time(0));
    int rand_pos[mines_count],i,j,temp;
    /*generates a random numbers without repetition for position of mines*/
    for(i=0;i<mines_count;i++){
        rand_pos[i]=randomNum(col*row)+1;
        for(j=0;j<i;j++){
            if(rand_pos[i]==rand_pos[j]){
                rand_pos[i]=randomNum(col*row)+1;
                j=(-1);
            }
        }
    }
    /*sort position of mines ascending*/
    for(i=0;i<mines_count;i++){
        for(j=0;j<(mines_count-i-1);j++) {
            if(rand_pos[j]>rand_pos[j+1]){
                temp=rand_pos[j];
                rand_pos[j]=rand_pos[j+1];
                rand_pos[j+1]=temp;
            }
        }
    }
    /*planting mines in 2d array */
    int planted_mines[row][col];
    int count=1,arr_count=0;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(count==rand_pos[arr_count]){
                planted_mines[i][j] = 1;
                arr_count++;
            }
            else
                planted_mines[i][j] = 0;
            count++;
        }
    }
    /*displaying and opening box*/
    int pick=0;
    int opened_pos[col*row];
    opened_pos[0]=0;
    int opened_count=0;
    int op_out=0;
    int mines_nearby = 0;
    int mine_remains = mines_count;
    int safe_remains = (col * row) - mines_count;
    int count_nearby[col*row+1];
    while(1){
        resetColor;
        clrscr();
        count=1;
        textcolor(15,4);
        printf("\n\tSIMPLE MINESWEEPER %d x %d\n",row,col);
        resetColor;
        printf("\t0 - Exit Game\n");
        printf("\n");
        for(i=0;i<row;i++){
            printf("     ");
            for(j=0;j<col;j++){
                if(count==pick){
                    mines_nearby=0;
                    if(j>0){
                        // all left
                        if(planted_mines[i][j-1]==1)
                            mines_nearby++;//left
                        if(i>0){
                            if(planted_mines[i-1][j-1]==1)
                            mines_nearby++;//upper left
                        }
                        if(i<col-1) {
                            if(planted_mines[i+1][j-1]==1)
                            mines_nearby++;//lower left;
                        }
                    }
                    if(j<col-1) {
                        //all right
                        if(planted_mines[i][j+1]==1)
                            mines_nearby++;//right
                        if(i>0) {
                            if(planted_mines[i-1][j+1]==1)
                            mines_nearby++;//upper right
                        }
                        if(i<col-1){
                            if(planted_mines[i+1][j+1]==1)
                            mines_nearby++;//lower right
                        }
                    }
                    if(i>0){
                        if(planted_mines[i-1][j]==1)
                            mines_nearby++;//up
                    }
                    if(i<row-1){
                        if(planted_mines[i+1][j]==1)
                            mines_nearby++;//down
                    }
                    //responsible for storing the count of mines nearby each box
                    count_nearby[count]=mines_nearby;
                    safe_remains-=printMine(planted_mines[i][j],count,count_nearby[count]);
                    if(planted_mines[i][j]==1){
                        lives--;
                        mine_remains--;
                    }
                }
                else if(opened_pos[opened_count]==count){
                    printMine(planted_mines[i][j],count,count_nearby[count]);
                    opened_count++;
                }
                else
                    printf("[ %2d ]",count);
                count++;
                resetColor;
            }
            printf("\n");
        }
        printf("\n");
        //reveal
        if(lives==0||safe_remains==0){
            clrscr();
            count = 1;
            printf("\n  \tSIMPLE MINESWEEPER\n  \t[ REVEALED ]\n");
            printf("\n");
            for(i=0;i<row;i++){
                printf("     ");
                for(j=0;j<col;j++){
                    printMine(planted_mines[i][j],0,count++);

                }
                textcolor(15,0);
                printf("\n");
            }
        }
        if(lives==0)
            return 0;//zero means lose
        if(safe_remains==0)
            return 1;//one means win
        opened_count=0;
        if(mines_nearby)
            printf("TIP: %d-Mine(s) Nearby Box %d \n",mines_nearby,pick);
        printf("REMAINING:\n%d-LIVES    %d-MINES    %d-SAFE\n",lives,mine_remains,safe_remains);
        while(1){
            printf("\nSELECT A NUMBER: ");
            scanf("%d",&pick);
            if(pick==0){
                if(exitGame()){
                    return -1;
                }
                else
                    continue;
            }
            else
                break;
        }
        for(i=0;i<=op_out;){
            if(pick>col*row){
                printf("%d IS NOT VALID.. ENTER ANOTHER: ",pick);
                scanf("%d",&pick);
                i=0;
                continue;
            }
            if(pick==opened_pos[i]){
                printf("ALREADY OPENED.. ENTER ANOTHER: ");
                scanf("%d",&pick);
                i=0;
                continue;
            }
            i++;
        }

        opened_pos[op_out]=pick;
        opened_count=0;
        for(i=0;i<op_out;i++){
            for(j=0;j<(op_out-i-1);j++) {
                if(opened_pos[j]>opened_pos[j+1]){
                    temp=opened_pos[j];
                    opened_pos[j]=opened_pos[j+1];
                    opened_pos[j+1]=temp;
                }
            }
        }

        op_out++;
    }
}
int playAgain(void){
    printf("DO YOU WANT TO PLAY AGAIN? \nPress Y to PLAY, Otherwise NOT\n");
    switch(getch()){
    case 'y':
    case 'Y':
        return 1;
    default:
        return 0;
    }
}


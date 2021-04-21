#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define resetColor textcolor(15,0);
/*UPDATES:
    110220-1333
    -added colorful intro game display
    -selecting using arrow keys in choosing level, play again and exit function
    -changed count of lives into heart symbols
*/
void clrscr(void);
void intro(void);
void textcolor(int,int);
int randomNum(int);
void instruct(void);
void chooseLevel(int*,int*,int*,int*);
int startGame(int,int,int,int);
void gameOver(int);
int playAgain(void);
int exitGame(void);
int printMine(int,int,int);
void gotoxy(int,int);
int clean_stdin(){
    while (getchar()!='\n');
    return 1;
}
int main(){
    int result;
    int row,col,mines_count,lives;
    intro();
    getch(); 
    while(1){
        chooseLevel(&row,&col,&lives,&mines_count);
        result = startGame(mines_count,col,row,lives);
        gameOver(result);
        if(result==-1)
            continue;
        else if(playAgain())
            continue;
        else
            break;
    }
    printf("\n\nTHANKS FOR PLAYING...");
    return 0;
}
void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}
void intro(void){
    
    system("chcp 65001  > nul");
    int i=1;
    while(1){
        clrscr();
        textcolor(15,0);
        printf("                           WELCOME TO ...\n");
        printf("                            * SIMPLE *\n");
        textcolor(i+1,0);
        printf("  ╔╗    ╔╗ ╔══╦══╗ ╔╗    ╦ ╔═══╗  ╔═══╗ ╔      ╗ ╔═══╗ ╔═══╗ ╔════╗\n");
        printf("  ║╚╗  ╔╝║    ║    ║╚╗   ║ ║     ╔╝   ╝ ║      ║ ║     ║     ║    ║\n");
        printf("  ║ ╚╗╔╝ ║    ║    ║ ╚╗  ║ ║     ║      ║      ║ ║     ║     ╠════╝\n");
        printf("  ║  ╚╝  ║    ║    ║  ╚╗ ║ ╠══╣  ╚════╗ ╚╗ ╔╗ ╔╝ ╠══╣  ╠══╣  ║     \n");
        printf("  ║      ║    ║    ║   ╚╗║ ║     ╦    ║  ╚╗║║╔╝  ║     ║     ║     \n");
        printf("  ╩      ╩ ╚══╩══╝ ╩    ╚╝ ╚═══╝ ╚════╝   ╚╝╚╝   ╚═══╝ ╚═══╝ ╩     \n");
        textcolor(15,0);
        if(i%2==0){
            gotoxy(20,5);
            textcolor(15,4);
            printf(" Press any key to start ... \n");
        }
        resetColor;
        i++;
        if(i>5)
            i=1;
        Sleep(300);
        if(kbhit())
            return;
    }

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
    printf("    -In the game, you will choose the number of the box to open.\n");
    printf("    -The mines are randomly placed and hidden in the boxes.\n");
    printf("    -When you select box, a number with asterisk will appear,\n");
    printf("     the number indicates how many mines are randomly hidden nearby.\n");
    printf("    -When you lost the all your lives, the game will over.\n");
    printf("    -Each mine opened(Box with RED color), you life will decrease by one (1).\n");
    printf("    -When you open all the safe box(GREEN COLOR) without\n");
    printf("     losing all lives, you will WIN the game.\n");
    printf("\nPRESS ANY KEY TO CONTINUE ...\n");
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
    int ch=1,level_selected=0;
    int max,i,color=1;
    int max_cell = 10;
    int easy=2, moderate=0, hard=0;
    int hover_color = 1;
    char selections[6][20]={" 1 EASY         ",
                            " 2 MODERATE     ",
                            " 3 HARD         \n",
                            " * PRESET       ",
                            " * INSTRUCTIONS ",
                            " * EXIT         "};
    while(1){
        clrscr();
        textcolor(0,15);
        printf("\n\n\t< CHOOSE LEVEL >\n");
        resetColor;
        for(i=0;i<6;i++){
            if(ch==i+1)
                textcolor(15,hover_color);
            printf("\t%s\n",selections[i]);
            resetColor;
        }
        resetColor;
        while(!kbhit()){
            gotoxy(0,0);
            textcolor(color++,0);
            printf("\tSIMPLE MINESWEEPER");
            Sleep(300);
            if(color==15)
                color=1;
        }
        resetColor;
        switch(getch()){
            case 80://down arrow
                (ch+=1)>6?ch=1:ch;
                break;
            case 72://up arrow
                (ch-=1)<1?ch=6:ch;
                break;
            case 13:
                level_selected = 1;
                break;
        }
        if(ch==5&&level_selected){
            instruct();
            level_selected = 0;
        }
        if(ch==6&&level_selected){
            if(exitGame()){
                printf("\n\nMAYBE PLAY A GAME LATER, GOODBYE...\n");
                exit(0);
            }
            else
                level_selected=0;
        }
        if(level_selected)
            break;
    }
    switch(ch){
            case 1:
                *row = 3;
                *col = 3;
                break;
            case 2:
                *row = 5;
                *col = 5;
                break;
            case 3:
                *row = 7;
                *col = 7;
                break;
            case 4:
                clrscr();
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
        }
        *mines = *col * 2 - 2;
        *lives = *col * 2 - 3;
        return;
}
void gameOver(int result){
    if(result==1){
        textcolor(15,2);
        printf("\n\tYOU WIN");
        resetColor;
    }
    else if(result==0){
        textcolor(15,4);
        printf("\n\tYOU LOSE");
        resetColor;
    }
    if(result == -1)
        printf("\nYOU EXIT THE GAME");
    printf(" | GAME OVER\n");
    return;
}
int exitGame(void){
    int ch = 0;
    while(1){
        clrscr();
        printf("\n\t╔════════════════════════════╗");
        printf("\n\t║ ARE YOU SURE TO EXIT GAME? ║\n\t║    ");
        kbhit();
        if(ch==0)
            textcolor(15,4);
        printf(" NO \t");
        resetColor;
        if(ch==1)
            textcolor(15,2);
        printf(" YES ");
        resetColor;
        printf("        ║\n\t╚════════════════════════════╝");
        switch(getch()){
            case 77:/*right*/
                (++ch)>1?ch=0:ch;
                break;
            case 75:/*left*/
                (--ch)<0?ch=1:ch;
                break;
            case 13:/*enter*/
                resetColor;
                return ch;
        }
        resetColor;
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
    char term;
    int opened_pos[col*row+1];
    opened_pos[0]=0;
    int opened_count=0;
    int op_out=0;
    int mines_nearby = 0;
    int mine_remains = mines_count;
    int safe_remains = (col * row) - mines_count;
    int count_nearby[col*row+1];
    int dont_exit = 0;
    while(1){
        resetColor;
        clrscr();
        count=1;
        textcolor(15,4);
        printf("\n\tSIMPLE MINESWEEPER %d x %d\n",row,col);
        resetColor;
        printf("\t0 - Exit Game\n\t");
        for(i=0;i<col;i++)
            printf("──────");
        printf("     \n");
        for(i=0;i<row;i++){
            printf("\t");
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
        printf("\t");
        for(i=0;i<col;i++)
            printf("──────");
        printf("\n");
        //reveal
        if(lives==0||safe_remains==0){
            clrscr();
            count = 1;
            printf("\n  \tSIMPLE MINESWEEPER\n  \t[ REVEALED ]\n");
            printf("\n");
            for(i=0;i<row;i++){
                printf("\t");
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
        textcolor(8,0);
        if(mines_nearby)
            printf("\tTIP: %d-Mine(s) Nearby Box %d\n",mines_nearby,pick);
        textcolor(15,0);printf("\tREMAINING: \n");
        textcolor(15,4);printf("\t%d-MINES",mine_remains);
        textcolor(15,2);printf("\t%d-SAFE\n",safe_remains);
        textcolor(13,0);
        printf("\tLIVES:");
        for(i=0;i<lives;i++)
            printf(" ♥");
        printf("\n");
        do{
            textcolor(0,9);
            printf("\tSELECT A NUMBER:");
            resetColor;
        }while((scanf("%d%c",&pick, &term)!=2||term!='\n')&&clean_stdin());
        if(pick==0){
            if(exitGame()){
                return -1;
            }
            else
                continue;
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
     /*  ╗ ╝ ╔ ╚ ═ ║ ╩  ╦ ╠ ╣ ╬   */
    int ch = 1;
    printf("\nPRESS ANY KEY TO CONTINUE...\n");
    getch();
    while(1){
        clrscr();
        printf("\n\t╔════════════════════════════╗");
        printf("\n\t║ DO YOU WANT TO PLAY AGAIN? ║\n\t║    ");
        kbhit();
        if(ch==0)
            textcolor(15,4);
        printf(" NO \t");
        resetColor;
        if(ch==1)
            textcolor(15,2);
        printf(" YES ");
        resetColor;
        printf("        ║\n\t╚════════════════════════════╝");
        switch(getch()){
            case 77:/*right*/
                (++ch)>1?ch=0:ch;
                break;
            case 75:/*left*/
                (--ch)<0?ch=1:ch;
                break;
            case 13:/*enter*/
                resetColor;
                return ch;
        }
        resetColor;
    }
}


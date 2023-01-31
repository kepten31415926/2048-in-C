#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include<unistd.h>
#define SIZE 4

int board[SIZE][SIZE];
int score;
int score_time;
void menu();
void resetboard();
void print_board();
void generate2();
void timer();
void move();
void down();
void up();
void right();
void left();
void play_game();
int game_over();
int game_end();
void scoreboard(int score, int type, int success, int time);
void high_score();

typedef struct{
    int player_num;
    char user_id[15];
    int user_score;
    int success; //1 no 0 yes
    int time;
    int game_type; //game type: 1 is classic, 2 is time attack
}score_board;

int main (void){
    menu();
    return 0;
    
}

void play_game(){
    generate2();
    print_board();
    move();
}

int game_over(){
    int i, j;
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(board[i][j]==0){
                return 1;//continue game when 1
            } 
            if(i < (SIZE-1) && board[i][j] == board[i+1][j]){
                return 1;
            } 
            if(j < (SIZE-1) && board[i][j] == board[i][j+1]){
                return 1;
            } 
        }
    }
    return 0;
    
}
int game_end(){
    int i, j;
    for(i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if (board[i][j]==2048){
                return 0;
                printf("congratulations you win.");
                
            }
        }
    }
    return 1;
}

void resetboard()
{ //makes everything into 0
    int x, y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            board[x][y]=0;
        }
    }
}

void generate2(){
    int y, x;
    y = rand()%(SIZE-1);
    x = rand()%(SIZE-1);

    while (board[x][y]!=0){
        y = rand()%(SIZE-1);
        x = rand()%(SIZE-1);
    }
    board[x][y]=2;  
}
void move(){
    char input;
    printf("  w  \na s d\n");
    beginning: 
    printf("enter ur move >>");
    input = getchar();
    if (input == 's'){
        down();
    } else if (input =='w'){
        up();
    } else if (input == 'd'){
        right();
    } else if (input == 'a'){
        left();
    } else{
        printf("wrong input\n");
        goto beginning;
    }
    
}
void down(){
    int x, y;
    for(y=SIZE-1;y>=0;y--){
        for(x=0;x<SIZE;x++){
            if(board[x][y]==0) continue;
            int ya = y; //use ya so it doesn't disturb the for loop
            while(board[x][ya+1]==0 && ya<(SIZE-1)){
                board[x][ya+1]=board[x][ya];
                board[x][ya]=0;
                ya++; //shift the tiles down
            }
            if(ya<(SIZE-1)&&board[x][ya+1]==board[x][ya]){
                board[x][ya+1]*=2;
                score+= board[x][ya+1];
                board[x][ya]=0; //adding tiles together
            }
                
        }
    }
}

void up(){
    int x, y;
    for(y=0;y<SIZE;y++){
        for(x=0;x<SIZE;x++){
            if(board[x][y]==0) continue;
            int ya=y;
            while(board[x][ya-1]==0 && ya>0){
                board[x][ya-1]=board[x][ya];
                board[x][ya]=0;
                ya--;//shift the tiles up
            }
            if(ya>0 && board[x][ya-1]==board[x][ya]){
                board[x][ya-1]*=2;
                score+= board[x][ya-1];

                board[x][ya]=0;
            }
        }
    }
}
void right(){
    int x, y;
    for(x=SIZE-1;x>=0;x--){
        for(y=0;y<SIZE;y++){
            if(board[x][y]==0) continue;
            int xa = x; //use xa so it doesn't disturb the for loop
            while(board[xa+1][y]==0 && xa<(SIZE-1)){
                board[xa+1][y]=board[xa][y];
                board[xa][y]=0;
                xa++; //shift the tiles down
            }
            if(xa<(SIZE-1)&&board[xa+1][y]==board[xa][y]){
                board[xa+1][y]*=2;
                score+= board[xa+1][y];
                board[xa][y]=0; //adding tiles together
            }
                
        }
    }
}
void left(){
    int x, y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(board[x][y]==0) continue;
            int xa=x;
            while(board[xa-1][y]==0 && xa>0){
                board[xa-1][y]=board[xa][y];
                board[xa][y]=0;
                xa--;//shift the tiles left
            }
            if(xa>0 && board[xa-1][y]==board[xa][y]){
                board[xa-1][y]*=2;
                score+= board[xa-1][y];
                board[xa][y]=0;
            }
        }
    }
}

void print_board(){
    int x, y;
    for(y=0;y<SIZE;y++){
        printf("|");
        for(x=0;x<SIZE;x++){
            if(board[x][y]<9){
                printf(" ");}
            if(board[x][y]<100){
                printf(" ");
            }
            if(board[x][y]==0){
                printf(" |");
            } else{
            printf("%d|",board[x][y]);
            }
            
        }
        printf("\n");
    }
    printf("\nscore: %d \n", score);
}


void menu(){
    int select;
    char select1;
    beginning: 
        printf("---Welcome to 2048---\n1) Play 2048: Classic Mode\n2) Play 2048: Time Attack!\n3) How to Play\n4) Ranking\n5) Exit\nSelect >>");
        scanf("%d", &select);
        system("cls");
        switch (select){
            case 1: //classic mode
            score = 0;
            score_time = 0;
            time_t start_time1;
            time_t current_time1;
            resetboard();
            generate2();
            time(&start_time1);

            while(game_over()==1&&game_end()==1){
                time(&current_time1);
                score_time = difftime(current_time1, start_time1);
                printf("\ntime elapsed: %d\n",score_time);

                play_game();
                system("cls");

            }
            print_board();
            printf("game over :(");
            scoreboard(score, select, game_end(), score_time);
            select_again:
                printf("\n1: go back to menu\n2: exit\n>>");
                select1 = getchar();
                if(select1 == '1'){
                    goto beginning;
                } else if (select1 == '2'){
                    break;
                    } else{
                        printf("\ninvalid input\n");
                        goto select_again;
                        }
            case 2: //time attack
                resetboard();
                score = 0;
                score_time=120;
                time_t start_time;
                time_t current_time;
                int elapsed_time;
                generate2();
                time(&start_time);
                while(game_over()==1&&score_time>0&&game_end()==1){
                    time(&current_time);
                    elapsed_time = difftime(current_time, start_time);
                    printf("\ntime left: %d\n", score_time);
                    play_game();
                    system("cls");
                    score_time -= elapsed_time;
                    }
                print_board();
                printf("game over :(");
                scoreboard(score, select, game_end(), score_time);
                select_again2: 
                    printf("\n1: go back to menu\n2: exit");
        
                    select1 = getchar();
                    if(select1 == '1'){
                        system("cls");
                        goto beginning;
                    } else if (select1 == '2'){
                        break;
                    } else{
                        printf("\ninvalid input\n");
                        goto select_again2;
                    }
            case 3:
                printf("---classic mode---\n1) use wasd to move the tiles\n2) tiles will appear in a blank space every move\n");
                printf("3) same tiles will add up\n4) score will increase every time they add up\n");
                printf("5) the game will end when:\n     a)a tile reaches 2048\n     b)no more moves are available\n\n");
                printf("---time attack---\n1) classical gameplay rules are similarly applied\n2) game will end in 120 seconds\n");
                beg4:
                    printf("\ngo back (1)");
                    int l;
                    scanf("%d", &l);
                if(l==1){
                    system("cls");
                    goto beginning;
                }else{
                    printf("\ninvalid input\n");
                    goto beg4;
                }
            case 4:
                high_score();
                int i;
                beginning4:
                printf("go back (1)");
                scanf("%d", &i);
                if(i==1){
                    goto beginning;
                } else{
                    printf("\nselect again\n");
                    goto beginning4;
                }
            case 5:
                break;
            default:
                printf("\ninvalid input\n");
                goto beginning;
    }
}

void scoreboard(int score, int type, int success, int time){
    FILE *scorefile;
    if (type ==1){
        scorefile = fopen("classic_score.txt", "a");
    } else if (type ==2){
        scorefile = fopen("time_scores.txt", "a");
    } else {
        printf("error");
    }
    
    char user[15];
    score_board array[50];
    int i;
    for(i=0;i<50;i++){
        if(array[i].user_score==0){
            break;
        }
    }
    array[i].player_num=i;
    array[i].user_score = score;
    array[i].game_type = type;
    array[i].success= success;
    array[i].time = time;
    printf("\nEnter ur game id:");
    scanf("%s", user);
    strcpy(array[i].user_id, user);
//error here 
    fwrite(&array[i], sizeof(score_board), 1, scorefile);
    fclose(scorefile);
    

}

void high_score(){
    int type;
    FILE *scorefile;

    beginning:
        printf("which type of score board would you like to view?\n");
        printf("(1) classic    (2) time attack\n>>");
        scanf("%d", &type);
        if (type == 1){
            scorefile = fopen("classic_score.txt", "r");
        }else if (type ==2){
            scorefile = fopen("time_score.txt", "r");
        }else {
            printf("\ninvalid integer\n");
            goto beginning;
        }
    
    score_board array[50];
    int i = 0;

    while (fread(&array[i], sizeof(score_board), 1, scorefile)) {
        i++;
    }

    int j;
    for (i = 0; i < 50 - 1; i++) {
        for (j = 0; j < 50 - i - 1; j++) {
            if (array[j].user_score < array[j + 1].user_score) {
                score_board temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    //success or nay
    
    // print sorted scores
    for (i = 0; i < 50; i++) {
        if (array[i].user_id[0] == '\0') {  
            break;
        }
        char yesorno[5];
        if(array[i].success==1){
            strcpy(yesorno, "no");
        } else if(array[i].success == 0){
            strcpy(yesorno, "yes");
        }
        printf("\nGame ID: %s   Score: %d     Time: %d     Success: %s\n", array[i].user_id, array[i].user_score, array[i].time, yesorno);
    }
    fclose(scorefile);  

}

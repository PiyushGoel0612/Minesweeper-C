#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"Minesweeper.h"

int main(){
    lvl = 0;
    LIST* lst = malloc(sizeof(LIST));
    lst = init(lst);

    while(1 == 1){
        char emp[10];
        printf("Enter the size of board between 4 and 10\n");
        fgets(emp, sizeof(emp), stdin);
        size = atoi(emp);
        if(size >=4 && size <= 10){
            break;
        }
    }
    lvl = size+size/4;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            lst = addEnd(lst,i,j,0);      // list,row,col,value
        }
    }
    printf("There are %d number of mines on the board in total\n",lvl);
    printf("To reveal : r/\n");
    printf("To mark or unmark flag : m/\n");
    display(lst);
    printf("\n\n");
    printf("Enter Action and Coordinates : ");

    // Taking first input
    int xx,yy;
    char Input[100];
    char* a;
    while(1 ==1){
    fgets(Input,100,stdin);
        a = strtok(Input, " ");
        xx = atoi(strtok(NULL, " ")); 
        yy = atoi(strtok(NULL, " ")); 
        if(strcmp(a,"r/") == 0 || strcmp(a,"m/") == 0){
            if(xx >= 0 && xx < size && yy >= 0 && yy < size){
                break;
            }
            else{
                printf("\033[2J"); 
                printf("\033[H");
                printf("There are %d number of mines on the board in total\n",lvl);
                printf("To reveal : r/\n");
                printf("To mark or unmark flag : m/\n");
                display(lst);
                printf("\n\n");
                printf("Enter Action and Coordinates : ");
            }
        }
        else{
            printf("\033[2J"); 
            printf("\033[H");
            printf("There are %d number of mines on the board in total\n",lvl);
            printf("To reveal : r/\n");
            printf("To mark or unmark flag : m/\n");
            display(lst);
            printf("\n\n");
            printf("Enter Action and Coordinates : ");
        }
    }
    NODE* wee;

    // Placing Mines
    srand(time(NULL));
    int t = 0;
    while(t < lvl){
        int rx = rand() % size;
        int ry = rand() % size;
        wee = traverse_list(lst, rx, ry);
        if(wee->num != 9 && (rx!=xx || ry!=yy)){
            wee->num = 9;
            t+=1;
        }
    }
    lst = AssignNum(lst);
    
    // checking for grouping
    if(!strcmp(a,"r/")){
        lst = Group(lst,xx,yy);
    }
    else if(!strcmp(a,"m/")){
        NODE* temp = traverse_list(lst,xx,yy);
        temp->pressed = 2;
    }
    else{
        printf("Invalid action");
    }
    printf("\033[2J"); 
    printf("\033[H"); 
    printf("There are %d number of mines on the board in total\n",lvl);
    printf("To reveal : r/\n");
    printf("To mark or unmark flag : m/\n");
    display(lst);

    t = 1;
    while(t!=0){
        printf("\n\n");
        printf("Enter Action and Coordinates : ");
        fgets(Input,100,stdin);
        a = strtok(Input, " ");
        xx = atoi(strtok(NULL, " ")); 
        yy = atoi(strtok(NULL, " "));
        if(!strcmp(a,"r/")){
            wee = traverse_list(lst,xx,yy);
            if(wee == NULL){
                printf("\n**** invalid input ****");
                continue;
            }
            else if(wee->num == 9){
                t = 0;
                printf("\n**** BOMB!!! ****");
                continue;
            }
            else if(wee->pressed == 1){
                printf("\n**** invalid input ****");
                continue;
            }
            else{
                lst = Group(lst,xx,yy);
            }
        }
        else if(!strcmp(a,"m/")){
            NODE* temp = traverse_list(lst,xx,yy);
            if(temp->pressed == 0){
                temp->pressed = 2;
            }
            else{
                temp->pressed = 0;
            }
        }
        else{
            printf("\nInvalid action\n");
        }
        printf("\033[2J");
        printf("\033[H"); 
        printf("There are %d number of mines on the board in total\n",lvl);
        printf("To reveal : r/\n");
        printf("To mark or unmark flag : m/\n");
        int x = display(lst);
        if(x == 1){
            t = 0;
            printf("\n**** Thy has 1 ****\n");
        }
    }
}
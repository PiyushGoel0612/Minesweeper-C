#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int size;
int lvl;

typedef struct Node{
    int num;
    int x;
    int y;
    int pressed;
    struct Node *next;
}NODE;

typedef struct List{
    NODE *head;
    struct List* down;
}LIST;

LIST* init(LIST* hd);
NODE* traverse_list(LIST* list, int x, int y);
LIST* addEnd(LIST* lst, int rw, int col, int m);
LIST* AssignNum(LIST* lst);
int display(LIST* lst);
LIST* Group(LIST* lst,int x,int y);
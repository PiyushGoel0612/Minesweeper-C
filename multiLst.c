#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

LIST* init(LIST* hd){
    hd->head = NULL;
    hd->down = NULL;
    return hd;
}

LIST* addEnd(LIST* lst, int rw, int col, int m){
    if(rw == 0){
        NODE* p = (NODE*)malloc(sizeof(NODE));
        p->num = m;
        p->x = rw;
        p->y = col;
        p->pressed = 0;
        p->next = NULL;
        if(lst->head == NULL){
            lst->head = p;
            return lst;
        }
        NODE* q = lst->head;
        while(q->next!= NULL){
            q = q->next;
        }
        q->next = p;
        return lst;
    }
    LIST* temp1 = lst;
    for(int i=0; i<rw-1; i++){
        temp1 = temp1->down;
    }
    if(temp1->down == NULL){
        temp1->down = malloc(sizeof(LIST));
        temp1 = temp1->down;
        NODE* head = malloc(sizeof(NODE));
        temp1->head = head;
        head->num = m;
        head->x = rw;
        head->y = col;
        head->pressed = 0;
        head->next = NULL;
        temp1->down = NULL;
        return lst;
    }
    else{
        temp1 = temp1->down;
    }
    NODE* node = temp1->head;
    while(node->next!=NULL){
        node = node->next;
    }
    node->next = malloc(sizeof(NODE));
    node = node->next;
    node->next = NULL;
    node->num = m;
    node->x = rw;
    node->pressed = 0;
    node->y = col;
    return lst;
}

NODE* traverse_list(LIST* list, int x, int y){
    if(x > 7 || y > 7){
        return NULL;
    }
    LIST* temp = list;
    for(int i=0; i<x; i++){
        temp = temp->down;
    }
    NODE* slow = temp->head;
    for(int j=0; j<y; j++){
        slow = slow->next;
    }
    return slow;
}

void display(LIST* lst){
    LIST* temp1 = lst;
    printf("\n");
    int x = 0;
    while(temp1!= NULL){
        NODE* node = temp1->head;
        printf("%d   ",x);
        while(node!= NULL){
            printf("[%d] ", node->pressed);
            node = node->next;
        }
        printf("\n");
        temp1 = temp1->down;
        x+=1;
    }
    printf("\n");
    printf("    ");
    for(int i = 0; i < x; i++){
        printf(" %d  ", i);
    }
    return;
}

int main(){
    LIST* lst = malloc(sizeof(LIST));
    lst = init(lst);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            lst = addEnd(lst,i,j,-1);      // list,row,col,value
        }
    }
    display(lst);
    printf("\n");
    printf("Enter maadi : ");

    int xx,yy;
    scanf("%d %d",&xx,&yy);
    NODE* wee = traverse_list(lst,xx,yy);
    wee->pressed = 1;

    srand(time(NULL));
    int t = 0;
    while(t < 10){
        int rx = rand() % 8;
        int ry = rand() % 8;
        wee = traverse_list(lst, rx, ry);
        if(wee->num != 9 && (rx!=xx || ry!=yy)){
            wee->num = 9;
            t+=1;
        }
    }
    display(lst);

    t = 1;
    while(t!=0){
        printf("\n");
        printf("Enter maadi : ");
        scanf("%d %d",&xx,&yy);
        wee = traverse_list(lst,xx,yy);
        if(wee == NULL){
            printf("**** galat input ****");
            continue;
        }
        else if(wee->num == 9){
            t = 0;
            printf("**** BOMB!!! ****");
            continue;
        }
        else if(wee->pressed == 1){
            printf("**** galat input ****");
            continue;
        }
        else{
            wee->pressed = 1;
        }
        display(lst);
    }
}
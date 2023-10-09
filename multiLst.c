#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

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

LIST* AssignNum(LIST* lst){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j  < 8; j++){
            NODE* n = traverse_list(lst,i,j);
            if(n->num!=9){
                int ngb[8][2] = {{i-1,j-1},{i-1,j},{i-1,j+1},
                                {i,j-1},{i,j+1},
                                {i+1,j-1},{i+1,j},{i+1,j+1}};
                for(int k = 0; k < 8; k++){
                    if(ngb[k][0] >= 0 && ngb[k][0] <= 7){
                        if(ngb[k][1] >= 0 && ngb[k][1] <= 7){
                            NODE* nb = traverse_list(lst,ngb[k][0],ngb[k][1]);
                            if(nb->num == 9){
                                n->num+=1;
                            }
                        }
                    }
                }
            }
        }
    }
    return lst;
}

int display(LIST* lst){
    int count = 0;
    LIST* temp1 = lst;
    printf("\n");
    int x = 0;
    while(temp1!= NULL){
        NODE* node = temp1->head;
        printf("%d   ",x);
        while(node!= NULL){
            if(node->pressed == 1){
                printf("[%d] ", node->num);
                count+=1;
            }
            else if(node->pressed == 2){
                printf("[*] ");
            }
            else{
                printf("[ ] ");
            }
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
    if(count == 54){
        return 1;
    }
    else{
        return 0;
    }
}

LIST* Group(LIST* lst,int x,int y){
    NODE* temp = traverse_list(lst,x,y);
    if(temp->num != 0){
        temp->pressed = 1;
        return lst;
    }
    else{
        temp->pressed = 1;
        int ngb[50][2] = {{x-1,y-1},{x-1,y},{x-1,y+1},
                          {x,y-1},{x,y+1},
                          {x+1,y-1},{x+1,y},{x+1,y+1}};
        for(int k = 0; k < 8; k++){
            if(ngb[k][0] >=0 && ngb[k][1] >=0 && ngb[k][0] <= 7 && ngb[k][1] <= 7){
                NODE* n = traverse_list(lst,ngb[k][0],ngb[k][1]);
                if(n->pressed != 1 && n->num !=9){
                    n->pressed = 1;
                    lst = Group(lst,ngb[k][0],ngb[k][1]);
                }
            }
        }
        return lst;
    }
}

int main(){
    LIST* lst = malloc(sizeof(LIST));
    lst = init(lst);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            lst = addEnd(lst,i,j,0);      // list,row,col,value
        }
    }
    printf("To reveal : r/\n");
    printf("To mark or unmark flag : m/\n");
    display(lst);
    printf("\n\n");
    printf("Enter Action and Coordinates : ");

    // Taking first input
    int xx,yy;
    char Input[100];
    char* a;
    fgets(Input,100,stdin);
    a = strtok(Input, " ");
    xx = atoi(strtok(NULL, " ")); 
    yy = atoi(strtok(NULL, " ")); 
    NODE* wee;

    // Placing Mines
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
            printf("\nInvalid action");
        }
        printf("\033[2J");
        printf("\033[H"); 
        printf("To reveal : r/\n");
        printf("To mark or unmark flag : m/\n");
        int x = display(lst);
        if(x == 1){
            t = 0;
            printf("\n**** Thy has 1 ****\n");
        }
    }
}
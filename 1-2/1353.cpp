typedef struct Web{
    char addr[100];
    struct Web *pre;
    struct Web *next;
}Web;
#include <bits/stdc++.h>
using namespace std;
Web * createList(){
    Web *L;
    L = (Web*)malloc(sizeof(Web));
    L->next = NULL;
    return L;
}

void inputSingle(Web *s){
    scanf("%s",s->addr);
}


void outputSingle(Web *s){
    printf("%s\n",s->addr);
}


void inputTail(Web *s ,Web *p){
    s->next = NULL;
    p->next = s;
    s->pre = p;
}


int main(){
    Web *s,*L,*p;
    char order[20];
    L = createList();
    p = L;
    while(1){
        scanf("%s",order);
        switch(order[0]){
            case 'V':
            s = (Web*)malloc(sizeof(Web));
            inputSingle(s);
            outputSingle(s);
            inputTail(s,p);
            p = s;
            break;
            case 'B':
            if (p->pre == L){
                printf("Ignored\n");
            }
            else{
                outputSingle(p->pre);
                p = p->pre;
            }
            break;
            case 'F':
            if (p->next==NULL){
                printf("Ignored\n");
            }
            else {
                outputSingle(p->next);
                p = p->next;
            }
            break;
            case 'Q':
            exit(0);
        }
    }
}
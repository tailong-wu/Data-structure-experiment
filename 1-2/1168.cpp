#include <bits/stdc++.h>
using namespace std;
typedef struct Customer {
    char guestnumber;
    char guesttype;
    int number;
    struct Customer *next;
} Customer;
Customer * createList(){
    Customer *C = (Customer*)malloc(sizeof(Customer));
    C->next= NULL;
    return C;
}

void inputSingle(Customer *s){
    scanf("%s %s",s->guestnumber,s->guesttype);
}

void outputSingle(Customer *s){
    scanf("%d %s %s\n",s->number,s->guestnumber,s->guesttype);
}

int Count(Customer *L,Customer *s){
    Customer *p = L->next;
    Customer *temp = s;
    int k = 0;
    int count = 0;
    while (p!=NULL)
    {
        count++;
        p = p->next;
    }
    while(temp !=NULL){
        k ++;
        temp = temp->next;
    }
    return count-k;
}


void outputSingle(Customer *L,Customer *s,int k){
    s->number = k;
    printf("IN:%d ",s->number);
    printf("%s %s %d\n",s->guestnumber,s->guesttype,Count(L,s));
}

void insertTail(Customer *L,Customer *s){
    Customer *p,*pre;
    pre = L;
    p = L->next;
    while(p!=NULL)
    {
        p = p->next;
        pre = pre->next;
    }
    pre->next = s;
    s->next = NULL;
}

void judge(Customer *L,Customer *s){
    char
}
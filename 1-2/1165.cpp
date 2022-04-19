#include<bits/stdc++.h>
using namespace std;
typedef struct Customer{
	char guestnumber[20];
	char guesttype[10];
	struct Customer *next;
}Customer;
Customer *createList()
{
	Customer *L;
	L=(Customer *)malloc(sizeof(Customer));
	L->next=NULL;
	return L;
}
void inputSingle(Customer *s)
{
	scanf("%s %s",s->guestnumber,s->guesttype);
}
void outputSingle(Customer *s,int i)
{
	printf("%d ",i);
	printf("%s %s %d\n",s->guestnumber,s->guesttype,i-1);
	
}
void insertTail(Customer *L,Customer *s)
{
	Customer *p,*pre;
	pre=L;
	p=L->next;
	while(p!=NULL)
	{
		p=p->next;
		pre=pre->next;
	}
	pre->next=s;
	s->next=NULL;
}
void IN(Customer *L,int i)
{
	Customer *s=(Customer *)malloc(sizeof(Customer));
	inputSingle(s);	
	outputSingle(s,i);
	insertTail(L,s);
} 
void List(Customer *L,int i)
{
	int j=1;
	printf("LIST:\n");
	Customer *p=L->next;
	while(p!=NULL)
	{
		outputSingle(p,j);
		j++;
		p=p->next;
	}
}
int main()
{
	int i=1;
	Customer *L,*s;
	L=createList();
	char op[10];
	while(1)
	{
		scanf("%s",op);
		switch(op[0])
		{
			case 'I':
				printf("IN:");
				IN(L,i);
				i++;
				break;
			case 'L':
				List(L,i);
				break;
			case 'Q':
				printf("GOOD BYE!\n");
				exit(0);
		}
	}
	return 0;
}
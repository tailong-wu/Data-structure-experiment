typedef struct {
    ElementType *array;// 存放元素的数组
    int top;// 栈顶的下标，该下标用于存放元素的数组array
    int capacity;// 容量
}SeqStack;


int full(SeqStack *S)
{
	if(S->top>=S->capacity-1) return 1;// 栈顶指针是否大于等于容量减一
	return 0;
}




int push(SeqStack *S,ElementType x)
{
	if(full(S))
		return 0;
	S->top++;// 栈顶位置加一
	S->array[S->top]=x; //并以栈顶位置作为数组的索引赋值 
	return 1;
}

int empty(SeqStack *S)
{
	if(S->top==-1) // 栈顶位置是否还是-1
		return 1;
	return 0;
}

int pop(SeqStack *S)
{
	if(empty(S))
		return 0;
	S->top--;// 栈顶位置减一，不用返回值，这不是python
	return 1;
}


ElementType top(SeqStack *S)
{
	return S->array[S->top]; // 读取栈顶数据 就是将top作为位置直接返回数组中对应位置的值即可
}



void clearStack(SeqStack *S){
    S->top=-1;
}


void destroyStack(SeqStack *S)
{
	free(S->array);// 释放指向数组的指针
	free(S);// 释放指向栈的指针
	S=NULL;// 并将栈的指针指向NULL
}

// 
int match(char ch,char str)
{
	if(ch=='(' && str==')')
		return 1;
	else if(ch=='{' && str=='}')
		return 1;
	else if(ch=='[' && str==']')
		return 1;
	else 
		return 0; 
}
int judge(char *a,SeqStack *S)
{	
	char ch;
	for(int i=0;a[i]!='\0';i++)
	{
		if(a[i]=='[' || a[i]=='{' || a[i]=='(')
			push(S,a[i]);
		if(a[i]==']' || a[i]=='}' || a[i]==')')
		{
			if(empty(S))
				return 0;
			ch=top(S);
			if(match(ch,a[i])==0)
				return 0;
			pop(S);
		}
	}
	if((empty(S)))
		return 1;
	return 0;
}
int main()
{
	SeqStack *S;
	int capacity=1000;
	S=createStack(capacity);
	char a[1000];
	gets(a);
	if(judge(a,S))
		printf("yes\n");
	else
		printf("no\n");
}

// 






#include <bits/stdc++.h>
using namespace std;

typedef int KeyType;
typedef struct
{
    KeyType value;
    int weight;
} Node;

typedef struct HTNode
{
    KeyType value; //节点数值
    int weight;  //节点权
    HTNode * lchild;
    HTNode * rchild;
    int depth;
    bool operator < (const HTNode &a)const
    {
        return weight < a.weight||(weight==a.weight&&value < a.value);
    }
} HTNode, *HuffmanTree;

typedef HuffmanTree ElementType;
typedef struct
{
    ElementType * data; //数据
    int size;	 		//大小
    int capacity;  		//容量
} HNode, *Heap;


// 队首
ElementType front(Heap H)
{
	return H->data[1];
}


// 保持子堆性质
void heapify(Heap H,int i)
{
	int l,r;
	int smallest;
	l=left(i);
	r=right(i);
	smallest=i;
	if(l<=H->size && *(H->data[l])<*(H->data[i]))
		smallest=l;
	if(r<=H->size && *(H->data[r])<*(H->data[smallest]))
		smallest=r;
	if(smallest!=i)
	{
		swap(H,i,smallest);
		heapify(H,smallest);
	}
} 

// 堆初始化
void initHeap(Heap H,Node data[],int n)
{
	int i;
	HTNode *p=NULL;
	for(int i=1;i<=n;i++)
	{
		p=(HTNode *)malloc(sizeof(HTNode));
		p->value=data[i].value;
		p->weight=data[i].weight;
		p->lchild=NULL;
		p->rchild=NULL;
		H->data[i]=p;
	}
	H->size=n;
	for(i=n/2;i>=1;i--)
		heapify(H,i);
}

// 入队
void push (Heap H,ElementType x)
{
	H->size++;
	int i=H->size;
	H->data[i]=x;
	while(i>1 && *(H->data[i])<*(H->data[parent(i)]))
	{
		swap(H,i,parent(i));
		i=parent(i);
	}
} 

// 出队
void pop(Heap H)
{
	if(!empty(H))
	{
		H->data[1]=H->data[H->size];
		H->size--;
		heapify(H,1);
	}
}

// 创建
HuffmanTree createHuffmanTree(Node data[],int n)
{
	Heap H=createHeap(n);
	initHeap(H,data,n);
	HTNode *p,*q,*t;
	for(int i=1;i<n;i++)
	{
		p=front(H),pop(H);
		q=front(H),pop(H);
		t=(HTNode *)malloc(sizeof(HTNode));
		t->value=min(p->value,q->value);
		t->weight =p->weight+q->weight;
		t->lchild=p;
		t->rchild=q;
		push(H,t); 
	} 
	HuffmanTree HT=front(H);
	pop(H);
	destroyHeap(H);
	return HT;
}
// 带权路径长度
int getWPL(HuffmanTree HT)
{
	if(HT==NULL)
		return 0;
	if(HT->lchild==NULL && HT->rchild==NULL)
		return HT->weight*HT->depth;
	return getWPL(HT->lchild)+getWPL(HT->rchild);
} 

// 节点深度
void initDepth(HuffmanTree HT,int depth)
{
	if(HT==NULL)
		return;
	HT->depth=depth;
	initDepth(HT->lchild,depth+1);
	initDepth(HT->rchild,depth+1); 
} 


// 编码
void huffmanCode(HuffmanTree HT,int code[],int depth)
{
	if(HT==NULL)
		return ;
	if(HT->lchild==NULL && HT->rchild==NULL)
	{
		printf("%d:",HT->value);
		for(int i=0;i<depth;i++)
			printf("%d",code[i]);
		printf("\n");
		return ;
	}
	if(HT->lchild!=NULL)
	{
		code[depth]=0;
		huffmanCode(HT->lchild,code,depth+1);
	}
	if(HT->rchild!=NULL)
	{
		code[depth]=1;
		huffmanCode(HT->rchild,code,depth+1);
	}
}

//哈夫曼树
//#include<bits/stdc++.h>
//using namespace std;
int main(){
	priority_queue<int,vector<int>,greater<int> > Q;
	int n,a,b,s,x;
	int sum=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&s,&x);
		Q.push(x);
	} 
	for(int i=1;i<n;i++){
		a=Q.top(),Q.pop();
		b=Q.top(),Q.pop();
		sum=sum+a+b;
		Q.push(a+b);
	}
	printf("%d\n",sum);
	return 0;
}

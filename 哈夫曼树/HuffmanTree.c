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
// 和堆类似，largest编程smallest
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
// heapify系统已预置
void initHeap(Heap H,Node data[],int n)
{
	int i;
	HTNode *p=NULL;
	// 遍历树，将data赋值，但是哈夫曼树的结点有更多属性 （参考题目给出的结构体）
	// 总之每一次 创建一个哈夫曼结点
	// 将data的value，weight赋值
	// 左右结点均为null
	// 之后把该data点更新为现在的哈夫曼树结点（遍历条件改变的内容）
	for(int i=1;i<=n;i++)
	{
		p=(HTNode *)malloc(sizeof(HTNode));
		p->value=data[i].value;
		p->weight=data[i].weight;
		p->lchild=NULL;
		p->rchild=NULL;
		H->data[i]=p;
	}
	// 同堆，反向遍历保持性质
	H->size=n;
	for(i=n/2;i>=1;i--)
		heapify(H,i);
}

// 入队
// 与堆类似
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
// 与堆类似
void pop(Heap H)
{
	if(!empty(H))
	{
		H->data[1]=H->data[H->size];
		H->size--;
		// 保持子堆性质函数输入：堆，索引
		heapify(H,1);
	}
}

// 创建
// 创建哈夫曼树的主要思路就是先用data创建最小堆
// 之后遍历该堆
// 每次取出两个个最小堆结点
// 每次创建一个哈夫曼树的节点
// 将较小value的赋值为根
// 将weight为两个相加
// 赋值为左右节点
// 将该哈夫曼树入队到堆中
// 之后将该堆存为哈夫曼树
// 注意存的过程中指定堆的队首为赋值对象
HuffmanTree createHuffmanTree(Node data[],int n)
{
	Heap H=createHeap(n);
	initHeap(H,data,n);
	HTNode *p,*q,*t;
	for(int i=1;i<n;i++)
	{
		// 注意该语句 出现较少
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
	return HT;
}

// 带权路径长度
//  该函数返回哈夫曼树HT的带全路径长度。
//  其中哈夫曼树HT每个节点的weight为该节点的全，depth为该接节点的深度(树根深度为0). 
int getWPL(HuffmanTree HT)
{
	// 判空
	if(HT==NULL)
		return 0;
	// 左右节点为空时返回该节点的权乘以深度
	if(HT->lchild==NULL && HT->rchild==NULL)
		return HT->weight*HT->depth;
	// 如果存在其中一个左右节点则获得左右节点深度相加
	return getWPL(HT->lchild)+getWPL(HT->rchild);
} 

// 节点深度
// 该函数初始化哈夫曼树HT中每个节点的深度depth。其中根节点深度为0. 
void initDepth(HuffmanTree HT,int depth)
{
	// 判断是否存在
	if(HT==NULL)
		return;
	// 赋值深度
	HT->depth=depth;
	// 递归左右子树 赋值深度(注意子树时深度已经加1)
	initDepth(HT->lchild,depth+1);
	initDepth(HT->rchild,depth+1); 
} 


// 编码
// 该函数按先序遍历的顺序输出哈夫曼树所有叶节点的值和编码，值与编码以“:”隔开（7:01000）。
// 每个叶节点的编码输出一行，编码采用左0右1的编码方案。 
// 参数code[]存放当前节点的编码(从code[0]开始保存)，depth表示当前节点的层次 。
void huffmanCode(HuffmanTree HT,int code[],int depth)
{
	// 判断是否存在
	if(HT==NULL)
		return ;
	// 如果左右节点为空
	if(HT->lchild==NULL && HT->rchild==NULL)
	{
		// 打印数值
		printf("%d:",HT->value);
		// 遍历i到depth的code值
		for(int i=0;i<depth;i++)
			printf("%d",code[i]);
		// 常规换行
		printf("\n");
		return ;
	}
	// 左节点不为空
	if(HT->lchild!=NULL)
	{
		// code depth位置 赋值为0
		code[depth]=0;
		// 递归，depth+1
		huffmanCode(HT->lchild,code,depth+1);
	}
	// 右节点不为空
	if(HT->rchild!=NULL)
	{
		// code depth位置 赋值为1
		code[depth]=1;
		// 同左
		huffmanCode(HT->rchild,code,depth+1);
	}
}

//哈夫曼树
// 给定n个互不相同的整数，以及这些整数出现的次数。
// 以每个整数出现的次数作为权值，构造一颗哈夫曼树。
// 求哈夫曼树的加权路径长度。
//#include<bits/stdc++.h>
//using namespace std;
int main(){
	// 创建优先队列，数组，最大堆
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

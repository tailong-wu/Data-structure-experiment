#include <bits/stdc++.h>
using namespace std;

typedef int ElementType;
typedef struct{
	ElementType *data; //数据
	int size;	 		//大小
	int capacity;  		//容量
}HNode, *Heap;


// 创建
Heap createHeap(int capacity){
    Heap H;
    H = (Heap)malloc(sizeof(HNode));
    H->size = 0;
    H->capacity = capacity;
    H->data = (ElementType*)malloc((capacity+1)*sizeof(ElementType));
    return H;
}

// 父节点
int parent(int i){
    return i/2;
}

// 左子节点
int left(int i){
    return i*2;
}


// 右子节点
int right(int i){
    return i*2+1;
}


// 判满
int full(Heap H){
    if (H->size == H->capacity) return 1;
    return 0;
}


// 判空
int empty(Heap H){
    if (H->size == 0 )return 1;
    return 0;
}

// 交换
void swap(Heap H, int i, int j){
    ElementType  x;
    x=H->data[i];
    H->data[i] = H->data[j];
    H->data[j] =x;
}


// 增大节点数值
void increase(Heap H, int i, ElementType x){
    if(H->data[i]<x){
        H->data[i] = x ;
        while(i>1 && H->data[parent(i)]<H->data[i]){
            swap(H,i,parent(i));
            i = parent(i);
        }
    }
}


// 插入
int insert(Heap H, ElementType x){
    if(H->size == H->capacity) return 0;
    H->size ++ ;
    int i = H->size;
    H->data[i] = x;
    while(i<1&&H->data[parent(i)]<H->data[i]){
        swap(H,i,parent(i));
        i = parent(i);
    }
    return 1;
}

//保持子堆性质
void heapify(Heap H,int i)
{
	int l,r;
	int largest;
	l=left(i);
	r=right(i);
	if(l<=H->size && H->data[l]>H->data[i])
		largest=l;
	else
		largest=i;
	if(r<=H->size && H->data[r]>H->data[largest]) 
		largest=r;
	if(largest!=i)
	{
		swap(H,i,largest);
    	heapify(H,largest);
	} 	
}

// 初始化
void initHeap(Heap H, ElementType data[], int n)
{
	int i;
	for(int i=1;i<=n;i++)
		H->data[i]=data[i];;
	H->size=n;
	for(i=n/2;i>=1;i--)
		heapify(H,i);
}

// 堆排序
void heapSort(Heap H)
{
	int n=H->size;
	for(int i=H->size;i>1;i--)
	{
		swap(H,1,i);
		H->size--;
		heapify(H,1);
	}
	H->size=n;
}

// 销毁
void destroyHeap(Heap H)
{
	if(H!=NULL)
	{
		free(H->data);
		free(H);
	}
}

// 队首
ElementType front(Heap H)
{
	return H->data[1];
} 

// 入队
int push(Heap H,ElementType x)
{
	if(full(H))
		return 0;
	H->size++;
	int i=H->size;
	H->data[i]=x;
	while(i>1&&H->data[parent(i)]<H->data[i])
	{
		swap(H,i,parent(i));
		i=parent(i);
	}
	return 1;
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

int main()
{
    return 0;
}

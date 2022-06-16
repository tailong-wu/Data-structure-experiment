#include <bits/stdc++.h>
using namespace std;

typedef int ElementType;
typedef struct{
	ElementType *data; //数据
	int size;	 		//大小
	int capacity;  		//容量
}HNode, *Heap;


// 该部分重要的是如何再改变数值之后保持堆的性质不变
// 从最后一层向上遍历，直到索引为1或者该索引指向节点与其父节点违反现在堆的性质



// 创建
Heap createHeap(int capacity){
    Heap H;
    H = (Heap)malloc(sizeof(HNode));// 分配内存
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
	// 查找该节点位置
	// 首先满足该节点的位置比x小，才能增大
    if(H->data[i]<x){
		// 增大
        H->data[i] = x ;
        // 保持性质
		while(i>1 && H->data[parent(i)]<H->data[i]){
            swap(H,i,parent(i));
            i = parent(i);
        }
    }
}


// 插入 最大堆
int insert(Heap H, ElementType x){
	// 判满
    if(H->size == H->capacity) return 0; 
    // 已有元素个数加1
	H->size ++ ;
	// 从最小的开始遍历
    int i = H->size;
    // 先将节点插入到最后一个
	H->data[i] = x;
	// 如果遍历到最后一个，并且是其父节点小于子节点（最大堆性质被打破）
    while(i<1&&H->data[parent(i)]<H->data[i]){
        // 交换i位置和其父节点
		swap(H,i,parent(i));
		//  交换后i变为其父节点
        i = parent(i);
    }
    return 1;
}

//保持子堆性质
// 把以 i 为根的子树调整为最大堆。 已知结点 i 的左子树和右子树已经是最大堆。 
// 主要就是判断左右子树的根节点和i节点的大小,交换之后保持性质.
void heapify(Heap H,int i)
{
	int l,r;
	// 最大
	int largest;
	l=left(i);
	r=right(i);
	// 如果左子树没有满并且其值大于i节点，则最大的是左子树
	// 否则是i节点
	if(l<=H->size && H->data[l]>H->data[i])
		largest=l;
	else
		largest=i;
	// 如果右子树没有满并且其值大于最大节点值，则最大的是右子树
	if(r<=H->size && H->data[r]>H->data[largest]) 
		largest=r;
	// 如果i节点不是最大的
	// 将i节点和最大节点交换,并保持性质
	if(largest!=i)
	{
		swap(H,i,largest);
    	heapify(H,largest);
	} 	
}

// 初始化
// 该函数把data[]数组中的数据(总共n个，从data[1]到data[n])初始化最大堆。
// 此处题目给明空间足够,所以不用判断
// 该题答案包括heapify
void initHeap(Heap H, ElementType data[], int n)
{
	int i;
	// 正向将数组数值依次赋值
	for(int i=1;i<=n;i++)
		H->data[i]=data[i];;
	// 指明空间
	H->size=n;
	// 反向遍历保持性质(确保每个子树都是最大堆)
	// 注意此处从n/2开始
	for(i=n/2;i>=1;i--)
		heapify(H,i);
}

// 堆排序
// 该函数对最大堆H中的数据排序。排序后的数据仍然保留在原处。 
void heapSort(Heap H)
{
	// 获取现在堆大小,排序中间会改变大小,留着最后赋值
	int n=H->size;
	// 反向遍历
	// 此处从n开始
	for(int i=H->size;i>1;i--)
	{
		// 交换根节点和i节点
		swap(H,1,i);
		// 大小减一
		H->size--;
		// 保持性质
		heapify(H,1);
	}
	H->size=n;
}

// 销毁
// 释放指向data数组的指针
// 释放指向Heap的指针
void destroyHeap(Heap H)
{
	if(H!=NULL)
	{
		free(H->data);
		free(H);
	}
}

// 队首
// 返回索引1的data值
ElementType front(Heap H)
{
	return H->data[1];
} 

// 入队
// 已有优先队列H（最大堆），该函数将数据x入队，入队成功返回1，否则返回0。
// 和插入完全相同?
int push(Heap H,ElementType x)
{
	// 判满
	if(full(H))
		return 0;
	// 大小加一
	H->size++;
	// 大小为遍历边界
	int i=H->size;
	// 入队放在队尾
	H->data[i]=x;
	// 保持性质
	while(i>1&&H->data[parent(i)]<H->data[i])
	{
		swap(H,i,parent(i));
		i=parent(i);
	}
	return 1;
}

// 出队
// 已知优先队列H（最大堆）非空，该函数将H中的队首数据出队。 
void pop(Heap H)
{
	// 如果不空
	if(!empty(H))
	{
		// 用最后一个节点将队首覆盖
		H->data[1]=H->data[H->size];
		// 大小减一
		H->size--;
		// 保持性质
		heapify(H,1);
	}
}

int main()
{
    return 0;
}

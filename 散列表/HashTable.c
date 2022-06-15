#include <bits/stdc++.h>
using namespace std;

#define USED 1
#define EMPTY 0

typedef int ElementType;

typedef struct
{
    ElementType key; //关键数字
    int flag;        //状态标志：USED(槽已用)或EMPTY(空闲)
}Cell;

typedef struct
{
    Cell *cells;  //散列表槽指针
    int capacity; //散列表容量
    int size;     //散列表大小
}HashTable;
// 
int prime(int n)
{
	if(n==2)
		return 1;
	if(n%2==0)
		return 0;
	for(int i=3;i*i<=n;i+=2)
		if(n%i==0)
			return 0;
	return 1;
}
int nextPrime(int n)
{
	if(n%2==0)
		n++;
	while(!prime(n))
		n+=2;
	return n; 
}
//  创建
HashTable *create(int capacity)
{
	HashTable *h;
	int i;
	int k=nextPrime(capacity);
	h=(HashTable *)malloc(sizeof(HashTable));
	h->capacity=k;
	h->size=0;
	h->cells=(Cell *)malloc(sizeof(Cell)*k);
	for(i=0;i<k;i++)
		h->cells[i].flag=EMPTY;
	return h;
}

//散列函数
int hash(HashTable *h,ElementType key)
{
	return key%h->capacity;
}
// 查找
int find(HashTable *h,ElementType key)
{
	int firstpos,curpos;
	int i=0;
	firstpos=hash(h,key);
	curpos=firstpos;
	while(1)
	{
		if(h->cells[curpos].flag==EMPTY)
			break;
		if(h->cells[curpos].key==key)
			break;
		i++;
		curpos=(firstpos+i*i)%h->capacity;
	}
	return curpos;
}


//  插入1

void insert(HashTable *h,ElementType key)
{
	int pos;
	pos=find(h,key);
	if(h->cells[pos].flag==EMPTY)
	{
		h->size++;
		h->cells[pos].flag=USED;
		h->cells[pos].key=key;
	}
}



// 重散列

void rehash(HashTable *h)
{
	int i,OldSize;
	int k;
	Cell *OldCells;
	OldCells=h->cells;
	OldSize=h->capacity;
	h->capacity=nextPrime(2*h->capacity);
	k=nextPrime(2*h->capacity);
	h->cells=(Cell *)malloc(sizeof(Cell)*k);
	h->capacity=k;
	for(i=0;i<k;i++)
		h->cells[i].flag=EMPTY;
	for(i=0;i<OldSize;i++)
		if(OldCells[i].flag==USED)
			insert(h,OldCells[i].key);
	free(OldCells);
	return ;
}

// 插入2
// 该函数在散列表中插入一个key，如果key已经存在，则什么都不做。 
// 如果散列表中槽占比超过50%，则对散列表重新散列。 
void insert(HashTable *h,ElementType key)
{
	int pos;
	pos=find(h,key);
	if(h->cells[pos].flag==EMPTY)
	{
		h->size++;
		h->cells[pos].flag=USED;
		h->cells[pos].key=key;
		if(h->size>=h->capacity/2)
			rehash(h);
	}
}
// 销毁
void destroy(HashTable *h)
{
	free(h->cells);
	free(h);
}


int main()
{
    /*此处代码由测试程序自动添加，主要为了向顺序表中插入数据
	并输出数据,你无需关心此处代码的具体实现细节。
	如果有必要，请自己添加代码以测试你的函数是否正确。 
    */
    return 0;
}
/*你的提交的代码将被添加在此处，请完成题目所要求的函数的定义*/
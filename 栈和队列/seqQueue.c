typedef struct {
    ElementType *array;
    int front; // 头指针
    int rear;  // 尾指针，若队列不空，指向队列尾元素的下一个位置
    int capacity; // 容量
}SeqQueue;


int empty(SeqQueue *Q)
{
	if(Q->front==Q->rear) // 头指针和尾指针是否相同
		return 1;
	return 0;
}


int full(SeqQueue *Q)
{
	if(Q->length==Q->capacity) // 现有元素数量等于容量
		return 1;
	return 0;
}


ElementType front(SeqQueue *Q)
{
	return Q->array[Q->front];
}


int push(SeqQueue *Q,ElementType x)
{
	if(full(Q))
		return 0;
	Q->array[Q->rear]=x; // 将x赋值给队列尾部的元素
	Q->rear=(Q->rear+1)%Q->capacity; // rear指针向后移动一位，如果超出容量就转到数组头部
	Q->length++; // 现有元素数量加1
	return 1;
}

int pop(SeqQueue *Q,ElementType *x)
{
	if(Q->length==0) return 0; // 队列现在是否有元素
	*x=Q->array[Q->front]; // 将队列头元素赋值给x 同取出队首数据
	Q->front=(Q->front+1)%Q->capacity; // front指针向后移动一个位置，如果到最后则转到数组头部
	Q->length--;// 现有元素数量减1
	return 1;
} 

void clearQueue(SeqQueue *Q)
{
	Q->front=0; 
	Q->rear=0;
	Q->length=0;
}


void destroyQueue(SeqQueue *Q)
{
	if(Q!=NULL)
	{
		free(Q->array);
		free(Q);
	}
}







typedef struct {
    ElementType *array;// 存放元素的数组
    int length;// 已经有多少个元素
    int capacity;//容量
}SeqList;



int isEmpty(SeqList *L){
	if (L->length == 0){
		return 1;
	}
	return 0;
}



void printList(SeqList *L){
	int i = 0;
	for (i =0;i<L->length;i++){
		printf("%d ",L->array[i]);
	}
	printf("\n");
}

int getLength(SeqList *L){
	return L->length;
}

int insertList(SeqList *L, int i, ElementType x){
	if (L->length>=L->capacity){//判断长度是否大于容量，大于代表顺序表已满
		return 0;
	}
	if (i<1||i>L->length+1){// 因为索引为位置-1，所以位置的范围为[1，length]，则索引不合法
		return 0;
	}
	int k;
	for (k=L->length-1;k>=i-1;k--){// 将从插入位置到结束的元素反向遍历
		L->array[k+1] = L->array[k];// 将每个元素都向后移动一位
	}
	L->array[i-1] =x;//插入元素
	L->length++;// 插入一个元素之后长度加1
	return 1;
}

int find(SeqList *L, ElementType x){
	int i ;
	for(i=0;i<L->length;i++){
		if (L->array[i] == x) return i+1;
	}
	return -1;
}


int getElement(SeqList *L, int i, ElementType *p){
	if (i<1||i>L->length) return 0;// 判断索引是否合法
	*p = L->array[i-1];// 用p指向需要的数据
	return 1;
}



int delElement(SeqList *L, int i, ElementType *p){
	if (i<1||i>L->length){
		return 0;
	}// 判断索引是否合法
	int k;
	*p = L->array[i-1]; // 用p指向要删除的元素
	for (k=i;k<L->length;k++){
		L->array[k-1] = L->array[k];// 从要删除的元素的后一个元素开始，将每个元素指向后一个元素
	}
	L->length--;// 删除一个元素，length-1 ，length为先有元素个数
	return 1;
}

void delRepeatElement(SeqList *L){
	int i=0,j=1;
    int leng=1;// 用于记录
	while(j<L->length){// 遍历每个数据
		for(i=0;i<leng;++i){// 从0遍历到leng直接的所有元素
			if (L->array[i]==L->array[j]) break;// 出现相同时跳出循环
		}
		if (i==leng) { // 如果i==leng 将该i位的元素赋值为当前元素的后一个元素
			L->array[leng++]=L->array[j++];} // ++ 是因为i和leng
		else { 
			j++;} // 如果i!= leng 则判断下一个元素
	}
	L->length = leng;
	
}

void clearList(SeqList *L){
	L->length=0;//清除就是将现有元素个数置为0
}



void mergeList(SeqList *LA, SeqList *LB, SeqList *LC){
	int i =0, j =0, k =0;
	while(i<LA->length&&j<LB->length){
        // 将LA当前元素和LB当前元素较小的一个存入LC
		if((LA->array[i]<=LB->array[j])){
			LC->array[k++]=LA->array[i++];
		}
		else {
            LC->array[k++] = LB->array[j++];
        }
    }
    // 将剩下的元素存入LC 
    // 注意该部分的k++是先进行赋值运算之后再自己增加1
	while (i<LA->length){
		LC->array[k++]= LA->array[i++];
	}
	while (j<LB->length){
		LC->array[k++]=LB->array[j++];
	}
	LC->length = k;
}

void destroyList(SeqList *L){
	free(L->array);// 释放指向存放数组的指针
}







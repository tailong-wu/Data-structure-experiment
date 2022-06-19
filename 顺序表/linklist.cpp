typedef struct Node{
    ElementType data;
    struct Node *next;
}Node,*LinkList;


int getLength(LinkList L){
	int len =0;
	while (L->next){// 直到最后一个节点，也就是next为空
		len++;
		L=L->next;// 指向下一个
	}
	return len;
}

void printList(LinkList L){
	struct Node *p;
	p =L->next;// 使用node数据结构来存放每个节点的next指针
	while (p!=NULL){
		printf("%d ",p->data);// 读取该节点的数据
		p= p->next;// 指向下一个节点
	}
	printf("\n");
}


void insertHead(LinkList L, ElementType x){
	Node *s;// 初始化node指针 
	s = (Node *)malloc(sizeof (Node));// 初始化内存
	s->data=x;//存放数据，x为输入
	s->next = L->next;// s的next取代L的next
	L->next=s;// 并将L的next指向s
}

void insertTail(LinkList  L, ElementType x){
	Node *p;
	p = (Node *) malloc (sizeof(Node));
	p->data = x;
	while(L->next!=NULL){
		L=L->next;
	}
	L->next = p;
}


int insertList(LinkList L,int i,ElementType x)
{
	int cnt=0;// cnt 用于
	if(i<1) return 0; // 判断位置是否合法
	Node *pre=NULL;
	for(pre=L;pre!=NULL;pre=pre->next)// 遍历链表
	{
		if(cnt==i-1)// 当索引匹配位置时break
			break;
		cnt++;
	}
	if(pre==NULL) return 0;// 如果前一个为NULL，那么该位置不在单链表内，位置不合法
	Node *p=(Node *)malloc(sizeof(Node));// 合法，就分配内存，同在头部插入数据。
	p->data=x;
	p->next=pre->next;
	pre->next=p;
	return 1;
}



void destroyList(LinkList L)
{
	LinkList q,p=L; //  p,q初始化为LinkList
	while(p!=0){// 遍历每一个链表指针
 		q=p->next; // 将next结点赋值给q
 		delete p;// 删除p结点
 		p=q; // 重新赋值
 	}
 	L=NULL;// 最终令L=NULL，即开头结点为NULL
}
void destroyList(LinkList L){
	Node *p;
	p = (Node*)malloc(sizeof(Node));
	while(L->next!=NULL){
		p = L->next;
		free(L);
		L = L->next;
	}
	free(L);
}



void clearList(LinkList L){
	Node *p,*t;
	p = L->next;// p保存下一个结点
	while (p!=NULL){// 遍历到最后一个结点
		t = p->next;// t暂时保存下一个结点
		free(p);// 释放p结点
		p = t;//重新赋值
	}
	L->next = NULL;// 将开头指针的next设置为NULL
}


Node *find(LinkList L,ElementType x){
	Node *p=L->next;// 指向下一个的指针
	while(p!=NULL && p->data != x){ // 遍历到最后或者出现输入的数据
		p = p->next;// 更新指针
	}
	return p;
}
Node* find(LinkList L, ElementType x){
	while (L->next!=NULL){
		if (L->data == x) return L;
		L=L->next;
	}
	return NULL;
}



Node* locate(LinkList L, int i){
	int cnt = 0;
	if (i<1) return NULL;// 索引合法性判断
	for (Node *p = L->next;p!=NULL;p=p->next)// 根据索引的遍历
	{
		cnt ++;//索引增加
		if (cnt==i) return p;// 索引相同则返回
	}
	return NULL;
}

// 删除对应数据结点
int delNode(LinkList L,ElementType x){
	Node *p,*pre;
	pre = L;// 第一个结点
	p = L->next;// 第二个结点
	while (p!= NULL && p->data !=x){// 遍历到发现该数据或者到达最后一个结点
		pre = p;
		p = p->next;
	}
	if (p==NULL) return 0;// 如果遍历到最后一个结点依然没有找到该数据则认定数据没有
	pre->next = p->next;// 将前一个结点的next换为要被删除结点的next
	free(p);// 并释放删除结点的指针
	return 1;}
int delNode(LinkList L, ElementType x){
	Node *p,*pre;
	pre = L;
	p = L->next;
	while(p!=NULL){
		if(p->data == x) {
			pre->next = p->next;
			free(p);
			return 1;
		}
		pre = p;
		p=p->next;
	}
	return 0;
}


// 删除索引的结点


int delNode (LinkList L,int i ,ElementType *px){
	int cnt = 1; 
	if (i<1) return 0; //检查位置合理
	Node *pre = L; //存储前一个结点
	Node *p = L->next; //存储后一个结点
	while (p!= NULL){     //遍历到最后一个结点
		if (cnt == i) break; //当索引相同的时候推出
		pre = p; //没到达指定索引 ，就继续存储之后的结点
		p = p->next;
		cnt ++;
	}
	if (p ==NULL) return 0;  //检测是否是最后一个结点
	//删除和前面的一样，将上下文指针链接，之后释放该结点
  	pre->next = p->next; 
	*px = p ->data;
	free(p);
	return 1;
}
int delNode(LinkList L, int i, ElementType *px){
	int k=0;
	Node *p ,*pre;
	pre = L;
	p = L->next;
	while(p!=NULL){
		k++;
		if (k==i){
			*px  = p->data;
			pre->next = p->next;
			free(p);
			return 1;
		}
		pre = p;
		p = p->next;
	}
	return 0;
}





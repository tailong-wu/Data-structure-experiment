void preOrder(BTree root)
{
	if(root==NULL)
		return;
	printf("%c",root->data);//  显示结点数据
	preOrder(root->lchild); // 先 前序遍历左子树
	preOrder(root->rchild); // 再 前序遍历右子树
}


void inOrder(BTree root)
{
	if(root==NULL)
		return;
	inOrder(root->lchild);
	printf("%c",root->data);// 中
	inOrder(root->rchild);
}



void postOrder(BTree root)
{
	if(root==NULL)
		return;
	postOrder(root->lchild);
	postOrder(root->rchild);
	printf("%c",root->data);
}


void layerOrder(BTree rt)
{
	BTree t;// 创建一个树结点
	queue<BTree>q; // 创建一个队列
	q.push(rt); // 将根结点放到队列中
	while(!q.empty()) // 只要队列不空就继续执行
	{
		t=q.front(); // 取出队头的树节点
		q.pop(); // 取出之后pop掉
		printf("%c",t->data); // 输出data
		if(t->lchild!=NULL) // 如果左结点不为空，则将左结点存储到队列最后
			q.push(t->lchild);
		if(t->rchild!=NULL) // 同左结点
			q.push(t->rchild);
	}
 } 


 void printTree(BTree bt)
{
	if(bt!=NULL)// 只要bt不是空 就一直递归输出下去 
	{
		printf("%c",bt->data); // 输出数据
		if(bt->lchild!=NULL || bt->rchild!=NULL) // 只要左右子树不是空，就递归输出
		{
            // （左结点，右结点）
			printf("(");  // 先输入左括号
			printTree(bt->lchild); // 递归输出左结点
			printf(","); // 逗号分隔
			printTree(bt->rchild); // 递归输出右结点
			printf(")");  // 右括号结束
		}
	}
}




void destroyTree(BTree bt)
{
	if(bt==NULL) 
		return;
	destroyTree(bt->lchild);
	destroyTree(bt->rchild);
	free(bt);
}





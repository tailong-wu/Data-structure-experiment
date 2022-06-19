typedef int ElementType;
typedef  struct  Node{
	ElementType  data;
	struct Node  *lchild;
	struct Node  *rchild;
}BSTNode, *BSTree;



void inOrder(BSTree bst)
{
	if(bst!=NULL)
	{
		inOrder(bst->lchild);
		printf("%d ",bst->data);
		inOrder(bst->rchild);
	}
}


BSTNode* findMin(BSTree bst){
    if(bst==NULL) return NULL;
    while (bst->lchild!=NULL){
        bst = bst->lchild;
    }
    return bst;
}


BSTNode* findMax(BSTree bst){
    if (bst==NULL) return NULL;
    while (bst->rchild!=NULL) bst= bst->rchild;
    return bst;
}


BSTNode* find(BSTree bst, ElementType x){
    while(bst!=NULL){
        if (x<bst->data) bst= bst->lchild;
        else if(x>bst->data) bst = bst->rchild;
        else if(x==bst->data) return bst;
    }
    return NULL;
}

BSTree deleteNode(BSTree bst,ElementType x)
{
	BSTNode *p;
	if(bst==NULL)
		return bst;
	if(x<bst->data)
		bst->lchild=deleteNode(bst->lchild,x);
	else if(x>bst->data)
		bst->rchild=deleteNode(bst->rchild,x);
	else // 该分支是等于的情况
	{
		if(bst->lchild!=NULL && bst->rchild!=NULL)
		{
			p=findMin(bst->rchild);
			bst->data=p->data;
			bst->rchild=deleteNode(bst->rchild,bst->data);
		}
		else
		{
			p=bst;
			if(bst->lchild==NULL)
				bst=bst->rchild;
			else if(bst->rchild==NULL)
			{
				bst=bst->lchild;
			}
			free(p);
		}
	
	}
		return bst;
}



BSTree destroyBSTree(BSTree bst)
{
 if(bst==0)
  return NULL;
 destroyBSTree(bst->lchild);
 destroyBSTree(bst->rchild);
 free(bst);
}



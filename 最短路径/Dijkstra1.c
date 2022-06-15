#include<bits/stdc++.h>
using namespace std;

#define MAXVEX 200 //最大顶点数
typedef char VertexType;

typedef struct ENode
{
    int adjVertex;  //该边所指的顶点编号
    int weight;     //边权
    struct ENode *nextEdge;  //下一条边
} ENode;

typedef struct VNode
{
    VertexType data;   //顶点信息
    int visited; //遍历标记. 1:已遍历  0:未遍历
    ENode *firstEdge; //第一条出边
} VNode;

typedef struct
{
    VNode vexs[MAXVEX];
    int vertexNum,edgeNum; //点数和边数
}AdjGraph,*Graph;

void Dijkstra(Graph g, int s, int D[], int P[]);

int main()
{
    /*此处代码由测试程序自动添加，主要为了向顺序表中插入数据
	并输出数据,你无需关心此处代码的具体实现细节。
	如果有必要，请自己添加代码以测试你的函数是否正确。 
    */
    return 0;
}
/*你的提交的代码将被添加在此处，请完成题目所要求的函数的定义*/

int findMin(Graph g,int D[])
{
	int k=-1;
	int min=INT_MAX;
	for(int i=0; i<g->vertexNum ;i++)
		if(g->vexs[i].visited==0 && min>D[i])
		{
			min=D[i];
			k=i;
		}
	return k;
}
void Dijkstra(Graph g, int s, int D[], int P[])
{
	int i,k;
	ENode *p;
	for(i=0;i<g->vertexNum;i++)
	{
		D[i]=INT_MAX;
		g->vexs[i].visited=0;
	}
	for(p=g->vexs[s].firstEdge;p!=NULL;p=p->nextEdge)
	{
		D[p->adjVertex]=p->weight;
		P[p->adjVertex]=s;
	}
	D[s]=0;
	g->vexs[s].visited=1;
	while(1)
	{
		k=findMin(g,D);
		if(k==-1)
			return;
		g->vexs[k].visited=1;
		for(p=g->vexs[k].firstEdge;p!=NULL; p=p->nextEdge)
			if(g->vexs[p->adjVertex].visited==0 && D[p->adjVertex]>D[k]+p->weight)
			{
				D[p->adjVertex]=D[k]+p->weight;
				P[p->adjVertex]=k;
			}
	} 
}

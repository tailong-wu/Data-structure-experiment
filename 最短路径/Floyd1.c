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





// 请设计void Floyd(Graph g, int D[][MAXVEX], int P[][MAXVEX])函数。 
// 该函数用Floyd算法计算图中任意两个顶点之间的最短路径长度及最短路径。 如果顶点不可达，则最短路径长度为INT_MAX。 
// 数组D[]记录对应顶点之间的最短距离的权(i到i的最短路径长度为0) 
// 数组P[]记录对应顶点之间的最短路径上的前驱(终点的前驱，特别的i到i的前驱为i)。

void Floyd (Graph g,int D[][MAXVEX],int P[][MAXVEX])
{
	int i,j,k,n;
	n=g->vertexNum;
	ENode *p;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			D[i][j]=INT_MAX;
		D[i][i]=0;
		P[i][i]=i;
	}
	for(i=0;i<n;i++)
		for(p=g->vexs[i].firstEdge;p!=NULL;p=p->nextEdge)
		{
			D[i][p->adjVertex]=p->weight;
			P[i][p->adjVertex]=i;
		}
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
		{
			if(i==k ||D[i][k]==INT_MAX)
				continue;
			for(j=0;j<n;j++)
			{
				if(j==k || i==j || D[k][j]==INT_MAX)
					continue;
				if(D[i][j]>D[i][k]+D[k][j])
				{
					D[i][j]=D[i][k]+D[k][j];
					P[i][j]=P[k][j];
				}
			}
		}
	
}





int main()
{
    return 0;
}

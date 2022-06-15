#include<bits/stdc++.h>
using namespace std;

#define MAXVEX 100
typedef char VertexType;
typedef int EdgeType;
typedef struct
{
    VertexType vexs[MAXVEX]; //顶点表
    EdgeType edge[MAXVEX][MAXVEX]; //邻接矩阵,即边表
    int vertexNum,edgeNum;
} MGraph,*Graph;

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


int findMin(Graph g, int D[],int final[])
{
	int min=INT_MAX;
	int k=-1;
	for(int i=0; i<g->vertexNum ;i++)
		if(final[i]==0 && min>D[i])
		{
			min=D[i];
			k=i;
		}
	return k;
}
void Dijkstra(Graph g, int s, int D[], int P[])
{
	int final[MAXVEX];
	int i,k;
	for(i=0; i<g->vertexNum ;i++)
	{
		final[i]=0;
		D[i]=g->edge[s][i];
		if(D[i]<INT_MAX)
			P[i]=s;
	}
	P[s]=s;
	final[s]=1;
	D[s]=0;
	while(1)
	{
		k=findMin(g,D,final);
		if(k==-1)
			return;
		final[k]=1;
		for(i=0 ;i<g->vertexNum ;i++)
		{
			if(g->edge[k][i]==INT_MAX || final[i])
				continue;
			if(D[i]>D[k]+g->edge[k][i])
			{
				D[i]=D[k]+g->edge[k][i];
				P[i]=k;
			}
		}
	}
}
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

void Floyd(Graph g, int D[][MAXVEX], int P[][MAXVEX]){
	int i,j,k;
	for(i=0;i< g->vertexNum ; i++)
	{
		for(j=0;j<g->vertexNum ;j++)
		{
			D[i][j]=g->edge[i][j];
			P[i][j]=i;
		}
		D[i][i]=0;
	}
	for(k=0; k< g->vertexNum ;k++)
		for(i=0; i< g->vertexNum ;i++)
		{
			if(D[i][k]==INT_MAX || i==k)
				continue;
			for(j=0;j<g->vertexNum;j++){
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
    /*此处代码由测试程序自动添加，主要为了向顺序表中插入数据
	并输出数据,你无需关心此处代码的具体实现细节。
	如果有必要，请自己添加代码以测试你的函数是否正确。 
    */
    return 0;
}
/*你的提交的代码将被添加在此处，请完成题目所要求的函数的定义*/
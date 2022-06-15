#include<bits/stdc++.h>
using namespace std;

#define MAXVEX 100
typedef char VertexType;
typedef int EdgeType;
typedef struct {
    VertexType vexs[MAXVEX]; //顶点表
    EdgeType edge[MAXVEX][MAXVEX]; //邻接矩阵,即边表
    int vertexNum,edgeNum;
}MGraph,*Graph;
// 创建图
Graph createGraph()
{
	Graph g=(Graph)malloc(sizeof(MGraph));
	g->edgeNum =0;
	g->vertexNum =0;
	return g;
}
// 查找顶点
int locateVertex(Graph g,VertexType v)
{
	int i;
	for(i=0;i<g->vertexNum ;i++)
		if(g->vexs[i]==v)
			return i;
	return -1;
}

// 增加边
void addVertex(Graph g,VertexType v)
{
	int k=locateVertex(g,v);
	if(k!=-1)
		return ;
	k=g->vertexNum ;
	g->vexs [k]=v;
	g->vertexNum ++;
	for(int i=0;i<g->vertexNum ;i++)
	{
		g->edge [i][k]=0;
		g->edge [k][i]=0;
	}
}
// 增加边
void addEdge(Graph g, VertexType x, VertexType y)
{
	int i,j;
	i=locateVertex(g,x);
	j=locateVertex(g,y);
	if(i!=-1 && j!=-1 && i!=j)
		if(g->edge[i][j]==0)
		{
			g->edge[i][j]=g->edge[j][i]=1;
			g->edgeNum++;
		}
}
// 删除顶点
void delVertex(Graph g,VertexType v)
{
	int k,n;
	k=locateVertex(g,v);
	if(k==-1)
		return ;
	n=g->vertexNum-1;
	g->vexs[k]=g->vexs[n];
	for(int i=0;i<g->vertexNum;i++)
	{
		if(g->edge[i][k]==1)
			g->edgeNum--;
		g->edge[i][k]=g->edge[i][n];
	}
	for(int i=0;i<g->vertexNum;i++)
		g->edge[k][i]=g->edge[n][i];
	g->vertexNum--;
}

// 删除边

void delEdge(Graph g,VertexType x,VertexType y)
{
	int i,j;
	i=locateVertex(g,x);
	j=locateVertex(g,y);
	if(i!=-1 && j!=-1){
		if(g->edge[i][j]==1){
			g->edge[i][j]=g->edge[j][i]=0;
			g->edgeNum--;
		}
	}
}

// 顶点的度
int degree(Graph g,VertexType v)
{
	int k,d;
	k=locateVertex(g,v);
	d=0;
	for(int i=0;i<g->vertexNum;i++)
		if(g->edge[k][i]==1)
			d++;
	return d;
}

// 深度优先遍历
void DFS(Graph g,int i)
{
	if(i>=g->vertexNum)
		return ;
	g->visited[i]=1;
	for(int j=0;j<g->vertexNum;j++)
		if(g->edge[i][j]==1 && g->visited[j]==0)
			DFS(g,j);
}

// 广度优先遍历
void BFS(Graph g,int i)
{
	if(i>=g->vertexNum)
		return ;
	queue<int>q;
	int v,j;
	g->visited[i]=1;
	q.push(i);
	while(!q.empty())
	{
		v=q.front();
		q.pop();
		for(j=0;j<g->vertexNum;j++)
			if(g->edge[v][j]==1)
				if(g->visited[j]==0)
				{
					g->visited[j]=1;
					q.push(j);
				}
	}
}
// 销毁
void destroyGraph(Graph g)
{
	free(g);
}

// 距离
int distance(Graph g,VertexType v, VertexType u)
{
	int x=locateVertex(g,v);
	int y=locateVertex(g,u);
	int i,j;
	int dis[g->vertexNum-1];
	if(i==-1 || j== -1)
		return 0;
	for(i=0;i< g->vertexNum ;i++)
	{
		dis[i]=0;
		g->visited[i]=0;
	}
	g->visited[x]=1;
	queue<int> Q;
	Q.push(x);
	while(!Q.empty())
	{
		i=Q.front();
		Q.pop();
		for(j=0; j<g->vertexNum ;j++)
			if(g->edge[i][j]==1)
				if(g->visited[j]==0)
				{
					g->visited[j]=1;
					Q.push(j);
					dis[j]=dis[i]+1;
				}
			
	}	
	return dis[y];
}

// 连通分支数
int connectedComps(Graph g)
{
	int i;
	int p=0;
	for(i=0;i< g->vertexNum ;i++)
		if(g->visited[i]==0)
		{
			DFS(g,i);
			p++;
		}
	return p;
}
// 连通
int connect(Graph g, VertexType v, VertexType u)
{
	int i=locateVertex(g,v);
	int j=locateVertex(g,u);
	if(i== -1 || j== -1)
		return 0;
	DFS(g,i);
	return g->visited[j];
}

int main()
{
    return 0;
}

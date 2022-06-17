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
	// 分配内存
	Graph g=(Graph)malloc(sizeof(MGraph));
	// 边个数为零
	g->edgeNum =0;
	// 点个数为0
	g->vertexNum =0;
	return g;
}
// 查找顶点
int locateVertex(Graph g,VertexType v)
{
	int i;
	for(i=0;i<g->vertexNum ;i++)
	//  判断
		if(g->vexs[i]==v)
			return i;
	return -1;
}

// 增加顶点
void addVertex(Graph g,VertexType v)
{
	// 定位顶点位置
	int k=locateVertex(g,v);
	// 定点存在返回空
	if(k!=-1)
		return ;
	// 顶点不存在 将顶点存入数组最后一位
	k=g->vertexNum ;
	g->vexs [k]=v;
	g->vertexNum ++;
	// 遍历每个顶点 ，到新增点的边为0
	for(int i=0;i<g->vertexNum ;i++)
	{
		g->edge [i][k]=0;
		g->edge [k][i]=0;
	}
}
// 增加边
void addEdge(Graph g, VertexType x, VertexType y)
{
	// 定位两个顶点
	int i,j;
	i=locateVertex(g,x);
	j=locateVertex(g,y);
	// 两个顶点存在 且不是同一个点 
	if(i!=-1 && j!=-1 && i!=j)
		// i 到j 之间没有边
		if(g->edge[i][j]==0)
		{
			// 将该边赋值为1 
			g->edge[i][j]=g->edge[j][i]=1;
			// 增加边个数
			g->edgeNum++;
		}
}


// 删除顶点
void delVertex(Graph g,VertexType v)
{
	int k,n;
	k=locateVertex(g,v);
	// 顶点不存在返回空
	if(k==-1)
		return ;
	// 将最后一个点用倒数第二个点覆盖
	n=g->vertexNum-1;
	g->vexs[k]=g->vexs[n];
	// 遍历所有顶点
	for(int i=0;i<g->vertexNum;i++)
	{
		// 删除边
		if(g->edge[i][k]==1)
			g->edgeNum--;
		// 使用倒数第二个点连接的边覆盖
		g->edge[i][k]=g->edge[i][n];
		g->edge[k][i]=g->edge[n][i];
	}
	// 顶点数量减一
	g->vertexNum--;
}

// 删除边

void delEdge(Graph g,VertexType x,VertexType y)
{
	// 定位顶点
	int i,j;
	i=locateVertex(g,x);
	j=locateVertex(g,y);
	// 两顶点存在
	if(i!=-1 && j!=-1){
		// 两顶点直接的边存在
		if(g->edge[i][j]==1){
			// 改为0
			g->edge[i][j]=g->edge[j][i]=0;
			g->edgeNum--;
		}
	}
}

// 顶点的度
// 度就是连接到该顶点的边个数
int degree(Graph g,VertexType v)
{
	// 定位顶点
	int k,d;
	k=locateVertex(g,v);
	d=0;
	// 遍历所有边,存在连接则加1
	for(int i=0;i<g->vertexNum;i++)
		if(g->edge[k][i]==1)
			d++;
	return d;
}

// 深度优先遍历
// 该函数从序号为i的顶点开始深度优先遍历图G(已遍历的点visited值标记为1)。 
// 已知未遍历的点visited值标记为0. 
// 目标就是把所有的顶点的visited都变为1
void DFS(Graph g,int i)
{
	// 如果i的个数大于顶点数,则初始点不存在
	if(i>=g->vertexNum)
		return ;
	// 第一个点为1
	g->visited[i]=1;
	// 遍历所有点,如果该点没被遍历过,并且与上一个遍历的点连接 则进入递归
	for(int j=0;j<g->vertexNum;j++)
		if(g->edge[i][j]==1 && g->visited[j]==0)
			DFS(g,j);
}

// 广度优先遍历
void BFS(Graph g,int i)
{
	if(i>=g->vertexNum)
		return ;
	// 队列q
	queue<int>q;
	int v,j;
	// 初始点存在就访问了
	g->visited[i]=1;
	// 初始点入队
	q.push(i);
	// 只要队列非空就继续运行
	while(!q.empty())
	{
		// 取出队首
		v=q.front();
		q.pop();
		// 遍历所有顶点 只要不被v连接 就入队,并被visited
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
	// 释放指向g的指针
	free(g);
}

// 距离
// 该函数返回图中两个顶点v和w之间的距离(最短连通路上边的数目)。提示：连通返回距离，不连通返回0。
int distance(Graph g,VertexType v, VertexType u)
{
	// 取出两个点索引
	int x=locateVertex(g,v);
	int y=locateVertex(g,u);
	int i,j;
	// 为啥num-1,因为不会求自己到自己的距离
	int dis[g->vertexNum-1];
	// 两顶点不存在,则不连通
	if(i==-1 || j== -1)
		return 0;
	// 初始化dis数组为全0
	// 每个顶点的visited为0
	for(i=0;i< g->vertexNum ;i++)
	{
		dis[i]=0;
		g->visited[i]=0;
	}
	// 之后同广度优先遍历 就是在每次访问新顶点时,距离加一并存储
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
					// 基于到上个顶点的距离加1
					dis[j]=dis[i]+1;
				}
			
	}
	// 返回dis对应后一个点的距离
	return dis[y];
}


// 连通分支数
// 不重复广度优先遍历 走几次能走完
int connectedComps(Graph g)
{
	int i;
	int p=0;
	// 遍历每个顶点
	// 如果顶点没有被遍历过 进入广度遍历 每次加一
	for(i=0;i< g->vertexNum ;i++)
		if(g->visited[i]==0)
		{
			DFS(g,i);
			p++;
		}
	return p;
}

// 连通
// 该函数判断图中两个顶点v和w是否连通，连通返回1，不连通返回0。
int connect(Graph g, VertexType v, VertexType u)
{
	// 获取两个顶点索引
	int i=locateVertex(g,v);
	int j=locateVertex(g,u);
	// 两个点其中一个不存在 return 0
	if(i== -1 || j== -1)
		return 0;
	// 广度优先遍历 前一个结点
	DFS(g,i);
	// 返回能够j是否被visited
	return g->visited[j];
}



int main()
{
    return 0;
}

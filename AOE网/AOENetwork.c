#include<bits/stdc++.h>
using namespace std;

#define MAXVEX 100 /*最大顶点数*/
typedef char VertexType;

struct AOENetworkStruct;
typedef struct AOENetworkStruct *AOENetwork;

typedef struct ENode
{
    int adjVertex;  //边的终点编号
    int weight;     //边权
    int earliest;   //活动最早开始时间
    int latest;     //活动最晚开始时间
    struct ENode *nextEdge;  //下一条边
} ENode;

typedef struct VNode
{
    VertexType data;    //顶点信息/
    int inDegree;       //入度/
    int earliest;       //事件最早发生时间/
    int latest;         //事件最晚发生时间
    ENode *firstEdge; //第一条出边
} VNode;

struct AOENetworkStruct
{
    VNode vexs[MAXVEX];    //点表
    int vertexNum, edgeNum; //顶点数和弧数
};
// 创建
AOENetwork createGraph(){
    AOENetworkStruct *g=(AOENetwork)malloc(sizeof(AOENetworkStruct));
	g->vertexNum =0;
	g->edgeNum =0;
	return g;
}

// 查找顶点
// 根据数据查找
int locateVertex(AOENetwork g,VertexType v)
{
	int i;
	for(i=0;i<g->vertexNum;i++)
		if(v==g->vexs[i].data)
			return i;
	return -1;
} 
// 插入顶点
// AOE中的顶点多几个属性 
// data为给定值v
// firstEdge NULL
// inDegree 0
// 
void addVertex(AOENetwork g,VertexType v)
{
	int k,n;
	k=locateVertex(g,v);
	if(k!=-1)
		return;
	n=g->vertexNum;
	g->vexs[n].data=v;
	g->vexs[n].firstEdge=NULL;
	g->vexs[n].inDegree=0;
	g->vertexNum++;
}
// 查找边
ENode *findEdge(AOENetwork g,int i,int j)
{
	ENode *p=NULL;
	for(p=g->vexs[i].firstEdge;p!=NULL;p=p->nextEdge)
		if(p->adjVertex==j)
			return p;
	return NULL;
}
// 插入边
void addEdge(AOENetwork g, VertexType v1, VertexType v2, int w)
{
	int i=locateVertex(g,v1);
	int j=locateVertex(g,v2);
	ENode *p;
	if(i==-1 || j==-1)
		return;
	p=findEdge(g,i,j);
	if(p!=NULL)
        {
		if(p->weight>w) 
                 {
			p->weight=w;
		}
	}
	else{
		p=(ENode*)malloc(sizeof(ENode));
		p->adjVertex=j;
		p->earliest=p->latest=0;
		p->weight=w;
		p->nextEdge=g->vexs[i].firstEdge;
		g->vexs[i].firstEdge=p;
		g->vexs[j].inDegree++;
	}
}
// 最早发生时间
int TopSort(AOENetwork g)
{
	int count=0;
	int x,y;
	ENode *p=NULL;
	stack<int>in;
	for(int i=0;i<g->vertexNum;i++)
		if(g->vexs[i].inDegree==0)
			in.push(i);
	while(!in.empty())
	{
		x=in.top();
		in.pop();
		count++;
		for(p=g->vexs[x].firstEdge;p!=NULL;p=p->nextEdge)
		{
			y=p->adjVertex;
			g->vexs[y].inDegree--;
			if(g->vexs[y].inDegree==0)
				in.push(y);
			if(g->vexs[y].earliest<g->vexs[x].earliest+p->weight)
				g->vexs[y].earliest=g->vexs[x].earliest+p->weight;
		}
	}
	if(count<g->vertexNum)
		return 0;
	return 1;
}

// 事件发生时间
void event(AOENetwork g)
{
	int i,x,y;
	ENode *p;
	stack<int>out;
	if(!TopSort(g,out))
		return ;
	for(i=0;i<g->vertexNum;i++)
		g->vexs[i].latest=g->vexs[g->vertexNum-1].earliest;
	while(!out.empty())
	{
		x=out.top();
		out.pop();
		for(p=g->vexs[x].firstEdge;p!=NULL;p=p->nextEdge)
		{
			y=p->adjVertex;
			if(g->vexs[x].latest>g->vexs[y].latest-p->weight)
				g->vexs[x].latest=g->vexs[y].latest-p->weight;
		}
	}
}

// 活动时间
int active(AOENetwork g)
{
	int x,y;
	ENode *p;
	int cnt=0;
	for(x=0;x<g->vertexNum;x++)
		for(p=g->vexs[x].firstEdge;p!=NULL;p=p->nextEdge)
		{
			y=p->adjVertex;
			p->earliest=g->vexs[x].earliest;
			p->latest=g->vexs[y].latest-p->weight;
			if(p->earliest==p->latest)
				cnt++;
		}
	return cnt;
}


// 关键路径
int DFS (AOENetwork g,int v)
{
	int i,sum=0;
	ENode *p;
	if(v==g->vertexNum-1)
		return 1;
	for(p=g->vexs[v].firstEdge ;p!=NULL ;p=p->nextEdge)
		if(p->earliest==p->latest)
			sum+=DFS(g,p->adjVertex);
	return sum;
} 
int pathNum(AOENetwork g)
{
	return DFS(g,0);
}
// AOE网
void criticalPath(AOENetwork g)
{
	int x,y;
	ENode *p;
	event(g);
	for(x=0;x<g->vertexNum ;x++)
		for(p=g->vexs[x].firstEdge ;p!=NULL ;p=p->nextEdge)
		{
			y=p->adjVertex;
			p->earliest=g->vexs[x].earliest;
			p->latest=g->vexs[y].latest-p->weight;
		}
} 
int main()
{
	AOENetwork g;
	int i,n,m;
	char str,edge[MAXVEX];
	scanf("%d",&n);
	getchar();
	g=createGraph();
	for(i=0;i<n;i++)
	{
		scanf("%c",&str);
		addVertex(g,str);
	}
	while(1)
	{
		scanf("%s",edge);
		if(strcmp(edge,"00")==0)
			break;
		scanf("%d",&m);
		addEdge(g,edge[0],edge[1],m);
	}
	criticalPath(g);
	printf("%d\n",pathNum(g));
	return 0;
}


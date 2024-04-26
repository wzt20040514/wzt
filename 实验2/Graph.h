#ifndef GRAPH_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
struct Vex {
	int num;//景点编号
	char name[20];//景点名字
	char desc[1024];//景点介绍
};
struct Edge {
	int vex1;//边的第一个顶点
	int vex2;//边的第二个顶点
	int weight;//权值
};
struct CGraph {
	int m_aAdjMatrix[20][20];//邻接矩阵
	Vex m_aVexs[20];//顶点信息数组
	int m_nVexNum;//当前图的顶点个数
};
typedef struct Path {
	int vexs[20];
	Path* next;
}*PathList;
void Init(void);
bool InsertVex(Vex sVex);
bool InsertEdge(Edge sEdge);
Vex GetVex(int v);
int FindEdge(int v, Edge aEdge[]);
void DFS(int nVex, bool bVisited[], int& nIndex, PathList& pList);
void DFSTraverse(int nVex, PathList& pList);
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
int FindminTree(int nStart, Edge aEdge[]);
#endif
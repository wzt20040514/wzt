#ifndef GRAPH_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
struct Vex {
	int num;//������
	char name[20];//��������
	char desc[1024];//�������
};
struct Edge {
	int vex1;//�ߵĵ�һ������
	int vex2;//�ߵĵڶ�������
	int weight;//Ȩֵ
};
struct CGraph {
	int m_aAdjMatrix[20][20];//�ڽӾ���
	Vex m_aVexs[20];//������Ϣ����
	int m_nVexNum;//��ǰͼ�Ķ������
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
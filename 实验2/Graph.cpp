#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;
const double INF = 1e9; // 定义无穷大为1e9
CGraph m_Graph;
void Init(void)
{
    m_Graph.m_nVexNum = 0;
    int i;
    for (i = 0; i < 20; i++)
    {
        m_Graph.m_aVexs[i].num = -1;
        strcpy(m_Graph.m_aVexs[i].name, "");
        strcpy(m_Graph.m_aVexs[i].desc, "");
        for (int j = 0; j < 20; j++)
            m_Graph.m_aAdjMatrix[i][j] = 0;

    }
}
//插入点
bool InsertVex(Vex sVex) {
    if (m_Graph.m_nVexNum == 32767) {
        return false;
    }
    m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
    return true;
}
//插入边
bool InsertEdge(Edge sEdge) {
    if (sEdge.vex1 < 0 || sEdge.vex1 >= m_Graph.m_nVexNum ||
        sEdge.vex2 < 0 || sEdge.vex2 >= m_Graph.m_nVexNum)
        return false;
    m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
    m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
    return true;
}
Vex GetVex(int v) {
    return m_Graph.m_aVexs[v];
}
int FindEdge(int v, Edge aEdge[]) {
    int k = 0;
    for (int i = 0; i < m_Graph.m_nVexNum; i++) {
        if (m_Graph.m_aAdjMatrix[v][i] != 0) {
            aEdge[k].vex1 = v;
            aEdge[k].vex2 = i;
            aEdge[k].weight = m_Graph.m_aAdjMatrix[v][i];
            k++;
        }
    }
    return k;
}
void DFSTraverse(int nVex, PathList& pList) {
    bool bVisited[20] = { false };
    int nIndex = 0;
    DFS(nVex, bVisited, nIndex, pList);
}
void DFS(int nVex, bool bVisited[], int& nIndex, PathList& pList) {
    bVisited[nVex] = true;
    pList->vexs[nIndex++] = nVex;//入栈
    int nVexnum = 0;//记录访问过的顶点个数
    for (int i = 0; i < m_Graph.m_nVexNum; i++) {
        if (bVisited[i] == true) {
            nVexnum++;
        }
    }
    //判断是否所有顶点都访问过
    if (nVexnum == m_Graph.m_nVexNum) {
        pList->next = (PathList)malloc(sizeof(Path));
        for (int i = 0; i < m_Graph.m_nVexNum; i++) {
            pList->next->vexs[i] = pList->vexs[i];
        }
        pList = pList->next;
        pList->next = NULL;
    }
    else {
        for (int i = 0; i < m_Graph.m_nVexNum; i++) {
            if (!bVisited[i] && (m_Graph.m_aAdjMatrix[nVex][i] > 0) && (m_Graph.m_aAdjMatrix[nVex][i] != 32767)) {
                DFS(i, bVisited, nIndex, pList);//递归得到一条路径
                bVisited[i] = false;
                nIndex--;//回溯
            }
        }
    }
}
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]) {
    //初始化最短路径
    int flag[20], pre[20];//标记，前置顶点
    int dist[20], k = 0;
    for (int i = 0; i < m_Graph.m_nVexNum; i++) {
        flag[i] = 0;//初始化未被访问
        pre[i] = -1;//初始化前置顶点
        if (m_Graph.m_aAdjMatrix[nVexStart][i] > 0 || i == nVexStart) {
            dist[i] = m_Graph.m_aAdjMatrix[nVexStart][i];//两点距离
            pre[i] = nVexStart;
        }
        else {
            dist[i] = INF;//将其他顶点与起点的距离初始化为无穷大
        }
    }
    flag[nVexStart] = 1;//将起点标记成已访问
    int min;
    //遍历m_Graph.m_nVexNum-1次；每次找出一个顶点的最短路径
    for (int i = 1; i < m_Graph.m_nVexNum; i++) {
        min = INF;
        for (int j = 0; j < m_Graph.m_nVexNum; j++) {
            if (flag[j] == 0 && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;
        if (k == nVexEnd) {
            break;
        }
        for (int j = 0; j < m_Graph.m_nVexNum; j++) {
            int tmp;//临时存储顶点k到顶点j的距离
            if (m_Graph.m_aAdjMatrix[k][j] == 0) {
                tmp = INF;
            }
            else {
                tmp = min + m_Graph.m_aAdjMatrix[k][j];
            }
            if (flag[j] == 0 && tmp < dist[j]) {
                dist[j] = tmp;
                pre[j] = k;
            }
        }
    }
    int Num = 0;
    int i = nVexEnd;//回溯
    while (i != nVexStart) {
        aPath[Num].vex2 = i;
        aPath[Num].vex1 = pre[i];
        aPath[Num].weight = m_Graph.m_aAdjMatrix[pre[i]][i];
        i = pre[i];
        Num++;
    }
    return Num;
}
int FindminTree(int nStart, Edge aEdge[]) {
    int flag[20];//标记数组
    int closest[20];//前置顶点
    int mindist[20];//最短权值
    //初始化
    for (int i = 0; i < m_Graph.m_nVexNum; i++) {
        closest[i] = -1;
        flag[i] = 0;
        if (m_Graph.m_aAdjMatrix[nStart][i] > 0 || i == nStart) {
            mindist[i] = m_Graph.m_aAdjMatrix[nStart][i];
            closest[i] = nStart;
        }
        else {
            mindist[i] = INF;
        }
    }
    flag[nStart] = 1;
    int num = 0;
    int min = 0;
    int k = 0;
    for (int i = 1; i < m_Graph.m_nVexNum; i++) {
        min = INF;
        for (int j = 0; j < m_Graph.m_nVexNum; j++) {
            if (flag[j] == 0 && mindist[j] < min) {
                min = mindist[j];
                k = j;
            }
        }
        flag[k] = 1;
        for (int j = 0; j < m_Graph.m_nVexNum; j++) {
            if (flag[j] == 0 && m_Graph.m_aAdjMatrix[k][j] < mindist[j] && m_Graph.m_aAdjMatrix[k][j] != 0) {
                mindist[j] = m_Graph.m_aAdjMatrix[k][j];
                closest[j] = k;
            }
        }
        flag[closest[k]] = 1;
        aEdge[num].vex1 = closest[k];
        aEdge[num].vex2 = k;
        aEdge[num].weight = m_Graph.m_aAdjMatrix[closest[k]][k];
        num++;
    }
    return num;
}
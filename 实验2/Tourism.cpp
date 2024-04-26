#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
#include <fstream>
using namespace std;
extern CGraph m_Graph;
//功能1. 创建景区顶点
void CreateGraph(void) {
    Init();
    cout << "===== 创建景区管理图 =====" << endl;
    int num;
    FILE* InVex = fopen("E:\\数据结构与算法实验\\实验2\\实验2\\Vex.txt", "r");
    fscanf(InVex, "%d", &num);
    cout << "顶点数目:" << num << endl;
    cout << "----- 顶点 -----" << endl;
    for (int i = 0; i < num; i++)
    {
        Vex vex;
        fscanf(InVex, "%d", &(vex.num));
        fscanf(InVex, "%s", vex.name);
        fscanf(InVex, "%s", vex.desc);
        cout << vex.num << " - " << vex.name << endl;
        InsertVex(vex);
    }
    fclose(InVex);
    cout << "----- 边 -----" << endl;;
    FILE* InEdge = fopen("E:\\数据结构与算法实验\\实验2\\实验2\\Edge.txt", "r");
    while (!feof(InEdge))
    {
        Edge edge;
        fscanf(InEdge, "%d %d %d", &edge.vex1, &edge.vex2, &edge.weight);
        cout << "<v" << edge.vex1 << ",v" << edge.vex2 << "> " << edge.weight << endl;
        InsertEdge(edge);
    }
    fclose(InEdge);
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++) {
            cout << m_Graph.m_aAdjMatrix[i][j] << "  ";
        }
        cout << endl;
    }
}
//功能2.查询景点信息
void GetSpotInfo(void) {
    if (m_Graph.m_nVexNum == 0) {
        cout << "景区无信息 请首先创建景区信息" << endl;
        return;
    }
    cout << "===== 查询景区信息 =====" << endl;
    int i;
    for (i = 0; i < m_Graph.m_nVexNum; i++) {
        cout << m_Graph.m_aVexs[i].num << " - " << m_Graph.m_aVexs[i].name << endl;
    }
    cout << "=========================" << endl;
    cout << "请输入想要查询的景点编号：";
    int v;
    cin >> v;
    if (v >= m_Graph.m_nVexNum) {
        cout << "编号输入错误 默认退出" << endl;
        return;
    }
    Vex vVex;
    vVex = GetVex(v);
    cout << "--------------------------" << endl;
    cout << vVex.name << ":" << vVex.desc << endl;
    cout << "--------------------------" << endl;
    cout << "=====周边景区=====" << endl;
    Edge aEdge[100];
    int nEdge = 0;
    nEdge = FindEdge(v, aEdge);
    for (int i = 0; i < nEdge; i++) {
        cout << m_Graph.m_aVexs[aEdge[i].vex1].name << "->" << m_Graph.m_aVexs[aEdge[i].vex2].name << " " <<
            aEdge[i].weight << "m"<<endl;
    }
}
//功能3.旅游景点导航
void TravelPath(void) {
    if (m_Graph.m_nVexNum == 0) {
        cout << "景区无信息 请首先创建景区信息" << endl;
        return;
    }
    for (int i = 0; i < m_Graph.m_nVexNum; i++)
        cout << m_Graph.m_aVexs[i].num << "-" << m_Graph.m_aVexs[i].name << endl;
    cout << "请输入起始点编号： ";
    int Num;
    cin >> Num;
    if (Num < 0 || Num >= m_Graph.m_nVexNum) {
        cout << "编号输入错误 默认退出" << endl;
        return;
    }
    cout << "导航路线为：" << endl;
    PathList pList = (PathList)malloc(sizeof(Path));
    PathList Head = pList;
    //调用DFSTraverse函数
    DFSTraverse(Num, pList);
    pList = Head;
    int i = 1;
    while (pList->next != NULL) {
        cout << "路线" << i << "：";
        for (int a = 0; a < m_Graph.m_nVexNum; a++) {
            cout << m_Graph.m_aVexs[pList->vexs[a]].name << "  ";
        }
        cout << endl;
        pList = pList->next;
        i++;
    }
    free(pList);
    pList = NULL;
    Head = NULL;
}
//功能4.搜索最短路径 Dijkstra贪心算法 贪心策略、最优子结构
void FindShortPath(void) {
    if (m_Graph.m_nVexNum == 0) {
        cout << "景区无信息 请首先创建景区信息" << endl;
        return;
    }
    int nStart, nEnd;
    cout << "请输入起点的编号：" << endl;
    cin >> nStart;
    cout << "请输入终点的编号：" << endl;
    cin >> nEnd;
    if (nStart > nEnd || nEnd >= m_Graph.m_nVexNum) {
        cout << "编号输入错误 默认退出" << endl;
        return;
    }
    if (nStart == nEnd) {
        cout << "最短距离为：0" << endl;
        return;
    }
    Edge aPath[32767];
    int Num = FindShortPath(nStart, nEnd, aPath);
    cout << "最短路径为：" << endl;
    int Path = 0;
    for (int i = Num - 1; i >= 0; i--) {
        cout << m_Graph.m_aVexs[aPath[i].vex1].name << "->";
        cout << m_Graph.m_aVexs[aPath[i].vex2].name << endl;
        Path += aPath[i].weight;
    }
    cout << "最短路径为：" << Path <<"m"<< endl;
}
//功能5.铺设电路规划 Prim贪心算法
void DesignPath(void) {
    if (m_Graph.m_nVexNum == 0) {
        cout << "景区无信息 请首先创建景区信息" << endl;
        return;
    }
    int n = m_Graph.m_nVexNum - 1;
    cout << "请输入您要铺设电路的起始顶点：输入(" << 0 << "/" << n << ")" << endl;
    int nStart;
    cin >> nStart;
    if (nStart != 0 && nStart != n) {
        cout << "编号输入错误 默认退出" << endl;
        return;
    }
    Edge aEdge[20];
    int Num = FindminTree(nStart, aEdge), Path = 0;
    //输出
    cout << "在以下两个景点之间铺设电路：" << endl;
    for (int i = 0; i < Num; i++) {
        cout << m_Graph.m_aVexs[aEdge[i].vex1].name << " - " << m_Graph.m_aVexs[aEdge[i].vex2].name << " "
            << aEdge[i].weight << "m" << endl;
        Path += aEdge[i].weight;
    }
    cout << "铺设电路的总长度为：" << Path << "m" << endl;
}
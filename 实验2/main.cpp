#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Tourism.h"
using namespace std;
int main(void) {
	int bRunning = 1;
	while (bRunning!=0) {
		//输出界面
		cout << "====景区信息管理系统====" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << endl;
		cout << "请输入选项<0~5>：" << endl;
		cin >> bRunning;
		switch (bRunning)
		{
		case 1:
			system("cls");
			CreateGraph();
			system("pause");
			break;
		case 2:
			system("cls");
			GetSpotInfo();
			system("pause");
			break;
		case 3:
			system("cls");
			TravelPath();
			system("pause");
			break;
		case 4:
			system("cls");
			FindShortPath();
			system("pause");
			break;
		case 5:
			system("cls");
			DesignPath();
			system("pause");
			break;
		case 0:
			cout << "退出系统" << endl;
			exit(0);
			break;
		default:
			cout << "输入错误编号 默认退出系统" << endl;
			exit(0);
			break;
		}
	}
}
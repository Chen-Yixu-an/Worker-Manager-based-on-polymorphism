#include<iostream>
using namespace std;
#include "workerManager.h"

int main() 
{
	WorkerManager wm;
	int choice = 0;//用户的选择
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;//input
		switch (choice)
		{
		case 0://退出管理系统
			wm.ExitSystem();
			break;
		case 1://增加职工信息
			wm.Add_Emp();
			break;
		case 2://显示职工信息
			wm.Show_Emp();
			break;
		case 3://删除离职员工
			wm.Del_Emp();
			break;
		case 4://修改员工信息
			wm.Mod_Emp();
			break;
		case 5://查找员工信息
			wm.Find_Emp();
			break;
		case 6://按照编号排序
			wm.Sort_Emp();
			break;
		case 7://清空所有信息
			wm.Clean_File();
			break;
		}
	}
	system("pause");
	return 0;
}
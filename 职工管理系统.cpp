#include<iostream>
using namespace std;
#include "workerManager.h"

int main() 
{
	WorkerManager wm;
	int choice = 0;//�û���ѡ��
	while (true)
	{
		wm.Show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;//input
		switch (choice)
		{
		case 0://�˳�����ϵͳ
			wm.ExitSystem();
			break;
		case 1://����ְ����Ϣ
			wm.Add_Emp();
			break;
		case 2://��ʾְ����Ϣ
			wm.Show_Emp();
			break;
		case 3://ɾ����ְԱ��
			wm.Del_Emp();
			break;
		case 4://�޸�Ա����Ϣ
			wm.Mod_Emp();
			break;
		case 5://����Ա����Ϣ
			wm.Find_Emp();
			break;
		case 6://���ձ������
			wm.Sort_Emp();
			break;
		case 7://���������Ϣ
			wm.Clean_File();
			break;
		}
	}
	system("pause");
	return 0;
}
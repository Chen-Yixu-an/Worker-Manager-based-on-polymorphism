#pragma once
#include<iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"

#include<fstream>
#define FILENAME "cmpFile.txt"

class WorkerManager
{
public:
	//���캯��
	WorkerManager();
	//����
	void Show_Menu();
	//�˳�
	void ExitSystem();
	//��¼ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker ** m_EmpArray;
	//���ְ������
	void Add_Emp();
	//�����ļ�
	void save();
	//��־(�ж�)�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	//ͳ���ļ��е���Ա��
	int get_EmpNum();
	//��ʼ��ְ��
	void init_Emp();
	//��ʾְ��
	void Show_Emp();
	//ɾ��ְ��
	void Del_Emp();
	//ְ���Ƿ���ں���,���ڷ��������±�,�����ڷ���-1
	int IsExist(int id);
	//�޸�ְ��
	void Mod_Emp();
	//����ְ������
	void Find_Emp();
	//����ְ���������
	void Sort_Emp();
	//����ļ�
	void Clean_File();
	//��������
	~WorkerManager();
};
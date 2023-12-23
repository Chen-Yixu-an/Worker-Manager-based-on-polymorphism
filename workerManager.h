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
	//构造函数
	WorkerManager();
	//界面
	void Show_Menu();
	//退出
	void ExitSystem();
	//记录职工人数
	int m_EmpNum;
	//职工数组指针
	Worker ** m_EmpArray;
	//添加职工函数
	void Add_Emp();
	//保存文件
	void save();
	//标志(判断)文件是否为空
	bool m_FileIsEmpty;
	//统计文件中的人员数
	int get_EmpNum();
	//初始化职工
	void init_Emp();
	//显示职工
	void Show_Emp();
	//删除职工
	void Del_Emp();
	//职工是否存在函数,存在返回数组下标,不存在返回-1
	int IsExist(int id);
	//修改职工
	void Mod_Emp();
	//查找职工函数
	void Find_Emp();
	//按照职工编号排序
	void Sort_Emp();
	//清空文件
	void Clean_File();
	//析构函数
	~WorkerManager();
};
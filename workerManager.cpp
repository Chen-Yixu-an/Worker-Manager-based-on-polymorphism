#include "workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//保存数据
	this->init_Emp();
	//初始化属性
	this->m_EmpNum = 0;
	this->m_EmpArray = NULL;
}

void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统!  **********" << endl;
	cout << "************** 0.退出管理系统 **************" << endl;
	cout << "************** 1.增加职工信息 **************" << endl;
	cout << "************** 2.显示职工信息 **************" << endl;
	cout << "************** 3.删除离职员工 **************" << endl;
	cout << "************** 4.修改员工信息 **************" << endl;
	cout << "************** 5.查找员工信息 **************" << endl;
	cout << "************** 6.按照编号排序 **************" << endl;
	cout << "************** 7.清空所有信息 **************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加的职工的数量：";
	int addNum = 0;//职工数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加，计算空间大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加数据
		for (int i = 0;i < addNum;i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工编号：";
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名：";
			cin >> name;

			cout << "请选择该员工职位：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		//更新数据
		this->m_FileIsEmpty = false;
		cout << "添加成功！本次共添加了" << addNum << "人" << endl;
		//保存数据
		this->save();
	}
	else
	{
		cout << "error!输入数据有误！" << endl;
	}
	//按任意键后 清屏回到上级目录
	system("pause");
	system("cls");
}

void WorkerManager::save() 
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0;i < this->m_EmpNum;i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//统计文件中的人员数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

//初始化职工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;
		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if(this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0;i < m_EmpNum;i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要删除的职工编号：";
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//说明找到了,删除员工
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功!" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工!" << endl;
		}
	}
	//保存数据
	this->save();
}

//职工是否存在函数,存在返回数组下标,不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入想要修改的职工编号：";
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到员工，修改信息
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查找到了" << id << "号职工，请输入新职工编号：";
			cin >> newId;
			cout << "请输入新姓名：";
			cin >> newName;
			cout << "请选择该员工新的职位：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, newName, 1);
				break;
			case 2:
				worker = new Manager(id, newName, 2);
				break;
			case 3:
				worker = new Boss(id, newName, 3);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "修改成功!" << endl;
			//保存数据
			this->save();
		}
		else
		{
			cout << "修改失败,查无此人！" << endl;
		}
		//按任意键后 清屏回到上级目录
		system("pause");
		system("cls");
	}
}

//查找职工函数
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式:" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照姓名查找" << endl;
		int select = 0;
		cin >> select;
		if(select == 1)
		{
			//按照编号
			int id;
			cout << "请输入要查找的职工编号:";
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			//按照姓名
			string name;
			cout << "请输入要查找的职工的姓名:";
			cin >> name;
			bool flag = false;
			for (int i = 0;i < m_EmpNum;i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工"
						<< this->m_EmpArray[i]->m_Id
						<< "的信息如下" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入选项有误!" << endl;
		}
	}
	//按任意键后 清屏回到上级目录
	system("pause");
	system("cls");
}

//按照职工编号排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
		//按任意键后 清屏回到上级目录
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入排序方式:" << endl;
		cout << "1.按职工号进行升序排序" << endl;
		cout << "2.按职工号进行降序排序" << endl;
		int select;
		cin >> select;
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			int minOrMax = i;
			for (int j = 0; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序排序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//降序排序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker * temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功!排序后的结果为:" << endl;
		//保存数据
		this->save();
		this->Show_Emp();
	}
	//按任意键后 清屏回到上级目录
	system("pause");
	system("cls");
}

//清空文件
void WorkerManager::Clean_File()
{
	cout << "确定要清空文件吗?" << endl;
	cout << "1:确定 2:返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		//del
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			//删除对象
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		else
		{
			cout << "文件不存在或者记录为空!" << endl;
			//按任意键后 清屏回到上级目录
			system("pause");
			system("cls");
		}
		cout << "删除成功!" << endl;
	}
	//按任意键后 清屏回到上级目录
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
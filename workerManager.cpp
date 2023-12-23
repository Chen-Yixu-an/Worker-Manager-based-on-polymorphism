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
	//�ļ���Ϊ��
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	//���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//��������
	this->init_Emp();
	//��ʼ������
	this->m_EmpNum = 0;
	this->m_EmpArray = NULL;
}

void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ!  **********" << endl;
	cout << "************** 0.�˳�����ϵͳ **************" << endl;
	cout << "************** 1.����ְ����Ϣ **************" << endl;
	cout << "************** 2.��ʾְ����Ϣ **************" << endl;
	cout << "************** 3.ɾ����ְԱ�� **************" << endl;
	cout << "************** 4.�޸�Ա����Ϣ **************" << endl;
	cout << "************** 5.����Ա����Ϣ **************" << endl;
	cout << "************** 6.���ձ������ **************" << endl;
	cout << "************** 7.���������Ϣ **************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//���ְ��
void WorkerManager::Add_Emp()
{
	cout << "��������ӵ�ְ����������";
	int addNum = 0;//ְ������
	cin >> addNum;
	if (addNum > 0)
	{
		//��ӣ�����ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker ** newSpace = new Worker*[newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�������
		for (int i = 0;i < addNum;i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����ְ����ţ�";
			cin >> id;

			cout << "�������" << i + 1 << "����ְ��������";
			cin >> name;

			cout << "��ѡ���Ա��ְλ��" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
		//��������
		this->m_FileIsEmpty = false;
		cout << "��ӳɹ������ι������" << addNum << "��" << endl;
		//��������
		this->save();
	}
	else
	{
		cout << "error!������������" << endl;
	}
	//��������� �����ص��ϼ�Ŀ¼
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

//ͳ���ļ��е���Ա��
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
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

//��ʼ��ְ��
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
		if (dId == 1)//��ְͨ��
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

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if(this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
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

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ����ţ�";
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//˵���ҵ���,ɾ��Ա��
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ�!" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��!" << endl;
		}
	}
	//��������
	this->save();
}

//ְ���Ƿ���ں���,���ڷ��������±�,�����ڷ���-1
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

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸ĵ�ְ����ţ�";
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ�Ա�����޸���Ϣ
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "���ҵ���" << id << "��ְ������������ְ����ţ�";
			cin >> newId;
			cout << "��������������";
			cin >> newName;
			cout << "��ѡ���Ա���µ�ְλ��" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			cout << "�޸ĳɹ�!" << endl;
			//��������
			this->save();
		}
		else
		{
			cout << "�޸�ʧ��,���޴��ˣ�" << endl;
		}
		//��������� �����ص��ϼ�Ŀ¼
		system("pause");
		system("cls");
	}
}

//����ְ������
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ:" << endl;
		cout << "1.����ְ����Ų���" << endl;
		cout << "2.������������" << endl;
		int select = 0;
		cin >> select;
		if(select == 1)
		{
			//���ձ��
			int id;
			cout << "������Ҫ���ҵ�ְ�����:";
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2)
		{
			//��������
			string name;
			cout << "������Ҫ���ҵ�ְ��������:";
			cin >> name;
			bool flag = false;
			for (int i = 0;i < m_EmpNum;i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ��"
						<< this->m_EmpArray[i]->m_Id
						<< "����Ϣ����" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cout << "����ѡ������!" << endl;
		}
	}
	//��������� �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//����ְ���������
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
		//��������� �����ص��ϼ�Ŀ¼
		system("pause");
		system("cls");
	}
	else
	{
		cout << "����������ʽ:" << endl;
		cout << "1.��ְ���Ž�����������" << endl;
		cout << "2.��ְ���Ž��н�������" << endl;
		int select;
		cin >> select;
		for (int i = 0;i < this->m_EmpNum;i++)
		{
			int minOrMax = i;
			for (int j = 0; j < this->m_EmpNum; j++)
			{
				if (select == 1)//��������
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//��������
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
		cout << "����ɹ�!�����Ľ��Ϊ:" << endl;
		//��������
		this->save();
		this->Show_Emp();
	}
	//��������� �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ��Ҫ����ļ���?" << endl;
	cout << "1:ȷ�� 2:����" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		//del
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			//ɾ������
			for (int i = 0;i < this->m_EmpNum;i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		else
		{
			cout << "�ļ������ڻ��߼�¼Ϊ��!" << endl;
			//��������� �����ص��ϼ�Ŀ¼
			system("pause");
			system("cls");
		}
		cout << "ɾ���ɹ�!" << endl;
	}
	//��������� �����ص��ϼ�Ŀ¼
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
#include "WorkerManager.h"
#include <fstream>

WorkerManager::WorkerManager()		//构造函数
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_FileisEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;

	if (ifs.eof())
	{
		this->m_Empnum = 0;
		this->m_EmpArray = NULL;
		this->m_FileisEmpty = true;
		ifs.close();
		return;
	}
	
	int num = this->get_EmpNum();
	this->m_Empnum = num;
	this->m_EmpArray = new Worker*[this->m_Empnum];
	init_emp();
	ifs.close();
}

WorkerManager::~WorkerManager()		//析构函数
{
	for (int i = 0; i < this->m_Empnum; i++)
	{
		if (this->m_EmpArray[i] != NULL)
			delete this->m_EmpArray[i];			//数组每个元素的内存释放
	}

	delete[] this->m_EmpArray;			//删除堆区数组内存
	this->m_Empnum = 0;
	this->m_EmpArray = NULL;
	this->m_FileisEmpty = true;
}

void WorkerManager::Show_Menu()					//显示菜单
{
	cout << "**********************************************" << endl;
	cout << "**********  欢迎使用职工管理系统！  **********" << endl;
	cout << "**************  0.退出管理程序  **************" << endl;
	cout << "**************  1.增加职工信息  **************" << endl;
	cout << "**************  2.显示职工信息  **************" << endl;
	cout << "**************  3.删除职工信息  **************" << endl;
	cout << "**************  4.修改职工信息  **************" << endl;
	cout << "**************  5.查找职工信息  **************" << endl;
	cout << "**************  6.按照编号排序  **************" << endl;
	cout << "**************  7.清空所有文档  **************" << endl;
	cout << "**********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()							//退出系统
{
	cout << "欢迎下次使用！" << endl;
	exit(0);
}


void WorkerManager::AddEmp()				//添加职工
{
	int add_num = 0;		//记录用户添加的数量

	cout << "请输入添加职工的数量：" << endl;
	cin >> add_num;

	if (add_num > 0)
	{
		//计算添加新空间的大小
		int new_size = this->m_Empnum + add_num;
		Worker** newspace = new Worker*[new_size];

		if (this->m_EmpArray != NULL)					//将原有的数据添加进新开辟的空间
		{
			for (int i = 0; i < this->m_Empnum; i++)
				newspace[i] = this->m_EmpArray[i];
		}

		//批量添加新数据
		for (int i = 0; i < add_num; i++)
		{
			int id;		//职工编号
			string name;	//职工姓名
			int Dselect;	//部门选择

			cout << "请输入第 " << i + 1 << "个新员工的编号: " << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << "个新员工的姓名:" << endl;
			cin >> name;

			cout << "请选择职工岗位：" << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> Dselect;

			Worker* worker = NULL;			//创建一个父类指针
			switch (Dselect)
			{
			case 1:
				worker = new Employee(id, name, Dselect);
				break;
			case 2:
				worker = new Manager(id, name, Dselect);
				break;
			case 3:
				worker = new Boss(id, name, Dselect);
				break;
			default:
				break;
			}
			//将添加后的数据添加进数组中
			int size = this->m_Empnum + i;
			newspace[size] = worker;
		}

			//释放原有空间
			delete[] this->m_EmpArray;

			//修改新空间的指向和修改后的人数
			this->m_EmpArray = newspace;
			this->m_Empnum = new_size;

			//将添加的职工添加进文件
			this->save();

			//提示修改成功
			cout << "成功添加" << add_num << "个新职工!" << endl;
	}
	else
		cout << "输入数据有误" << endl;
}

void WorkerManager::save()				//保存职工到文件
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_Empnum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum()			//获取职工人数
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)		//读取文件行数
		num++;

	ifs.close();		//关闭文件
	return num;
}

void WorkerManager::init_emp()		//初始化数组
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)		//读取文件行数
	{
		Worker* worker = NULL;
		if (did == 1)	worker = new Employee(id, name, did);
		else if (did == 2)	worker = new Manager(id, name, did);
		else if (did == 3)	worker = new Boss(id, name, did);
		this->m_EmpArray[index] = worker;
		index++;
	}
}

void WorkerManager::show_Emp()		//显示职工
{
	if (this->m_FileisEmpty)
		cout << "文件不存在或者为空！" <<endl;
	else 
		for (int i = 0; i < this->m_Empnum; i++)
			this->m_EmpArray[i]->show_info();			//利用多态显示
}

void WorkerManager::del_Emp()			//删除职工
{
	int index, n_id;

	if (this->m_FileisEmpty)
		cout << "文件不存在或者为空！" << endl;
	else
	{
		cout << "请输入要删除职工的编号：" << endl;
		cin >> n_id;
		index = this->isExist(n_id);

		if (index != -1)					//职工存在，删除职工
		{
			delete this->m_EmpArray[index];				//释放掉内存，防止内存泄漏
			for (int i = index; i < this->m_Empnum-1; i++)
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			this->m_Empnum--;
			this->save();
			cout << "删除成功！" << endl;
		}
		else
			cout << "删除失败，未找到该职工！" << endl;
	}

}

int WorkerManager::isExist(int id)				//判断职工是否存在
{
	int index = -1;

	for (int i=0; i < this->m_Empnum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}	
	}
	return index;
}

void WorkerManager::mod_Emp()				//修改职工信息
{
	int index, n_id;

	if (this->m_FileisEmpty)
		cout << "文件不存在或者为空！" << endl;
	else
	{
		cout << "请输入要修改职工的编号：" << endl;
		cin >> n_id;
		index = this->isExist(n_id);

		if (index != -1)					//职工存在，修改职工
		{
			delete this->m_EmpArray[index];

			int id;		//职工编号
			string name;	//职工姓名
			int Dselect;	//部门选择

			cout << "请重新输入修改员工的编号: " << endl;
			cin >> id;

			cout << "请重新输入修改员工的姓名:" << endl;
			cin >> name;

			cout << "请重新输入要修改职工的岗位：" << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> Dselect;

			Worker* worker = NULL;
			if (Dselect == 1)	worker = new Employee(id, name, Dselect);
			else if (Dselect == 2)	worker = new Manager(id, name, Dselect);
			else if (Dselect == 3)	worker = new Boss(id, name, Dselect);
			this->m_EmpArray[index] = worker;
			this->save();

			cout << "修改成功！" << endl;
		}
		else
			cout << "修改失败，未找到该职工！" << endl;
	}
}

void WorkerManager::Find_Emp()			//查找职工
{
	if (this->m_FileisEmpty)
		cout << "文件不存在或者为空！" << endl;
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;

		int select;
		cin >> select;

		if (select == 1)
		{
			int id, index;
			cout << "请输入要查找职工的编号：" << endl;
			cin >> id;
			index = this->isExist(id);
			if (index != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[index]->show_info();
			}
			else
				cout << "未找到该职工！" << endl;
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入要查找职工的姓名：" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功！该职工信息如下：" << endl;
					this->m_EmpArray[i]->show_info();
					flag = true;
				}
			}
			if (flag == false)
				cout << "未找到该职工！" << endl;
		}
	}
}

void  WorkerManager::Sort_Emp()			//按照编号排序
{
	if (this->m_FileisEmpty)
		cout << "文件不存在或者为空！" << endl;
	else
	{
		cout << "请选择排序的方式:" << endl;
		cout << "1.按照职工号升序排：" << endl;
		cout << "2.按照职工号降序排：" << endl;

		int select;
		cin >> select;

		for (int i = 0; i < this->m_Empnum - 1; i++)
		{
			int MinorMax = i;
			for (int j = i + 1; j < this->m_Empnum; j++)
			{
				//升序
				if (select == 1)
				{
					if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[MinorMax]->m_Id)
						MinorMax = j;
				}
				else if (select == 2)
				{
					if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[MinorMax]->m_Id)
						MinorMax = j;
				}
			}
			if (i != MinorMax)
			{
				Worker* temp = this->m_EmpArray[MinorMax];
				this->m_EmpArray[MinorMax] = this->m_EmpArray[i];
				this->m_EmpArray[i] = temp;
			}
		}
		cout << "排序成功！" << endl;
		this->save();
		this->show_Emp();
	}
}

void WorkerManager::Clean_File()			//清空文件
{
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		//打开模式ios::trunc  删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
					delete this->m_EmpArray[i];
			}

			delete[] this->m_EmpArray;			//删除堆区数组内存
			this->m_Empnum = 0;
			this->m_EmpArray = NULL;
			this->m_FileisEmpty = true;
		}
		cout << "清空成功!" << endl;
	}
}
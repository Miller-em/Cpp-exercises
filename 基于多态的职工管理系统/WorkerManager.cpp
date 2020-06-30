#include "WorkerManager.h"
#include <fstream>

WorkerManager::WorkerManager()		//���캯��
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

WorkerManager::~WorkerManager()		//��������
{
	for (int i = 0; i < this->m_Empnum; i++)
	{
		if (this->m_EmpArray[i] != NULL)
			delete this->m_EmpArray[i];			//����ÿ��Ԫ�ص��ڴ��ͷ�
	}

	delete[] this->m_EmpArray;			//ɾ�����������ڴ�
	this->m_Empnum = 0;
	this->m_EmpArray = NULL;
	this->m_FileisEmpty = true;
}

void WorkerManager::Show_Menu()					//��ʾ�˵�
{
	cout << "**********************************************" << endl;
	cout << "**********  ��ӭʹ��ְ������ϵͳ��  **********" << endl;
	cout << "**************  0.�˳��������  **************" << endl;
	cout << "**************  1.����ְ����Ϣ  **************" << endl;
	cout << "**************  2.��ʾְ����Ϣ  **************" << endl;
	cout << "**************  3.ɾ��ְ����Ϣ  **************" << endl;
	cout << "**************  4.�޸�ְ����Ϣ  **************" << endl;
	cout << "**************  5.����ְ����Ϣ  **************" << endl;
	cout << "**************  6.���ձ������  **************" << endl;
	cout << "**************  7.��������ĵ�  **************" << endl;
	cout << "**********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()							//�˳�ϵͳ
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	exit(0);
}


void WorkerManager::AddEmp()				//���ְ��
{
	int add_num = 0;		//��¼�û���ӵ�����

	cout << "���������ְ����������" << endl;
	cin >> add_num;

	if (add_num > 0)
	{
		//��������¿ռ�Ĵ�С
		int new_size = this->m_Empnum + add_num;
		Worker** newspace = new Worker*[new_size];

		if (this->m_EmpArray != NULL)					//��ԭ�е�������ӽ��¿��ٵĿռ�
		{
			for (int i = 0; i < this->m_Empnum; i++)
				newspace[i] = this->m_EmpArray[i];
		}

		//�������������
		for (int i = 0; i < add_num; i++)
		{
			int id;		//ְ�����
			string name;	//ְ������
			int Dselect;	//����ѡ��

			cout << "������� " << i + 1 << "����Ա���ı��: " << endl;
			cin >> id;

			cout << "������� " << i + 1 << "����Ա��������:" << endl;
			cin >> name;

			cout << "��ѡ��ְ����λ��" << endl;
			cout << "1.Ա��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> Dselect;

			Worker* worker = NULL;			//����һ������ָ��
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
			//����Ӻ��������ӽ�������
			int size = this->m_Empnum + i;
			newspace[size] = worker;
		}

			//�ͷ�ԭ�пռ�
			delete[] this->m_EmpArray;

			//�޸��¿ռ��ָ����޸ĺ������
			this->m_EmpArray = newspace;
			this->m_Empnum = new_size;

			//����ӵ�ְ����ӽ��ļ�
			this->save();

			//��ʾ�޸ĳɹ�
			cout << "�ɹ����" << add_num << "����ְ��!" << endl;
	}
	else
		cout << "������������" << endl;
}

void WorkerManager::save()				//����ְ�����ļ�
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
int WorkerManager::get_EmpNum()			//��ȡְ������
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)		//��ȡ�ļ�����
		num++;

	ifs.close();		//�ر��ļ�
	return num;
}

void WorkerManager::init_emp()		//��ʼ������
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)		//��ȡ�ļ�����
	{
		Worker* worker = NULL;
		if (did == 1)	worker = new Employee(id, name, did);
		else if (did == 2)	worker = new Manager(id, name, did);
		else if (did == 3)	worker = new Boss(id, name, did);
		this->m_EmpArray[index] = worker;
		index++;
	}
}

void WorkerManager::show_Emp()		//��ʾְ��
{
	if (this->m_FileisEmpty)
		cout << "�ļ������ڻ���Ϊ�գ�" <<endl;
	else 
		for (int i = 0; i < this->m_Empnum; i++)
			this->m_EmpArray[i]->show_info();			//���ö�̬��ʾ
}

void WorkerManager::del_Emp()			//ɾ��ְ��
{
	int index, n_id;

	if (this->m_FileisEmpty)
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	else
	{
		cout << "������Ҫɾ��ְ���ı�ţ�" << endl;
		cin >> n_id;
		index = this->isExist(n_id);

		if (index != -1)					//ְ�����ڣ�ɾ��ְ��
		{
			delete this->m_EmpArray[index];				//�ͷŵ��ڴ棬��ֹ�ڴ�й©
			for (int i = index; i < this->m_Empnum-1; i++)
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			this->m_Empnum--;
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
	}

}

int WorkerManager::isExist(int id)				//�ж�ְ���Ƿ����
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

void WorkerManager::mod_Emp()				//�޸�ְ����Ϣ
{
	int index, n_id;

	if (this->m_FileisEmpty)
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	else
	{
		cout << "������Ҫ�޸�ְ���ı�ţ�" << endl;
		cin >> n_id;
		index = this->isExist(n_id);

		if (index != -1)					//ְ�����ڣ��޸�ְ��
		{
			delete this->m_EmpArray[index];

			int id;		//ְ�����
			string name;	//ְ������
			int Dselect;	//����ѡ��

			cout << "�����������޸�Ա���ı��: " << endl;
			cin >> id;

			cout << "�����������޸�Ա��������:" << endl;
			cin >> name;

			cout << "����������Ҫ�޸�ְ���ĸ�λ��" << endl;
			cout << "1.Ա��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> Dselect;

			Worker* worker = NULL;
			if (Dselect == 1)	worker = new Employee(id, name, Dselect);
			else if (Dselect == 2)	worker = new Manager(id, name, Dselect);
			else if (Dselect == 3)	worker = new Boss(id, name, Dselect);
			this->m_EmpArray[index] = worker;
			this->save();

			cout << "�޸ĳɹ���" << endl;
		}
		else
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ����" << endl;
	}
}

void WorkerManager::Find_Emp()			//����ְ��
{
	if (this->m_FileisEmpty)
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1.����ְ����Ų���" << endl;
		cout << "2.����ְ����������" << endl;

		int select;
		cin >> select;

		if (select == 1)
		{
			int id, index;
			cout << "������Ҫ����ְ���ı�ţ�" << endl;
			cin >> id;
			index = this->isExist(id);
			if (index != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[index]->show_info();
			}
			else
				cout << "δ�ҵ���ְ����" << endl;
		}
		else if (select == 2)
		{
			string name;
			cout << "������Ҫ����ְ����������" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->show_info();
					flag = true;
				}
			}
			if (flag == false)
				cout << "δ�ҵ���ְ����" << endl;
		}
	}
}

void  WorkerManager::Sort_Emp()			//���ձ������
{
	if (this->m_FileisEmpty)
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	else
	{
		cout << "��ѡ������ķ�ʽ:" << endl;
		cout << "1.����ְ���������ţ�" << endl;
		cout << "2.����ְ���Ž����ţ�" << endl;

		int select;
		cin >> select;

		for (int i = 0; i < this->m_Empnum - 1; i++)
		{
			int MinorMax = i;
			for (int j = i + 1; j < this->m_Empnum; j++)
			{
				//����
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
		cout << "����ɹ���" << endl;
		this->save();
		this->show_Emp();
	}
}

void WorkerManager::Clean_File()			//����ļ�
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		//��ģʽios::trunc  ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
					delete this->m_EmpArray[i];
			}

			delete[] this->m_EmpArray;			//ɾ�����������ڴ�
			this->m_Empnum = 0;
			this->m_EmpArray = NULL;
			this->m_FileisEmpty = true;
		}
		cout << "��ճɹ�!" << endl;
	}
}
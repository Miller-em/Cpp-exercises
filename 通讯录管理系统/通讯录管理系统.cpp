#include <iostream>
#include <string>

using namespace std;
#define MAX 1000

/*����һ����ϵ�˽ṹ��*/
typedef struct				
{	
	string name;  //��ϵ������	
	int sex;      //1��ʾ�У�2��ʾŮ
	int age;	  //��ϵ������
	string phone_num; //��ϵ�˵绰����
	string addr; //��ϵ�˵�ַ
}person;

/*����һ��ͨѶ¼�ṹ��*/
typedef struct				
{
	person personarray[MAX];
	int pSize;						//ͨѶ¼�е�����
}addBooks;

void ShowMenu(); //��ʾ�˵�����
int InitAddBooKs(addBooks* L); //ͨѶ¼��ʼ��
int Add_person(addBooks *L); //������ϵ��
void ShowBooks(addBooks* L); //��ʾ��ϵ��
int isExist(addBooks* L, string name); //�����ϵ���Ƿ����
void Deperson(addBooks* L); //ɾ����ϵ��
void Findperson(addBooks* L); //������ϵ��
void modifyPerson(addBooks* L); //�޸���ϵ��
void clearPerson(addBooks* L);			//���ͨѶ¼


int main()
{
	int select = 0; //�û�ѡ��ı���
	addBooks Books; 

	InitAddBooKs(&Books);		//��ʼ��ͨѶ¼
	while (true)
	{
		ShowMenu();				//�˵���ʾ
		cout << "��ѡ���ܣ�" << endl;
		cin >> select;

		switch (select)
		{
		case 1:					//������ϵ��
			Add_person(&Books);
			break;
		case 2:					//��ʾ��ϵ��
			ShowBooks(&Books);
			break;
		case 3:					//ɾ����ϵ��
			Deperson(&Books);
			break;
		case 4:					//������ϵ��
			Findperson(&Books);
			break;
		case 5:					//�޸���ϵ��
			modifyPerson(&Books);
			break;
		case 6:					//�����ϵ��
			clearPerson(&Books);
			break;
		case 0:					//�˳���ϵ��
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		default:
		{
			cout << "���޴˹��ܣ�����������!" << endl;
			system("pause");
			system("cls");
		}
			break;
		}
	}

	system("pause");
	return 0;
}

void ShowMenu() //��ʾ�˵�����
{
	cout << "*****  1.������ϵ��  *****" << endl;
	cout << "*****  2.��ʾ��ϵ��  *****" << endl;
	cout << "*****  3.ɾ����ϵ��  *****" << endl;
	cout << "*****  4.������ϵ��  *****" << endl;
	cout << "*****  5.�޸���ϵ��  *****" << endl;
	cout << "*****  6.�����ϵ��  *****" << endl;
	cout << "*****  0.�˳���ϵ��  *****" << endl;
}

int Add_person(addBooks* L) //������ϵ��
{
	if (L->pSize >= MAX)
	{
		cout << "ͨѶ¼�������޷�������ϵ��!" << endl;
		return 0;
	}
	else
	{
		//��������
		string name;
		cout << "������������" << endl;
		cin >> name;
		L->personarray[L->pSize].name = name;

		//�����Ա�
		int sex;
		cout << "�������Ա�" << endl;
		cout << "1-----��" << endl;
		cout << "2-----Ů" << endl;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				L->personarray[L->pSize].sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}

		//��������
		int age;
		cout << "���������䣺" << endl;
		cin >> age;
		L->personarray[L->pSize].age = age;

		//����绰
		string phone_num;
		cout << "������绰���룺" << endl;
		cin >> phone_num;
		L->personarray[L->pSize].phone_num = phone_num;

		//�����ַ
		string addr;
		cout << "�������ַ��" << endl;
		cin >> addr;
		L->personarray[L->pSize].addr = addr;

		L->pSize++;
		system("pause");
		system("cls");
		return 1;
	}
}

int InitAddBooKs(addBooks* L)	//��ʼ��ͨѶ¼
{
	L->pSize = 0;
	return 0;
}

void ShowBooks(addBooks* L) //��ʾ��ϵ��
{
	if (L->pSize == 0)				//���ͨѶ¼û���ˣ�Ҫ����쳣
	{
		cout << "��ǰͨѶ¼û�м�¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		for (int i = 0; i < L->pSize; i++)
		{
			cout << "������" << L->personarray[i].name << "\t";
			cout << "�Ա�" << (L->personarray[i].sex == 1 ? "��":"Ů") << "\t";
			cout << "���䣺" << L->personarray[i].age << "\t";
			cout << "�绰��" << L->personarray[i].phone_num << "\t";
			cout << "��ַ��" << L->personarray[i].addr << endl;
		}
	}
	system("pause");
	system("cls");
	return;
}

int isExist(addBooks* L, string name) //�����ϵ���Ƿ����
{
	for (int i = 0; i < L->pSize; i++)
	{
		if (name == L->personarray[i].name)
			return i;
	}
	return -1; //δ�ҵ�
}

void Deperson(addBooks* L) //ɾ����ϵ��
{
	string name;
	int i;
	cout << "������ɾ����ϵ������: " << endl;
	cin >> name;
	int rst = isExist(L, name);

	if (rst == -1)
	{
		cout << "���޴��ˣ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		for (i = rst; i < L->pSize - 1; i++)
			L->personarray[i] = L->personarray[i +1];
		L->pSize--;
		cout << "ɾ���ɹ���" << endl;
		system("pause");
		system("cls");
		return;
	}
}

void Findperson(addBooks* L) //������ϵ��
{
	string name;
	int i;
	cout << "�����������ϵ������: " << endl;
	cin >> name;
	int rst = isExist(L, name);

	if (rst == -1)
	{
		cout << "���޴��ˣ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "������" << L->personarray[rst].name << "\t";
		cout << "�Ա�" << (L->personarray[rst].sex == 1 ? "��" : "Ů") << "\t";
		cout << "���䣺" << L->personarray[rst].age << "\t";
		cout << "�绰��" << L->personarray[rst].phone_num << "\t";
		cout << "��ַ��" << L->personarray[rst].addr << endl;
		system("pause");
		system("cls");
		return;
	}
}

void modifyPerson(addBooks* L) //�޸���ϵ��
{
	string name;
	int i;
	cout << "������Ҫ�޸ĵ���ϵ������: " << endl;
	cin >> name;
	int rst = isExist(L, name);

	if (rst == -1)
	{
		cout << "���޴��ˣ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		//��������
		string name;
		cout << "�������޸ĵ�������" << endl;
		cin >> name;
		L->personarray[rst].name = name;

		//�����Ա�
		int sex;
		cout << "�������Ա�" << endl;
		cout << "1-----��" << endl;
		cout << "2-----Ů" << endl;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				L->personarray[rst].sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}

		//��������
		int age;
		cout << "�������޸ĵ����䣺" << endl;
		cin >> age;
		L->personarray[rst].age = age;

		//����绰
		string phone_num;
		cout << "�������޸ĵĵ绰���룺" << endl;
		cin >> phone_num;
		L->personarray[rst].phone_num = phone_num;

		//�����ַ
		string addr;
		cout << "�������޸ĵĵ�ַ��" << endl;
		cin >> addr;
		L->personarray[rst].addr = addr;
		cout << "�޸ĳɹ���" << endl;

		system("pause");
		system("cls");
		return;
	}
}

void clearPerson(addBooks* L)			//���ͨѶ¼
{
	L->pSize = 0;
	cout << "ͨѶ¼����գ�" << endl;
	system("pause");
	system("cls");
}
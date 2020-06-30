#include <fstream>
#include <iostream>
#include <string>
#include "WorkerManager.h"
#include "Worker.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"

using namespace std;


int main()
{
	WorkerManager wm;			//����һ��ְ���������
	int choice = -1;			//�����û���ѡ���ֵ

	while (true)
	{
		wm.Show_Menu();				//�˵�����ʾ
		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.exitSystem();		//�˳�ϵͳ
			break;
		case 1:
			wm.AddEmp();			//���ְ��
			break;
		case 2:
			wm.show_Emp();			//��ʾְ��
			break;
		case 3:
			wm.del_Emp();			//ɾ��ְ��
			break;
		case 4:
			wm.mod_Emp();			//�޸�Ա����Ϣ
			break;
		case 5:
			wm.Find_Emp();			//����Ա����Ϣ
			break;
		case 6:
			wm.Sort_Emp();			//����ְ��������
			break;
		case 7:
			wm.Clean_File();		//����ļ�
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
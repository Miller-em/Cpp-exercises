#pragma once		//��ֹͷ�ļ�����
#include <iostream>
#include "Worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;	//ʹ�ñ�׼�������ռ�
#define FILENAME "empfile.txt"

class WorkerManager
{
public:
	WorkerManager();		//���캯��
	
	void Show_Menu();			//��ʾ�˵�
	void exitSystem();			//�˳�ϵͳ
	void AddEmp();				//���ְ��
	void save();				//����ְ�����ļ�
	int get_EmpNum();			//��ȡְ������
	void init_emp();			//��ʼ������
	void show_Emp();			//��ʾְ��
	void del_Emp();				//ɾ��ְ��
	void mod_Emp();				//�޸�ְ����Ϣ
	void Find_Emp();			//����ְ��
	void Sort_Emp();			//���ձ������
	void Clean_File();			//����ļ�

	int isExist(int id);				//�ж�ְ���Ƿ����

	~WorkerManager();		//��������
	
	/*
		��������
		m_Empnum��ְ������
		m_EmpArray�����ְ��������
		m_FileisEmpty: �ж��ļ��Ƿ�Ϊ��
	*/
	int m_Empnum;			
	Worker** m_EmpArray;
	bool m_FileisEmpty;
};

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Worker
{
	/*����һ��Ա��������*/
public:
	//��ʾ������Ϣ
	virtual void show_info() = 0;
	//��ȡ��λ����
	virtual string get_Deptname() = 0;

	int m_Id;		//Ա���ı��
	string m_name;	//Ա��������
	int m_DeptId;	//Ա�����ڲ��ŵı��
};
#pragma once
#include <iostream>
#include <string>
#include "Worker.h"

using namespace std;

class Boss : public Worker
{
public:
	//���캯��
	Boss(int id, string name, int did);

	//��ʾ������Ϣ
	virtual void show_info();

	//��ȡ��λ����
	virtual string get_Deptname();
};

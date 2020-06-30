#pragma once
#include <iostream>
#include <string>
#include "Worker.h"

using namespace std;

class Boss : public Worker
{
public:
	//构造函数
	Boss(int id, string name, int did);

	//显示个人信息
	virtual void show_info();

	//获取岗位名称
	virtual string get_Deptname();
};

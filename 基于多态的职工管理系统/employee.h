#pragma once
#include <iostream>
#include <string>
#include "Worker.h"

using namespace std;


//定义一个员工类
class Employee : public Worker
{
public:
	//构造函数
	Employee(int id, string name, int did);

	//显示个人信息
	virtual void show_info();

	//获取岗位名称
	virtual string get_Deptname();
};
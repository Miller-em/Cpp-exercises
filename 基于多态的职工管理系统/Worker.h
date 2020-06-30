#pragma once
#include <iostream>
#include <string>

using namespace std;

class Worker
{
	/*构建一个员工抽象类*/
public:
	//显示个人信息
	virtual void show_info() = 0;
	//获取岗位名称
	virtual string get_Deptname() = 0;

	int m_Id;		//员工的编号
	string m_name;	//员工的姓名
	int m_DeptId;	//员工所在部门的编号
};
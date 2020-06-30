#pragma once		//防止头文件重名
#include <iostream>
#include "Worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;	//使用标准的命名空间
#define FILENAME "empfile.txt"

class WorkerManager
{
public:
	WorkerManager();		//构造函数
	
	void Show_Menu();			//显示菜单
	void exitSystem();			//退出系统
	void AddEmp();				//添加职工
	void save();				//保存职工到文件
	int get_EmpNum();			//获取职工人数
	void init_emp();			//初始化数组
	void show_Emp();			//显示职工
	void del_Emp();				//删除职工
	void mod_Emp();				//修改职工信息
	void Find_Emp();			//查找职工
	void Sort_Emp();			//按照编号排序
	void Clean_File();			//清空文件

	int isExist(int id);				//判断职工是否存在

	~WorkerManager();		//析构函数
	
	/*
		公有属性
		m_Empnum：职工人数
		m_EmpArray：存放职工的数组
		m_FileisEmpty: 判断文件是否为空
	*/
	int m_Empnum;			
	Worker** m_EmpArray;
	bool m_FileisEmpty;
};

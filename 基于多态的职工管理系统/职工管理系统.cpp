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
	WorkerManager wm;			//创建一个职工管理对象
	int choice = -1;			//设置用户的选择初值

	while (true)
	{
		wm.Show_Menu();				//菜单的显示
		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.exitSystem();		//退出系统
			break;
		case 1:
			wm.AddEmp();			//添加职工
			break;
		case 2:
			wm.show_Emp();			//显示职工
			break;
		case 3:
			wm.del_Emp();			//删除职工
			break;
		case 4:
			wm.mod_Emp();			//修改员工信息
			break;
		case 5:
			wm.Find_Emp();			//查找员工信息
			break;
		case 6:
			wm.Sort_Emp();			//按照职工号排序
			break;
		case 7:
			wm.Clean_File();		//清空文件
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
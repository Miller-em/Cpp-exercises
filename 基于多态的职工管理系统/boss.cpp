#include "boss.h"

//构造函数
Boss::Boss(int id, string name, int did)
{
    this->m_Id = id;
    this->m_name = name;
    this->m_DeptId = did;
}

//显示个人信息
void Boss::show_info()
{
    cout << "职工编号：" << this->m_Id
        << "\t职工姓名：" << this->m_name
        << "\t岗位：" << this->get_Deptname() << endl;
}

//获取岗位名称
string Boss::get_Deptname()
{
    return "老板";
}
#include "boss.h"

//���캯��
Boss::Boss(int id, string name, int did)
{
    this->m_Id = id;
    this->m_name = name;
    this->m_DeptId = did;
}

//��ʾ������Ϣ
void Boss::show_info()
{
    cout << "ְ����ţ�" << this->m_Id
        << "\tְ��������" << this->m_name
        << "\t��λ��" << this->get_Deptname() << endl;
}

//��ȡ��λ����
string Boss::get_Deptname()
{
    return "�ϰ�";
}
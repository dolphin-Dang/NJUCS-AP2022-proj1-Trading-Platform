#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

#include <iostream>
using namespace std;

class Administrator {
private:
	string a_id;
	string a_name;
	string a_password;
public:
	Administrator()
	{
		a_id = "U000";			//����ԱIDĬ��ΪU000
		a_name = "dolphin";		//����Ա����Ĭ��Ϊdolphin
		a_password = "123456";	//����Ա����Ĭ��Ϊ123456
	}
	void a_log_in();				//����Ա��¼
	void a_search_goods();			//���ؼ��֣�������Ʒ
	void a_all_goods();				//�鿴������Ʒ���������¼ܡ����۳���
	void a_remove_good();			//�¼���Ʒ

	void a_all_orders();			//�鿴���ж���

	void a_all_users();				//�鿴�����û�
	void a_ban_user();				//����û�

	void a_argue();				//����ϵͳ
};


#endif
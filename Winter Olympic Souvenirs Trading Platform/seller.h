#ifndef _SELLER_H_
#define _SELLER_H_

#include "user.h"

class Seller :public User {
public:
	Seller(string id) {
		u_id = id;
	}
	void s_my_goods();		//�鿴�Լ�����Ʒ��δ�۳������۳���
	void s_post_good();		//��������Ʒ
	void s_remove_good();	//�¼���Ʒ����ɾ����¼��״̬�ĳ��¼ܣ�
	void s_update_good();	//��Ʒ��Ϣ����
	void s_his_orders();	//�鿴��ʷ����
};

#endif
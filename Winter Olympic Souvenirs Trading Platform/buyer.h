#ifndef _BUYER_H_
#define _BUYER_H_

#include "user.h"

class Buyer :public User {
public:
	Buyer(string id) {
		u_id = id;
	}
	void b_buy();				//����Ʒ���γɶ���
	void b_judge();				//�������ң��γ�������Ϣ,�ύ����(��δ���)
	void b_all_goods();			//�鿴������Ʒ�б�
	void b_search_good();		//������Ʒ
	void b_his_orders();		//�鿴��ʷ����
	void b_good_detail();		//�鿴��Ʒ����
};


#endif
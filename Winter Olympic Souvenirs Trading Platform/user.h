#ifndef _USER_H_
#define _USER_H_

using namespace std;

static int u_num = 0;

struct s_User {
	string u_id;
	string u_name;
	string u_password;
	string u_location;
	string u_phone_number;

	double u_money = 0;			//�˻����
	bool u_banned = false;		//�û�״̬
	int credibility = 100;		//�û�������
};

class User {
private:
	string u_name;
	string u_password;
	string u_location;
	string u_phone_number;
public:
	User(string id) {
		u_id = id;
	}
	User() {};

	void u_show_inf();			//��Ϣ�鿴
	void u_inf();				//��Ϣ����
	void u_update();
	void u_update_name();		
	void u_update_password();
	void u_update_address();
	void u_update_phone();

	void u_buyer_mode();		//���ģʽ
	void u_seller_mode();		//����ģʽ

	void u_recharge();			//��ֵ
	void u_notice();			//֪ͨϵͳ

	double u_money = 0;			//�˻����
	bool u_banned = false;		//�û�״̬
protected:
	string u_id;
	int credibility = 100;		//�û�������
};


void u_log_in();			//��¼
void u_register();			//�û�ע��



#endif
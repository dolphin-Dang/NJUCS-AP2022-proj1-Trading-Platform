#ifndef _USER_H_
#define _USER_H_

using namespace std;

struct s_User {
	string u_id;
	string u_name;
	string u_password;
	string u_location;
	string u_phone_number;

	double u_money = 0;			//账户余额
	bool u_banned = false;		//用户状态
	int credibility = 100;		//用户信誉分
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

	void u_show_inf();			//信息查看
	void u_inf();				//信息管理
	void u_update();
	void u_update_name();		
	void u_update_password();
	void u_update_address();
	void u_update_phone();

	void u_buyer_mode();		//买家模式
	void u_seller_mode();		//卖家模式

	void u_recharge();			//充值
	void u_notice();			//通知系统

	double u_money = 0;			//账户余额
	bool u_banned = false;		//用户状态
protected:
	string u_id;
	int credibility = 100;		//用户信誉分
};


void u_log_in();			//登录
void u_register();			//用户注册



#endif
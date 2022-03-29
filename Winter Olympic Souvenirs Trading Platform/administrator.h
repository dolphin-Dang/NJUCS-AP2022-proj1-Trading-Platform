#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

using namespace std;

class Administrator {
private:
	string a_id;
	string a_name;
	string a_password;
public:
	Administrator()
	{
		a_id = "U000";			//管理员ID默认为U000
		a_name = "dolphin";		//管理员名字默认为dolphin
		a_password = "123456";	//管理员密码默认为123456
	}
	void a_log_in();				//管理员登录
	void a_search_goods();			//（关键字）搜索商品
	void a_all_goods();				//查看所有商品（包括已下架、已售出）
	void a_remove_good();			//下架商品

	void a_all_orders();			//查看所有订单

	void a_all_users();				//查看所有用户
	void a_ban_user();				//封禁用户

	void a_argue();				//申诉系统
};


#endif
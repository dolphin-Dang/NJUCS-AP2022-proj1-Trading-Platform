#ifndef _SELLER_H_
#define _SELLER_H_

#include "user.h"

class Seller :public User {
public:
	Seller(string id) {
		u_id = id;
	}
	void s_my_goods();		//查看自己的商品（未售出、已售出）
	void s_post_good();		//发布新商品
	void s_remove_good();	//下架商品（不删除记录，状态改成下架）
	void s_update_good();	//商品信息更新
	void s_his_orders();	//查看历史订单
};

#endif
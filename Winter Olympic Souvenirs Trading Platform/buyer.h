#ifndef _BUYER_H_
#define _BUYER_H_

#include "user.h"

class Buyer :public User {
public:
	Buyer(string id) {
		u_id = id;
	}
	void b_buy();				//买商品，形成订单
	void b_judge();				//评价卖家，形成评价信息,提交描述(暂未完成)
	void b_all_goods();			//查看所有商品列表
	void b_search_good();		//搜索商品
	void b_his_orders();		//查看历史订单
	void b_good_detail();		//查看商品详情
};


#endif
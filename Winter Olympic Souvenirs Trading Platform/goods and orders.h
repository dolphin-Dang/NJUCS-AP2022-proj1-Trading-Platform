#ifndef _G_A_O_
#define _G_A_O_

#include <iostream>
using namespace std;

struct orders {
	string o_id = "T";
	string o_good_id;
	string o_time;
	string o_seller_id;
	string o_buyer_id;
	double o_all_price;
	int o_num;
};

struct goods {
	int num;
	int g_state;
	double g_price;
	string g_id;
	string g_name;
	string g_seller_id;
	string g_description;
};

#endif

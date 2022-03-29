#include <iostream>
#include "user.h"
#include "seller.h"
#include "buyer.h"
#include "print.h"
#include <fstream>
#include <string>
#include <vector>
#include "calculator.h"
#include "notice.h"
#include "helpers.h"

#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
extern string choice;

//返回第n个逗号所在位置

void User::u_inf()
{
	//system("cls");

	bool end_procedure = false;
	while (!end_procedure) {
		box_print("1.查看信息 2.修改信息 3.充值 4.返回用户主界面", '=');
		cout << "请选择操作：";

		//检查输入准确性
		if (!input_check(4)) {
			continue;
		}

		switch ((int)(choice[0]-'0')) {
		case 1:
			u_show_inf();
			break;
		case 2:
			u_update();
			break;
		case 3:
			u_recharge();
			break;
		case 4:
			//system("cls");
			end_procedure = true;
			break;
		}

	}
}

void User::u_show_inf()//查看信息：用户名 联系方式 地址 余额
{
	fstream fuser("users.txt");
	if (!fuser.is_open()) {
		cout << "Open failed!";
		exit(-1);
	}
	else {
		string lines, name, phone, address, money, state, credibility;
		//不可能找不到
		while (getline(fuser, lines)) {
			if (u_id == lines.substr(0, 4)) {
				name = lines.substr(find_comma(lines, 1) + 1, find_comma(lines, 2) - find_comma(lines, 1) - 1);
				phone = lines.substr(find_comma(lines, 3) + 1, find_comma(lines, 4) - find_comma(lines, 3) - 1);
				address = lines.substr(find_comma(lines, 4) + 1, find_comma(lines, 5) - find_comma(lines, 4) - 1);
				credibility = lines.substr(find_comma(lines, 6) + 1, find_comma(lines, 7) - find_comma(lines, 6) - 1);
				state = lines.substr(find_comma(lines, 7) + 1);
			}
		}

		if (phone == "") phone = "无";
		if (address == "") address = "无";

		//余额需要重新计算
		string expr;
		//充值记录
		ifstream recharge("recharge.txt");
		if (!recharge.is_open()) {
			cout << "Open failed!" << endl;
		}
		else {
			string lines;
			getline(recharge, lines);
			while (getline(recharge, lines)) {
				if (lines.substr(0, 4) == u_id) {
					expr = expr + lines.substr(find_comma(lines, 2)+1) + "+";
				}
			}
		}
		recharge.close();

		//卖出商品
		ifstream orders("orders.txt");
		if (!orders.is_open()) {
			cout << "Open failed!";
		}
		else {
			string lines;
			getline(orders, lines);
			while(getline(orders, lines)) {
				if (lines.substr(find_comma(lines, 5) + 1, find_comma(lines, 6) - find_comma(lines, 5) - 1) == u_id) {
					expr = expr + lines.substr(find_comma(lines, 3) + 1, find_comma(lines, 4) - find_comma(lines, 3) - 1) + "*" + \
						lines.substr(find_comma(lines, 2) + 1, find_comma(lines, 3) - find_comma(lines, 2) - 1) + "+";
				}
			}
		}
		orders.close();
		if (expr != "") expr = expr.substr(0, expr.length() - 1);

		//买入商品
		ifstream order("orders.txt");
		if (!order.is_open()) {
			cout << "Open failed!";
		}
		else {
			string lines;
			getline(order, lines);
			while (getline(order, lines)) {
				if (lines.substr(find_comma(lines, 6) + 1, find_comma(lines, 7) - find_comma(lines, 6) - 1) == u_id) {
					expr = expr + "-" + lines.substr(find_comma(lines, 3) + 1, find_comma(lines, 4) - find_comma(lines, 3) - 1) + "*" + \
						lines.substr(find_comma(lines, 2) + 1, find_comma(lines, 3) - find_comma(lines, 2) - 1);
				}
			}
		}
		order.close();

		expr = simplify(expr);
		money = calculator(expr);

		if (money == "") {
			money = "0.0";
		}

		//输出结果
		//system("cls");

		cout << "******************************" << endl;
		cout << "用户ID：\t" << u_id << endl;
		cout << "用户名：\t" << name << endl;
		cout << "联系方式：\t" << phone << endl;
		cout << "地址：\t\t" << address << endl;
		cout << "余额：\t\t" << money << endl;
		cout << "信誉分：\t" << credibility << endl;
		cout << "状态：\t\t" << state << endl;
		cout << "******************************" << endl;

		pause();
		//system("cls");
	}
}

void User::u_update()//修改信息
{
	bool end_procedure = false;
	while (!end_procedure) {
		cout << "请选择修改的属性（1.用户名 2.密码 3.联系方式 4.地址 5.取消）：";

		//检查输入准确性
		if (!input_check(5)) {
			continue;
		}

		switch ((int)(choice[0] - '0')) {
		case 1:
			u_update_name();
			end_procedure = true;
			break;
		case 2:
			u_update_password();
			end_procedure = true;
			break;
		case 3:
			u_update_phone();
			end_procedure = true;
			break;
		case 4:
			u_update_address();
			end_procedure = true;
			break;
		case 5:
			//system("cls");
			end_procedure = true;
			break;
		}
	}
}

void User::u_update_name()
{
	string name;
	cout << "请输入用户名（不超过10个英文字母或汉字）：";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	//检查用户名是否合法
	int len = 0;
	for (int i = 0; i < name.length(); i++) {
		len++;
		if (len > 10) {
			colorful_print("用户名不合法：长度大于10！", 4);
			pause();
			//system("cls");
			return;
		}
		if (name[i] < 0)i++;
	}

	for (int i = 0; i < name.length(); i++) {
		if (name[i] < 0)i++;
		else if (name[i] < 65 || (name[i] > 90 && name[i] < 97) || name[i]>122) {
			colorful_print("用户名不合法：有不合法字符！", 4);
			pause();
			//system("cls");
			return;
		}
	}
	if (name[name.length() - 1] == ' ' || name[0] == ' ') {
		colorful_print("用户名不合法：不能以空格开头或结尾！", 4);
		pause();
		//system("cls");
		return;
	}

	//用户名是否重复
	fstream name_check("users.txt");
	if (!name_check) {
		cout << "Open failed!";
		exit(-1);
	}
	else {
		string lines, names;
		getline(name_check, lines);//跳过第一行
		while (getline(name_check, lines)) {
			names = lines.substr(find_comma(lines, 1) + 1, find_comma(lines, 2) - find_comma(lines, 1) - 1);
			if (names == name) {
				if (u_id == lines.substr(0, 4)) {
					colorful_print("用户名不合法：不能与原用户名相同！", 4);
					pause();
					//system("cls");
					return;
				}
				else {
					colorful_print("用户名不合法：重复！", 4);
					pause();
					//system("cls");
					return;
				}
			}
		}
	}

	//都没问题
	change_txt(u_id, "users.txt", name, 1);

	cout << "——————修改成功——————";
	pause();
	//system("cls");
}

void User::u_update_password()
{
	string o_password, n_password;
	cout << "请输入现在的密码：";
	getline(cin, o_password);
	if (o_password == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	fstream user("users.txt");
	string password, lines;
	getline(user, lines);
	while (getline(user, lines)) {
		if (u_id == lines.substr(0, 4)) {
			password = lines.substr(find_comma(lines, 2) + 1, find_comma(lines, 3) - find_comma(lines, 2) - 1);
			if (password != o_password) {
				colorful_print("Error：密码错误！", 4);
				pause();
				//system("cls");
				return;
			}
			else {
				//密码正确
				cout << "请输入密码（不超过20个小写字母和数字）：";
				getline(cin, n_password);
				if (n_password == "") {
					colorful_print("Error：输入不能为空！", 4);
					pause();
					//system("cls");
					return;
				}
				//检查密码是否合法
				if (n_password.length() > 20) {
					colorful_print("密码不合法：长度大于20！", 4);
					pause();
					//system("cls");
					return;
				}
				for (int i = 0; i < n_password.length(); i++) {
					if (n_password[i] < 48 || (n_password[i] > 57 && n_password[i] < 97) || n_password[i]>122) {
						colorful_print("密码不合法：有不合法字符！", 4);
						pause();
						//system("cls");
						return;
					}
				}

				//再次输入密码
				string pas_check;
				cout << "请再次输入密码：";
				getline(cin, pas_check);
				if (pas_check != n_password) {
					colorful_print("Error：密码不一致！", 4);
					pause();
					//system("cls");
					return;
				}
			}

		}
	}

	change_txt(u_id, "users.txt", n_password, 2);

	cout << "——————修改成功——————";
	pause();
	//system("cls");
}

void User::u_update_address()
{
	string address;
	cout << "请输入地址（不超过20个字符）：";
	getline(cin, address);
	if (address == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}

	bool legal;
	legal =  chinese_length_check(address, 20);
	if (!legal) {
		colorful_print("地址不合法：长度大于20！", 4);
		pause();
		//system("cls");
		return;
	}
	else {
		for (int i = 0; i < address.length(); i++) {
			if (address[i] == ' ') {
				colorful_print("地址不合法：不能有空格！", 4);
				pause();
				//system("cls");
				return;
			}
			if (address[i] == ',') {
				colorful_print("地址不合法：不能有逗号！", 4);
				pause();
				//system("cls");
				return;
			}
			if (address[i] < 0)i++;
			else if (address[i] < 65 || (address[i] > 90 && address[i] < 97) || address[i]>122) {
				colorful_print("用户名不合法：有不合法字符！", 4);
				pause();
				//system("cls");
				return;
			}
		}

		change_txt(u_id, "users.txt", address, 4);

		cout << "——————修改成功——————";
		pause();
		//system("cls");
	}
}

void User::u_update_phone()
{
	string phone;
	cout << "请输入联系方式（不超过20个数字）：";
	getline(cin, phone);
	if (phone == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}

	//字符是否合法
	bool legal = true;
	for (int i = 0; i < phone.length(); i++) {
		if (phone[i] < '0' || phone[i]>'9') {
			legal = false;
		}
	}
	if (!legal) {
		colorful_print("联系方式不合法：有非数字！", 4);
		pause();
		//system("cls");
		return;
	}
	else if (phone.length() > 20) {
		colorful_print("联系方式不合法：长度大于20！", 4);
		pause();
		//system("cls");
		return;
	}
	else {
		change_txt(u_id, "users.txt", phone, 3);

		cout << "——————修改成功——————";
		pause();
		//system("cls");
	}
}

void User::u_recharge()//充值
{
	string money;
	cout << "请输入充值金额（整数或一位小数）：";
	getline(cin, money);
	if (money == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}

	//是否合法
	bool legal = true, integ = true;
	for (int i = 0; i < money.length(); i++) {
		if ((money[i] < '0' || money[i]>'9') && money[i] != '.') {
			legal = false;
			break;
		}
		if (money[i] == '.') {
			integ = false;
			if (i == 0) {
				colorful_print("充值金额不合法：小数点不能是第一位！", 4);
				pause();
				//system("cls");
				return;
			}
			else if (i + 1 == money.length()) {
				colorful_print("充值金额不合法：小数点后无数字！", 4);
				pause();
				//system("cls");
				return;
			}
			else if (i + 2 < money.length()) {
				colorful_print("充值金额不合法：至多一位小数！", 4);
				pause();
				//system("cls");
				return;
			}
		}
	}
	if (!legal) {
		colorful_print("充值金额不合法：有非法字符！", 4);
		pause();
		//system("cls");
		return;
	}
	
	//都合法
	//生成充值记录
	fstream recharge("recharge.txt", ios::app);
	if (!recharge.is_open()) {
		cout << "Open failed!" << endl;
	}
	else {
		recharge << u_id << "," << get_time() << "," << money << endl;
	}
	recharge.close();

	//增加余额
	fstream user("users.txt");
	string balance, lines;
	getline(user, lines);
	while (getline(user, lines)) {
		if (u_id == lines.substr(0, 4)) {
			balance = lines.substr(find_comma(lines, 5) + 1, find_comma(lines, 6) - find_comma(lines, 5) - 1);
			break;
		}
	}
	user.close();

	balance = calculator(balance + "+" + money);

	change_txt(u_id, "users.txt", balance, 5);

	cout << "——————充值成功——————";
	pause();
	//system("cls");
}

void User::u_buyer_mode()
{
	//system("cls");

	Buyer buyer(u_id);
	bool end_procedure = false;
	while (!end_procedure) {
		box_print("1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.评价卖家 7.返回用户主界面", '=');
		cout << "请选择操作：";

		//检查输入准确性
		if (!input_check(7)) {
			continue;
		}

		switch ((int)(choice[0] - '0')) {
		case 1:
			buyer.b_all_goods();
			break;
		case 2:
			buyer.b_buy();
			break;
		case 3:
			buyer.b_search_good();
			break;
		case 4:
			buyer.b_his_orders();
			break;
		case 5:
			buyer.b_good_detail();
			break;
		case 6:
			buyer.b_judge();
			break;
		case 7:
			//system("cls");
			end_procedure = true;
			break;
		}

	}

}

void User::u_seller_mode()
{
	//system("cls");

	Seller seller(u_id);
	bool end_procedure = false;
	while (!end_procedure) {
		box_print("1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面", '=');
		cout << "请选择操作：";

		//检查输入准确性
		if (!input_check(6)) {
			continue;
		}

		switch ((int)(choice[0] - '0')) {
		case 1:
			seller.s_post_good();
			break;
		case 2:
			seller.s_my_goods();
			break;
		case 3:
			seller.s_update_good();
			break;
		case 4:
			seller.s_remove_good();
			break;
		case 5:
			seller.s_his_orders();
			break;
		case 6:
			//system("cls");
			end_procedure = true;
			break;
		}

	}

}

void u_log_in()
{
	string name, password;
	cout << "请输入用户名：";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	cout << "请输入密码：";
	getline(cin, password);
	if (password == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	fstream fuser;
	fuser.open("users.txt");
	if (!fuser.is_open()) {
		cout << "Open failed!";
		exit(-1);
	}
	else {
		string names, passwords, lines, id;
		int name_b, name_e, pas_b = 0, pas_e;
		getline(fuser, lines);
		//寻找用户名和密码
		string state;
		bool login = false;
		while (getline(fuser, lines)) {
			for (int i = 0; i < lines.length(); i++) {
				if (lines[i] == ',') {
					name_b = i + 1;
					for (int j = i + 1; j < lines.length(); j++) {
						if (lines[j] == ',') {
							name_e = j - 1;
							names = lines.substr(name_b, name_e - name_b + 1);
							if (names == name) {
								pas_b = j + 1;
								for (int k = j + 1; k < lines.length(); k++) {
									if (lines[k] == ',') {
										pas_e = k - 1;
										passwords = lines.substr(pas_b, pas_e - pas_b + 1);
										if (passwords == password) {
											login = true;
											id = lines.substr(0, 4);
											state = lines.substr(lines.length() - 6, 6);
										}
										else {
											colorful_print("密码错误！", 4);
											pause();
											//system("cls");
											return;
										}
									}
									if (login) {
										break;
									}
								}
							}
						}
						if (login) {
							break;
						}
					}

				}
				if (login) {
					break;
				}
			}
		}
		if (!login) {
			colorful_print("Error：用户不存在！", 4);
			pause();
			//system("cls");
			return;
		}

		//是否封禁
		if (state == "banned") {
			colorful_print("该用户已被封禁！", 4);
			pause();
			//system("cls");
			return;
		}
		else {
			cout << "——————登陆成功——————";
			pause();
			//system("cls");
		}


		//登录成功：
		User user(id);
		bool end_procedure = false;
		while (!end_procedure) {
			box_print("1.我是买家 2.我是卖家 3.个人信息管理 4.我的通知 5.退出登录", '=');
			cout << "请选择操作：";

			//检查输入准确性
			if (!input_check(5)) {
				continue;
			}

			switch ((int)(choice[0] - '0')) {
			case 1:
				//system("cls");
				user.u_buyer_mode();
				break;
			case 2:
				//system("cls");
				user.u_seller_mode();
				break;
			case 3:
				//system("cls");
				user.u_inf();
				break;
			case 4:
				//system("cls");
				user.u_notice();
				break;
			case 5:
				//system("cls");
				end_procedure = true;
				break;
			}
		}
	}
}

void u_register()
{	
	string name, password;
	cout << "请输入用户名（不超过10个英文字母或汉字）：";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	//检查用户名是否合法
	int len = 0;
	for (int i = 0; i < name.length(); i++) {
		len++;
		if (len > 10) {
			colorful_print("用户名不合法：长度大于10！", 4);
			pause();
			//system("cls");
			return;
		}
		if (name[i] < 0)i++;
	}

	for (int i = 0; i < name.length(); i++) {
		if (name[i] < 0)i++;
		else if (name[i] < 65 || (name[i] > 90 && name[i] < 97) || name[i]>122) {
			colorful_print("用户名不合法：有不合法字符！", 4);
			pause();
			//system("cls");
			return;
		}
	}
	if (name[name.length() - 1] == ' ' || name[0] == ' ') {
		colorful_print("用户名不合法：不能以空格开头或结尾！", 4);
		pause();
		//system("cls");
		return;
	}

	//用户名是否重复
	fstream name_check("users.txt");
	if (!name_check) {
		cout << "Open failed!";
		exit(-1);
	}
	else {
		string lines, names;
		int name_b, name_e;
		getline(name_check, lines);//跳过第一行
		while (getline(name_check, lines)) {
			for (int i = 0; i < lines.length(); i++) {
				if (lines[i] == ',') {
					name_b = i + 1;
					for (int j = i; j < lines.length(); j++) {
						if (lines[j] == ',') {
							name_e = j - 1;
							names = lines.substr(name_b, name_e - name_b + 1);
							if (names == name) {
								colorful_print("用户名不合法：重复！", 4);
								pause();
								//system("cls");
								return;
							}
						}
					}
					
				}
			}
		}
	}

	cout << "请输入密码（不超过20个小写字母和数字）：";
	getline(cin, password);
	if (password == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	//检查密码是否合法
	if (password.length() > 20) {
		colorful_print("密码不合法：长度大于20！", 4);
		pause();
		//system("cls");
		return;
	}
	for (int i = 0; i < password.length(); i++) {
		if (password[i] < 48 || (password[i] > 57 && password[i] < 97) || password[i]>122) {
			colorful_print("密码不合法：有不合法字符！", 4); 
			pause();
			//system("cls");
			return;
		}
	}

	//再次输入密码
	string pas_check;
	cout << "请再次输入密码：";
	getline(cin, pas_check);
	if (pas_check != password) {
		colorful_print("Error：密码不一致！", 4);
		pause();
		//system("cls");
		return;
	}

	//都合法
	string last_id;
	fstream users("users.txt");
	if (!users.is_open()) {
		cout << "Open failed!";
	}
	else {
		string lines;
		getline(users, lines);
		while (getline(users, lines)) {
			last_id = lines.substr(0, 4);
		}
	}
	users.close();

	fstream user;
	user.open("users.txt", ios::app);
	if (!user.is_open()) {
		cout << "Open failed!";
	}
	else {
		//用户ID
		if (last_id == "") {
			last_id = "U001";
		}
		else {
			last_id[0] = '1';
			int u_num = atoi(last_id.c_str());
			u_num++;
			last_id = to_string(u_num);
			last_id[0] = 'U';
		}
		user << last_id << ',';

		//用户名和密码
		user << name << "," << password << ",";

		//其他
		user << ",,0.0,无,active" << endl;
	}
	user.close();

	cout << "——————注册成功——————" << endl;
	pause();
	//system("cls");
}

void User::u_notice()
{
	//system("cls");

	bool end_procedure = false;
	while (!end_procedure) {
		//system("cls");
		box_print("1.查看新消息 2.查看历史消息 3.评价申诉 4.返回主界面", '=');
		cout << "请选择操作：";

		//检查输入准确性
		if (!input_check(4)) {
			continue;
		}

		//通知编号,发送时间,发送者ID,接收者ID,是否已读,通知内容
		vector<string> notice;
		if ((int)choice[0] - '0' != 4) {
			fstream helper("notice.txt");
			string lines;
			while (getline(helper, lines)) {
				if (cut(lines, 3, ',') == u_id) {
					notice.push_back(lines);
				}
			}
			helper.close();
		}

		switch ((int)(choice[0] - '0')) {
		case 1:
		{
			bool have_new = false;
			for (int i = 0; i < notice.size(); i++) {
				if (cut(notice[i], 4, ',') == "否") {
					have_new = true;

					cout << endl;
					int length = max(notice[i].length() - find_comma(notice[i], 5) - 1, find_comma(notice[i], 2) + 1) + 10;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "发送时间：" << cut(notice[i], 1, ',') << endl;
					cout << "发送者ID：" << cut(notice[i], 2, ',') << endl;
					cout << "通知内容：" << cut(notice[i], 5, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;

					change_txt(notice[i].substr(0, 4), "notice.txt", "是", 4);
				}
			}
			if (!have_new) {
				cout << endl;
				box_print("您没有新的消息！", '=');
			}
			pause();
			break; 
		}
		case 2:
		{
			bool have_new = false;
			for (int i = 0; i < notice.size(); i++) {
				if (cut(notice[i], 4, ',') == "是") {
					have_new = true;

					cout << endl;
					int length = max(notice[i].length() - find_comma(notice[i], 5) - 1, find_comma(notice[i], 2) + 1) + 10;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "发送时间：" << cut(notice[i], 1, ',') << endl;
					cout << "发送者ID：" << cut(notice[i], 2, ',') << endl;
					cout << "通知内容：" << cut(notice[i], 5, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
				}
			}
			if (!have_new) {
				cout << endl;
				box_print("您没有历史消息！", '=');
			}
			pause();
			break;
		}
		case 3:
		{
			fstream comment("comments.txt");
			vector<string> comments;
			string lines;
			getline(comment, lines);
			while (getline(comment, lines)) {
				if (cut(lines, 6, ',') != "无效") {
					comments.push_back(lines);
				}
			}
			comment.close();

			if (comments.size() == 0) {
				cout << endl;
				box_print("您没有历史评价！", '=');
				pause();
				break;
			}
			else {
				for (int i = 0; i < comments.size(); i++) {
					int length = cut(comments[i], 1, ',').length() + 10;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "评价ID：\t" << comments[i].substr(0,4) << endl;
					cout << "评价时间：\t" << cut(comments[i], 1, ',') << endl;
					cout << "评价者ID：\t" << cut(comments[i], 2, ',') << endl;
					cout << "订单ID：\t" << cut(comments[i], 4, ',') << endl;
					cout << "评分：\t\t" << cut(comments[i], 5, ',') << endl;
					cout << "状态：\t\t"<< cut(comments[i], 6, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
				}
			}

			//有历史评价
			string id;
			cout << "请输入你要申诉的评价ID:";
			getline(cin, id);
			if (id == "") {
				colorful_print("Error：输入不能为空！", 4);
				pause();
				//system("cls");
				return;
			}
			if (id.length() != 4 || id[0] != 'C' || !is_num(id[1]) || !is_num(id[2]) || !is_num(id[3])) {
				colorful_print("评价ID错误！", 4);
				pause();
				//system("cls");
				return;
			}

			cout << endl;

			bool have_comment = false;
			for (int i = 0; i < comments.size(); i++) {
				if (comments[i].substr(0, 4) == id) {
					have_comment = true;
				}
			}

			if (!have_comment) {
				colorful_print("评价ID错误！", 4);
				pause();
				//system("cls");
				return;
			}
			else {
				int i = 0;
				for (; i < comments.size(); i++) {
					if (comments[i].substr(0, 4) == id) {
						break;
					}
				}
				//是否正在申诉
				if (cut(comments[i], 6, ',') == "申诉中") {
					colorful_print("该评价正在申诉中！", 4);
					pause();
					//system("cls");
					return;
				}
				//是否已经被驳回
				fstream argues("argue.txt");
				string lines;
				while (getline(argues, lines)) {
					if (cut(lines, 3, ',') == id && cut(lines, 5, ',') == "已驳回") {
						colorful_print("针对此评价的申诉已被驳回！", 4);
						pause();
						//system("cls");
						return;
					}
				}
				argues.close();

				do {
					int length = cut(comments[i], 1, ',').length() + 10;
					cout << "您要向管理员申诉的评价是：" << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "评价ID：\t" << comments[i].substr(0, 4) << endl;
					cout << "评价时间：\t" << cut(comments[i], 1, ',') << endl;
					cout << "评价者ID：\t" << cut(comments[i], 2, ',') << endl;
					cout << "订单ID：\t" << cut(comments[i], 4, ',') << endl;
					cout << "评分：\t\t" << cut(comments[i], 5, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;

					//再次确认
					cout << "是否确认申诉？(y/n)：";
					string check;
					getline(cin, check);
					if (check == "") {
						colorful_print("Error：输入不能为空！", 4);
						pause();
						//system("cls");
						return;
					}
					if (check.length() == 1 && check[0] == 'y') {
						argue(id);
						return;
					}
					else if (check.length() == 1 && check[0] == 'n') {
						cout << endl;
						cout << "——————申诉取消——————";
						pause();
						//system("cls");
						return;
					}
					else {
						colorful_print("输入非法！请重新输入！", 4);
						pause();
						//system("cls");
						continue;
					}
				} while (true);
			}

			break;//对应switch case 的 braek
		}
		case 4:
			end_procedure = true;
			//system("cls");
			break;
		}

	}
}

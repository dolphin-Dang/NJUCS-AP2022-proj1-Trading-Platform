#include <iostream>
#include "seller.h"
#include "command.h"
#include "print.h"
#include <fstream>
#include <string>
#include "helpers.h"

using namespace std;
extern string choice;

void Seller::s_my_goods()
{
	string command = "SELECT * FROM commodity";
	solve_command(command, 's', u_id);
}

void Seller::s_his_orders()
{
	string command = "SELECT * FROM order";
	solve_command(command, 's', u_id);
}

void Seller::s_post_good()
{
	string command = "INSERT INTO commodity VALUES ";
	string name, money, num, account;

	//检查商品名称是否合法
	cout << "请输入商品名称：";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	bool name_len_legal = chinese_length_check(name, 10);
	if (!name_len_legal) {
		colorful_print("商品名称不合法：长度大于10！", 4);
		pause();
		//system("cls");
		return;
	}
	for (int i = 0; i < name.length(); i++) {
		if (name[i] < 0)i++;
		else if (name[i] < 65 || (name[i] > 90 && name[i] < 97) || name[i]>122) {
			colorful_print("商品名称不合法：有不合法字符！", 4);
			pause();
			//system("cls");
			return;
		}
	}
	if (name[name.length() - 1] == ' ' || name[0] == ' ') {
		colorful_print("商品名称不合法：不能以空格开头或结尾！", 4);
		pause();
		//system("cls");
		return;
	}

	
	//商品价格是否合法
	cout << "请输入商品价格：";
	getline(cin, money);
	if (money == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	if (money[0] == '0') {
		colorful_print("商品价格不合法：不能以0开头！", 4);
		pause();
		//system("cls");
		return;
	}
	if (money[0] == '-') {
		colorful_print("商品价格不合法：不能是负数！", 4);
		pause();
		//system("cls");
		return;
	}
	bool legal = true, integ = true;
	for (int i = 0; i < money.length(); i++) {
		if ((money[i] < '0' || money[i]>'9') && money[i] != '.') {
			legal = false;
			break;
		}
		if (money[i] == '.') {
			integ = false;
			if (i == 0) {
				colorful_print("商品价格不合法：小数点不能是第一位！", 4);
				pause();
				//system("cls");
				return;
			}
			else if (i + 1 == money.length()) {
				colorful_print("商品价格不合法：小数点后无数字！", 4);
				pause();
				//system("cls");
				return;
			}
			else if (i + 2 < money.length()) {
				colorful_print("商品价格不合法：至多一位小数！", 4);
				pause();
				//system("cls");
				return;
			}
		}
	}
	if (!legal) {
		colorful_print("商品价格不合法：有非法字符！", 4);
		pause();
		//system("cls");
		return;
	}

	//商品个数是否合法
	cout << "请输入商品个数：";
	getline(cin, num);
	if (num == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	if (num[0] == '0') {
		colorful_print("商品个数不合法：不能以0开头！", 4);
		pause();
		//system("cls");
		return;
	}
	if (num[0] == '-') {
		colorful_print("商品个数不合法：不能是负数！", 4);
		pause();
		//system("cls");
		return;
	}
	for (int i = 0; i < num.length(); i++) {
		if (num[i] < '0' || num[i]>'9') {
			colorful_print("商品个数不合法：有非法字符！", 4);
			pause();
			//system("cls");
			return;
		}
	}

	cout << "请输入商品描述：";
	getline(cin, account);
	if (account == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	for (int i = 0; i < account.length(); i++) {
		if (account[i] == ',') {
			colorful_print("商品描述不合法：含有非法字符‘,’！", 4);
			pause();
			//system("cls");
			return;
		}
	}
	bool account_len_legal = chinese_length_check(account, 100);
	if (!account_len_legal) {
		colorful_print("商品描述不合法：长度大于100！", 4);
		pause();
		//system("cls");
		return;
	}

	//都合法：
	cout << endl;

	string check;
	do {
		cout << "请确认发布商品信息无误：" << endl;
		cout << "*************************" << endl;
		cout << "商品名称：" << name << endl;
		cout << "商品价格：" << money << endl;
		cout << "商品个数：" << num << endl;
		cout << "商品描述：" << account << endl;
		cout << "*************************" << endl;
		cout << endl;

		cout << "是否确认发布？(y/n)：";
		getline(cin, check);
		if (check == "") {
			colorful_print("Error：输入不能为空！", 4);
			pause();
			//system("cls");
			return;
		}
		if (check.length() == 1 && check[0] == 'y') {
			command = command + "(" + name + "," + money + "," + num + "," + account + ")";
			solve_command(command, 's', u_id);

			return;
		}
		else if (check.length() == 1 && check[0] == 'n') {
			cout << endl;
			cout << "——————发布取消——————";
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

void Seller::s_remove_good()
{
	string command = "DELETE FROM commodity WHERE ID = ";
	string good_id;
	cout << "请输入要下架的商品ID：";
	getline(cin, good_id);
	if (good_id == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	if (good_id.length() != 4 || good_id[0] != 'M' || !is_num(good_id[1]) || !is_num(good_id[2]) || !is_num(good_id[3])) {
		colorful_print("商品ID错误！", 4);
		pause();
		//system("cls");
		return;
	}

	fstream goods("commodity.txt");
	string lines;
	bool good_found = false;
	getline(goods, lines);
	while (getline(goods, lines)) {
		if (good_id == lines.substr(0, 4)) {
			good_found = true;
			break;
		}
	}
	goods.close();
	if (!good_found) {
		colorful_print("商品不存在！", 4);
		pause();
		//system("cls");
		return;
	}

	command = command + good_id;
	solve_command(command, 's');

}

void Seller::s_update_good()
{
	string command = "UPDATE commodity SET ";
	string good_id, money, account, name;

	cout << "请输入被修改的商品ID：";
	getline(cin, good_id);
	if (good_id == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		//system("cls");
		return;
	}
	if (good_id.length() != 4 || good_id[0] != 'M' || !is_num(good_id[1]) || !is_num(good_id[2]) || !is_num(good_id[3])) {
		colorful_print("商品ID错误！", 4);
		pause();
		//system("cls");
		return;
	}

	//取出用户id 商品名
	fstream goods("commodity.txt");
	string lines,user_id;
	bool name_found = false;
	getline(goods, lines);
	while (getline(goods, lines)) {
		if (good_id == lines.substr(0, 4)) {
			user_id = lines.substr(find_comma(lines, 5) + 1, find_comma(lines, 6) - find_comma(lines, 5) - 1);
			name = lines.substr(find_comma(lines, 1) + 1, find_comma(lines, 2) - find_comma(lines, 1) - 1);
			name_found = true;
			break;
		}
	}
	goods.close();
	
	if (!name_found) {
		colorful_print("商品不存在！", 4);
		pause();
		//system("cls");
		return;
	}

	if (u_id != user_id) {
		colorful_print("这不是你的商品！", 4);
		pause();
		//system("cls");
		return;
	}

	string chr;
	cout << "请输入修改的商品属性（1.价格 2.描述）";
	getline(cin,chr);
	if (chr.length() != 1 || !is_num(chr[0])) {
		colorful_print("Error：非法输入！", 4);
		pause();
		//system("cls");
		return;
	}
	int ch = (chr[0] - '0');
	if (ch != 1 && ch != 2) {
		colorful_print("Error：非法输入！", 4);
		pause();
		//system("cls");
		return;
	}
	else if (ch == 1) {
		cout << "请输入修改的商品价格：";
		getline(cin, money);
		if (money == "") {
			colorful_print("Error：输入不能为空！", 4);
			pause();
			//system("cls");
			return;
		}
		if (money[0] == '0') {
			colorful_print("商品价格不合法：不能以0开头！", 4);
			pause();
			//system("cls");
			return;
		}
		if (money[0] == '-') {
			colorful_print("商品价格不合法：不能是负数！", 4);
			pause();
			//system("cls");
			return;
		}
		bool legal = true, integ = true;
		for (int i = 0; i < money.length(); i++) {
			if ((money[i] < '0' || money[i]>'9') && money[i] != '.') {
				legal = false;
				break;
			}
			if (money[i] == '.') {
				integ = false;
				if (i == 0) {
					colorful_print("商品价格不合法：小数点不能是第一位！", 4);
					pause();
					//system("cls");
					return;
				}
				else if (i + 1 == money.length()) {
					colorful_print("商品价格不合法：小数点后无数字！", 4);
					pause();
					//system("cls");
					return;
				}
				else if (i + 2 < money.length()) {
					colorful_print("商品价格不合法：至多一位小数！", 4);
					pause();
					//system("cls");
					return;
				}
			}
		}
		if (!legal) {
			colorful_print("商品价格不合法：有非法字符！", 4);
			pause();
			//system("cls");
			return;
		}
	}
	else {
		cout << "请输入修改的商品描述：";
		getline(cin, account);
		if (account == "") {
			colorful_print("Error：输入不能为空！", 4);
			pause();
			//system("cls");
			return;
		}
		for (int i = 0; i < account.length(); i++) {
			if (account[i] == ',') {
				colorful_print("商品描述不合法：含有非法字符‘, ’！", 4);
				pause();
				//system("cls");
				return;
			}
		}
		bool account_len_legal = chinese_length_check(account, 20);
		if (!account_len_legal) {
			colorful_print("商品描述不合法：长度大于20！", 4);
			pause();
			//system("cls");
			return;
		}
	}

	//都合法：
	cout << endl;
	string check;
	do {
		cout << "请确认修改的商品信息无误：" << endl;
		cout << "*************************" << endl;
		cout << "商品ID：\t" << good_id << endl;
		cout << "商品名称：\t" << name << endl;
		if (ch == 1) {
			cout << "商品价格：\t" << money << endl;
		}
		else {
			cout << "商品描述：\t" << account << endl;
		}
		cout << "*************************" << endl;
		cout << endl;

		cout << "是否确认修改？(y/n)：";
		getline(cin, check);
		if (check == "") {
			colorful_print("Error：输入不能为空！", 4);
			pause();
			//system("cls");
			return;
		}

		if (check.length() == 1 && check[0] == 'y') {
			string command_app = " WHERE ID = " + good_id;
			if (ch == 1) {
				command = command + "价格 = " + money + command_app;
			}
			else if (ch == 2) {
				command = command + "描述 = " + account + command_app;
			}
			solve_command(command, 's');

			return;
		}
		else if (check.length() == 1 && check[0] == 'n') {
			cout << endl;
			cout << "——————修改取消——————";
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

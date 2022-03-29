#include <iostream>
#include "administrator.h"
#include "print.h"
#include "command.h"
#include <fstream>
#include <string>
#include "notice.h"
#include <vector>
#include "helpers.h"

using namespace std;

extern string choice;

void Administrator:: a_log_in()
{
	string name, password;

	cout << "请输入管理员名称：";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		////system("cls");
		return;
	}
	cout << "请输入密码：";
	getline(cin, password);
	if (password == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		////system("cls");
		return;
	}

	if (name != a_name || password != a_password) {
		colorful_print("用户名或密码错误，登陆失败！", 4);
		pause();
		////system("cls");
		return;
	}
	
	cout << "——————登陆成功——————" << endl;
	pause();

	bool end_procedure = false;
	while (!end_procedure) {
		////system("cls");
		box_print("1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.申诉通知 8.注销", '=');
		cout << "请选择操作：";

		if (!input_check(8)) {
			continue;
		}

		switch ((int)(choice[0] - '0')) {
		case 1:
			a_all_goods();
			break;
		case 2:
			a_search_goods();
			break;
		case 3:
			a_remove_good();
			break;
		case 4:
			a_all_orders();
			break;
		case 5:
			a_all_users();
			break;
		case 6:
			a_ban_user();
			break;
		case 7:
			a_argue();
			break;
		case 8:
			end_procedure = true;
			////system("cls");
			break;
		}
	}
}

void Administrator::a_search_goods()
{
	string command, good_name;
	cout << "请输入商品名：";
	getline(cin, good_name);
	if (good_name == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		////system("cls");
		return;
	}
	command = "SELECT * FROM commodity WHERE 名称 CONTAINS " + good_name;
	solve_command(command, 'a');

}

void Administrator::a_all_goods()
{
	string command = "SELECT * FROM commodity";
	solve_command(command, 'a');
}

void Administrator::a_all_orders()
{
	string command;
	command = "SELECT * FROM orders";
	solve_command(command, 'a');
}

void Administrator::a_all_users()
{
	string command;
	command = "SELECT * FROM users";
	solve_command(command, 'a');
}

void Administrator::a_ban_user()
{
	string command, user_id;
	cout << "请输入用户ID：";
	getline(cin, user_id);
	if (user_id == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		////system("cls");
		return;
	}
	if (user_id.length() != 4 || user_id[0] != 'U' || !is_num(user_id[1]) || !is_num(user_id[2]) || !is_num(user_id[3])) {
		colorful_print("用户ID错误！", 4);
		pause();
		////system("cls");
		return;
	}
	command = "DELETE FROM users WHERE ID = " + user_id;
	solve_command(command, 'a');
	
}

void Administrator::a_remove_good()
{
	string command, good_id;
	cout << "请输入商品ID：";
	getline(cin, good_id);
	if (good_id == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		////system("cls");
		return;
	}
	if (good_id.length() != 4 || good_id[0] != 'M' || !is_num(good_id[1]) || !is_num(good_id[2]) || !is_num(good_id[3])) {
		colorful_print("商品ID错误！", 4);
		pause();
		////system("cls");
		return;
	}

	fstream goods("commodity.txt");
	string lines, s_id;
	bool good_found = false;
	getline(goods, lines);
	while (getline(goods, lines)) {
		if (good_id == lines.substr(0, 4)) {
			good_found = true;
			s_id = cut(lines, 5, ',');
			break;
		}
	}
	goods.close();
	if (!good_found) {
		colorful_print("商品不存在！", 4);
		pause();
		////system("cls");
		return;
	}

	command = "DELETE FROM commodity WHERE ID = " + good_id;
	solve_command(command, 'a');

	send_notice("admin", good_id, s_id);
}

void Administrator::a_argue()
{
	////system("cls");
	fstream argue("argue.txt");
	string lines;
	vector<string> argues;
	getline(argue, lines);
	while (getline(argue, lines)) {
		if (cut(lines, 5, ',') == "未处理") {
			argues.push_back(lines);
		}
	}
	argue.close();

	if (argues.size() == 0) {
		box_print("暂无卖家申诉！", '=');
		pause();
		return;
	}
	else {
		for (int i = 0; i < argues.size(); i++) {
			int length = max(cut(argues[i],1,',').length(), cut(argues[i], 4, ',').length()) + 16;
			for (int j = 0; j < length; j++) cout << '=';
			cout << endl;
			cout << "申诉编号：\t" << argues[i].substr(0, 4) << endl;
			cout << "申诉时间：\t" << cut(argues[i], 1, ',') << endl;
			cout << "申诉人ID：\t" << cut(argues[i], 2, ',') << endl;
			string reason = cut(argues[i], 4, ',');
			int k = 0;
			for (; k < reason.length(); k++) {
				if (reason[k] == ')') {
					break;
				}
			}
			cout << "申诉理由：\t" << reason.substr(k + 1) << endl;
			cout << "评分：\t\t" << reason.substr(1, k - 1) << endl;
			for (int j = 0; j < length; j++) cout << '=';
			cout << endl;
		}

		//有申诉
		string id;
		cout << "请输入你处理的申诉ID:";
		getline(cin, id);
		if (id == "") {
			colorful_print("Error：输入不能为空！", 4);
			pause();
			//system("cls");
			return;
		}
		if (id.length() != 4 || id[0] != 'A' || !is_num(id[1]) || !is_num(id[2]) || !is_num(id[3])) {
			colorful_print("申诉ID错误！", 4);
			pause();
			////system("cls");
			return;
		}

		bool have_argue = false;
		for (int i = 0; i < argues.size(); i++) {
			if (argues[i].substr(0, 4) == id) {
				have_argue = true;
			}
		}

		if (!have_argue) {
			colorful_print("申诉ID错误！", 4);
			pause();
			////system("cls");
			return;
		}
		else {//id正确
			int i = 0;
			for (; i < argues.size(); i++) {
				if (argues[i].substr(0, 4) == id) {
					break;
				}
			}

			cout << endl;
			box_print("请选择对此条申诉的操作：1.同意申诉，撤销评价 2.驳回申诉，维持原样", '=');
			cout << "请输入你的选择：";

			//检查输入准确性
			if (!input_check(2)) {
				return;
			}

			switch ((int)(choice[0] - '0')) {
			case 1:
				rejudge(id);
				break;
			case 2:
				reject(id);
				break;
			}
		}
	}
}
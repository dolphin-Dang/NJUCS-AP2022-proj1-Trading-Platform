#include <iostream>
#include "notice.h"
#include <fstream>
#include <string>
#include "print.h"
#include <Windows.h>

using namespace std;

extern string get_time();
extern string get_time_sec();
extern string cut(string s, int n, char c);
extern void change_txt(string id, string txt, string inf, int n);
extern bool chinese_length_check(string s, int n);
extern string cal_cred(string id);

//admin下架商品  用户购买商品  用户评价卖家
void send_notice(string u_id, string id, string receiver)
{
	string last_id;
	fstream notice("notice.txt");
	if (!notice.is_open()) {
		cout << "Open failed!";
	}
	else {
		string lines;
		getline(notice, lines);
		while (getline(notice, lines)) {
			last_id = lines.substr(0, 4);
		}
	}
	notice.close();

	fstream notice1;
	notice1.open("notice.txt");
	if (!notice1.is_open()) {
		cout << "Open failed!";
	}
	else {
		//用户ID
		if (last_id == "") {
			last_id = "N001";
		}
		else {
			last_id[0] = '1';
			int u_num = atoi(last_id.c_str());
			u_num++;
			last_id = to_string(u_num);
			last_id[0] = 'N';
		}
	}
	notice1.close();

	if (u_id == "admin") {
		if (id[0] == 'M') {
			fstream notice("notice.txt", ios::app);
			notice << last_id << ',' << get_time() << " " << get_time_sec() << ',' << u_id << ',' << receiver << ',' << "否" << ',' << \
				"您的商品（ID " << id << "）已被管理员下架！" << endl;
			notice.close();
		}
		else if (id[0] == 'A') {
			fstream argue("argue.txt");
			string lines, state, c_id;
			while (getline(argue, lines)) {
				if (lines.substr(0, 4) == id) {
					state = cut(lines, 5, ',').substr(2);
					c_id = cut(lines, 3, ',');
					break;
				}
			}
			argue.close();


			fstream notice("notice.txt", ios::app);
			notice << last_id << ',' << get_time() << " " << get_time_sec() << ',' << u_id << ',' << receiver << ',' << "否" << ',' << \
				"您对评价（ID "<< c_id <<")的申诉（ID " << id << "）已被管理员" << state << "！" << endl;
			notice.close();
		}
	}
	else {
		if (id[0] == 'M') {
			string name, num, g_name, lines;
			//商品数量
			fstream order("orders.txt");
			while (getline(order, lines)) {
				if (cut(lines, 1, ',') == id) {
					num = cut(lines, 3, ',');
				}
			}
			order.close();
			//用户名
			fstream user("users.txt");
			while (getline(user, lines)) {
				if (lines.substr(0,4) == u_id) {
					name = cut(lines, 1, ',');
				}
			}
			user.close();
			//商品名
			fstream good("commodity.txt");
			while (getline(good, lines)) {
				if (lines.substr(0, 4) == id) {
					g_name = cut(lines, 1, ',');
				}
			}
			user.close();

			fstream notice("notice.txt", ios::app);
			notice << last_id << ',' << get_time() << " " << get_time_sec() << ',' << u_id << ',' << receiver << \
				',' << "否" << ',' << "用户" << name << "（ID:" << u_id << "）购买了" \
				<< num << "个您的商品"<< g_name << "（ID: " << id << "）！" << endl;
			notice.close();
		}
		else if (id[0] == 'T') {
			string lines, score;
			fstream comment("comments.txt");
			while (getline(comment, lines)) {
				if (cut(lines, 4, ',') == id) {
					score = cut(lines, 5, ',');
					break;
				}
			}
			comment.close();

			fstream notice("notice.txt", ios::app);
			notice << last_id << ',' << get_time() << " " << get_time_sec() << ',' << u_id << ',' << receiver << ',' << "否" << ',' << \
				"买家（ID:"<< u_id <<"）评价了您的交易（ID " << id << "）：" << score << "分" << endl;
			notice.close();
		}
	}
}

void argue(string c_id)
{
	//申诉编号,申诉时间,申诉者ID,评价编号,申诉理由,处理状态
	string comment, score;
	fstream helper("comments.txt");
	string lines;
	while (getline(helper, lines)) {
		if (lines.substr(0, 4) == c_id) {
			comment = lines;
			score = cut(lines, 5, ',');
			break;
		}
	}

	//生成编号
	string last_id;
	fstream argue("argue.txt");
	if (!argue.is_open()) {
		cout << "Open failed!";
	}
	else {
		string lines;
		getline(argue, lines);
		while (getline(argue, lines)) {
			last_id = lines.substr(0, 4);
		}
	}
	argue.close();

	fstream argue1;
	argue1.open("argue.txt", ios::app);
	if (!argue1.is_open()) {
		cout << "Open failed!";
	}
	else {
		//用户ID
		if (last_id == "") {
			last_id = "A001";
		}
		else {
			last_id[0] = '1';
			int u_num = atoi(last_id.c_str());
			u_num++;
			last_id = to_string(u_num);
			last_id[0] = 'A';
		}

		cout << endl;
		cout << "请输入申诉理由：";
		string reason;
		getline(cin, reason);
		if (reason == "") {
			colorful_print("Error：输入不能为空！", 4);
			system("pause");
			system("cls");
			argue1.close();
			return;
		}
		for (int i = 0; i < reason.length(); i++) {
			if (reason[i] == ',') {
				colorful_print("申诉理由不合法：含有非法字符‘, ’！", 4);
				system("pause");
				system("cls");
				argue1.close();
				return;
			}
		}
		bool account_len_legal = chinese_length_check(reason, 100);
		if (!account_len_legal) {
			colorful_print("申诉理由不合法：长度大于100！", 4);
			system("pause");
			system("cls");
			argue1.close();
			return;
		}

		argue1 << last_id << ',' << get_time() << ' ' << get_time_sec() << ',' << cut(comment, 3, ',') \
			<< ',' << c_id << ",(" << score << ")" << reason << ',' << "未处理" << endl;

		change_txt(c_id, "comments.txt", "申诉中", 6);

		cout << "——————申诉成功——————" << endl;
	}
	argue1.close();

	system("pause");
	system("cls");
}

void rejudge(string a_id)
{
	fstream argue("argue.txt");
	string lines, s_id, c_id;
	getline(argue, lines);
	while (getline(argue, lines)) {
		if (a_id == lines.substr(0, 4)) {
			s_id = cut(lines, 2, ',');
			c_id = cut(lines, 3, ',');
			break;
		}
	}
	argue.close();

	change_txt(a_id, "argue.txt", "已同意", 5);
	change_txt(c_id, "comments.txt", "无效", 6);

	cal_cred(s_id);
	send_notice("admin", a_id, s_id);
}

void reject(string a_id)
{
	fstream argue("argue.txt");
	string lines, s_id, c_id;
	getline(argue, lines);
	while (getline(argue, lines)) {
		if (a_id == lines.substr(0, 4)) {
			s_id = cut(lines, 2, ',');
			c_id = cut(lines, 3, ',');
			break;
		}
	}
	argue.close();

	change_txt(a_id, "argue.txt", "已驳回", 5);
	change_txt(c_id, "comments.txt", "有效", 6);

	send_notice("admin", a_id, s_id);
}

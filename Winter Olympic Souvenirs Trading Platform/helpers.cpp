#include <iostream>
#include "helpers.h"
#include <string>
#include "print.h"
#include <fstream>
#include <vector>
#include "calculator.h"

using namespace std;
extern string choice;

bool input_check(int n) 
{
	getline(cin, choice);
	if (choice == "") {
		colorful_print("Error：输入不能为空！", 4);
		pause();
		////system("cls");
		return false;
	}
	if (choice.length() > 1 || choice.length() == 0) {
		colorful_print("ERROR:请输入正确的选项！\n", 4);
		pause();
		////system("cls");
		return false;
	}
	if (choice[0] < '1' || choice[0] > '0' + n) {
		colorful_print("ERROR:请输入正确的选项！\n", 4);
		pause();
		////system("cls");
		return false;
	}
	else {
		return true;
	}
}

//判断是否是加减乘除括号
bool is_signal(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '(') {
		return true;
	}
	return false;
}
//判断是否是加减乘除
bool is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/') {
		return true;
	}
	return false;
}
//判断是否是数字
bool is_num(char c)
{
	if (c > 47 && c < 58) {
		return true;
	}
	return false;
}

//获得订单年月日信息
string get_time()
{
	string ret;
	// 基于当前系统的当前日期/时间
	time_t now = time(0);
	tm* ltm = localtime(&now);
	ret = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);

	return ret;
}


string get_time_sec()
{
	string ret;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	ret = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);

	return ret;
}

//切出第n个char后的string
string cut(string s, int n, char c)
{
	string ret;
	int space = 0;

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == c) {
			space++;
		}
		if (space == n) {
			if (n != 0) {
				ret = s.substr(i + 1);
			}
			else {
				ret = s;
			}
			break;
		}
	}
	if (space < n)return "404";

	for (int i = 0; i < ret.length(); i++) {
		if (ret[i] == c) {
			ret = ret.substr(0, i);
			break;
		}
	}

	return ret;
}

int find_comma(string s, int n)
{
	int cnt = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ',') {
			cnt++;
			if (cnt == n) {
				return i;
			}
		}
	}
	return 0;
}

//修改文件信息
void change_txt(string id, string txt, string inf, int n)	//ID 文件名 修改的信息 第几个逗号后
{
	ifstream fin(txt);
	string lines;
	vector<string>inform;

	while (getline(fin, lines)) {
		if (id == lines.substr(0, 4)) {
			if (find_comma(lines, n + 1) == 0) {
				lines = lines.substr(0, find_comma(lines, n) + 1) + inf;
			}
			else {
				lines = lines.substr(0, find_comma(lines, n) + 1) + inf + lines.substr(find_comma(lines, n + 1));
			}
		}
		inform.push_back(lines);
	}
	fin.close();

	ofstream fout(txt);
	for (int i = 0; i < inform.size(); i++) {
		fout << inform[i] << endl;
	}
	fout.close();

}

//字符长度是否合法
bool chinese_length_check(string s, int n)
{
	int len = 0;
	for (int i = 0; i < s.length(); i++) {
		len++;
		if (len > n) {
			return false;
		}
		if (s[i] < 0)i++;
	}
	return true;
}

//计算信誉分
string cal_cred(string id)
{
	string expr, ans;
	string lines;
	int cnt = 0;
	fstream helper("comments.txt");
	getline(helper, lines);
	while (getline(helper, lines)) {
		if (id == cut(lines, 3, ',') && cut(lines, 6, ',') != "无效") {
			cnt++;
			expr += cut(lines, 5, ',') + "+";
		}
	}

	if (cnt == 0) {
		ans = "无";
	}
	else {
		helper.close();
		expr = "(" + expr.substr(0, expr.length() - 1) + ")/" + to_string(cnt);
		ans = calculator(expr);
	}
	return ans;
}

void pause()
{
	cout << "请输入任意键继续......";
	string line;
	getline(cin, line);
}
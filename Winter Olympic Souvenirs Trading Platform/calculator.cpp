#include <iostream>
#include <math.h>
#include "calculator.h"
#include <string>
#include <vector>

using namespace std;

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
//判断括号是否匹配
bool match_parentheses(string s)
{
	int len = s.length();
	int match = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '(') {
			match++;
		}
		else if (s[i] == ')') {
			match--;
		}
		if (match < 0) {
			return true;
		}
	}
	if (match > 0) {
		return true;
	}
	return false;
}
//移除空格 如果空格有问题则返回单个空格 不然返回去除空格后的式子
string remove_space(string s)
{
	int len = s.length();
	for (int i = 0; i < len; i++) {
		if (s[i] == ' ') {
			if (i != 0 && i != len - 1) {
				if (is_num(s[i - 1]) && is_num(s[i + 1])) {			//前后都是数字
					return " ";
				}
				else if (s[i - 1] == '.' || s[i + 1] == '.') {		//前后有小数点
					return " ";
				}
			}
			s.erase(i, 1);
			i--;
			len--;
		}
	}
	return s;
}
//操作符使用是否有误 如果有问题就返回问题 不然返回空格
string operator_usage(string s)
{
	//是否有两个连续的操作符
	//数字和括号之间是否有操作符
	//一个数字内有几个小数点
	//'('前')'后是否有数字
	//0之后不能直接出现数字

	int len = s.length();
	int dot_num = 0;
	for (int i = 0; i < len; i++) {
		//检查符号是否合法
		if (!is_signal(s[i]) && (s[i] < 48 || s[i] > 57) && s[i] != '.') {
			return "表达式中含有不合法符号";
		}

		//检查是否有两个连续的操作符
		//开头不能是加乘除	结尾不能是加减乘除
		if (i == 0 || i == len - 1) {		//开头结尾
			if (is_operator(s[i]) && s[i] != '-') {
				return "操作符误用";
			}
		}
		else {		//中间部分
			if (is_operator(s[i])) {
				//中间部分加减乘除前后都不能是加减乘除
				if (is_operator(s[i - 1]) || is_operator(s[i + 1])) {
					return "操作符误用";
				}
				//加乘除前不能是'('，加减乘除后不能是')'
				if ((s[i] != '-' && s[i - 1] == '(') || s[i + 1] == ')') {
					return "操作符误用";
				}
				//'('前')'后只能是运算符
				if ((s[i] == '(' && is_signal(s[i - 1])) || (s[i] == ')' && is_signal(s[i + 1]))) {
					return "操作符误用";
				}
			}
		}

		//检查小数点
		if (s[i] == '.') {

			//检查一个数字里有几个小数点
			for (int j = i + 1; !is_signal(s[j]) && j < len; j++) {
				if (s[j] == '.') {
					return "小数点使用错误";
				}
			}

			//检查小数点周围是否有数字
			if (i == 0 || i == len - 1) {
				return "小数点使用错误";
			}
			else {
				if (!is_num(s[i - 1]) || !is_num(s[i + 1])) {
					return "小数点使用错误";
				}
			}
		}

		//'('前')'后是否有数字
		if ((s[i] == '(' && i != 0 && is_num(s[i - 1])) || (s[i] == ')' && i != len - 1 && is_num(s[i + 1]))) {
			return "操作符误用";
		}

		//排除00形式
		if (s[i] == '0' && (i==0||!is_num(s[i-1]))) {
			bool still = false;
			for (int j = i + 1; j < len; j++) {
				if (s[j] == '0') {
					if (j == len - 1)return "形如00不是一个合法数字";
					else {
						still = true;
						continue;
					}
				}
				else if ((j == len - 1 || is_signal(s[j])) && still) {
					return "形如00不是一个合法数字";
				}
				else {
					break;
				}
			}
		}

		//0之后有无数字
		if (s[i] == '0' && i < len - 1 && is_num(s[i + 1])) {
			if (i == 0 || (!is_num(s[i - 1]) && s[i - 1] != '.')) {
				return "非零数不能以0开头";
			}
		}

		//检查除数为零
		if (s[i] == '/') {
			if (i + 2 == len) {
				if (s[i + 1] == '0') return "除数不能为零";
			}
			else {
				if (s[i + 1] == '0' && is_signal(s[i + 2]) || s.substr(i + 1, 3) == "0.0") return "除数不能为零";
			}
		}

	}
	return " ";
}
//计算
string calculate(string s)
{
	//基本思路：递归解决
	//先用递归解决所有括号
	//再用数组存储数字和操作符，将括号递归解决
	//如果计算结果是正数则直接返回正数 如果是负数则返回值带括号

	int len = s.length();

	//遍历解决括号问题
	int dismatches = 0;				//不匹配的括号数量
	int begin = -1, end = -1;		//括号的开始和结束
	for (int i = 0; i < len; i++) {
		if (s[i] == '(') {
			if (dismatches == 0) {
				begin = i;
			}
			dismatches++;
		}
		if (s[i] == ')') {
			dismatches--;
			if (dismatches == 0) {
				//解决括号内只有一个数的问题	负数不管   正数去括号(利用递归)
				bool only_nega = true;
				bool only_posi = false;
				for (int j = i - 1; s[j] != '('; j--) {
					if (is_operator(s[j]) && s[j] != '-') {
						only_nega = false;
						break;
					}
					else if (is_num(s[j]) && s[j - 1] == '(') {
						only_posi = true;
					}
				}
				if (!only_nega || only_posi) {
					end = i;
					string substr = calculate(s.substr(begin + 1, end - begin - 1));
					s = s.substr(0, begin) + substr + s.substr(end + 1);
					//调整len和i的值
					int delta = end - begin + 1 - substr.length();	//式子长度变化
					len -= delta;
					i -= delta;
				}
			}
		}
	}

	//完成计算
	//此时式子中只有数字和加减乘除，括号只出现在负数周围
	//如果计算结果是负数则需要返回括号
	//判断整个式子最前面有无负号
	len = s.length();
	if (s[0] == '-') {

		//负号后面是数字
		if (is_num(s[1])) {
			for (int j = 2; j < len; j++) {
				if (is_operator(s[j])) {
					s = "(" + s.substr(0, j) + ")" + s.substr(j);
					break;
				}
			}
		}
		//负号后面是括号:先去掉"-(-",再在后面去掉一个")"
		else if (s[1] == '(') {
			s = s.substr(3);
			for (int j = 0; j < len - 3; j++) {
				if (s[j] == ')') {
					s = s.erase(j, 1);
					break;
				}
			}
		}

	}
	//将所有数字和运算符取出放到vector里
	vector<double>operands(0);
	vector<char>operators;
	//double operands[100] = { 0 };
	//char operators[100];
	bool negative = false;				//是不是负数
	int cnt = 0;						//数字的数量 = 运算符的数量 + 1
	begin = -1;
	end = -1;							//begin == - 1 代表不在一个数字中
	len = s.length();
	for (int i = 0; i < len; i++) {
		if (is_operator(s[i])) {
			//operators[cnt] = s[i];
			operators.push_back(s[i]);
			cnt++;
			begin = -1;
			negative = false;
		}
		else if (is_num(s[i])) {
			if (begin == -1) {
				begin = i;
			}
			if ((i + 1 < len && is_signal(s[i + 1])) || i + 1 == len) {
				end = i;
				if (negative) {
					//operands[cnt] = -1 * atof(s.substr(begin, end - begin + 1).c_str());
					operands.push_back(-1 * atof(s.substr(begin, end - begin + 1).c_str()));
				}
				else {
					//operands[cnt] = atof(s.substr(begin, end - begin + 1).c_str());
					operands.push_back(atof(s.substr(begin, end - begin + 1).c_str()));
				}
			}
		}
		else if (s[i] == '(') {
			i++;
			negative = true;
		}
	}
	//此时有cnt+1个数字	下面计算得出结果
	//两次遍历 第一次计算所有乘除 第二次计算所有加减
	//第一次
	for (int i = 0; i < cnt; i++) {
		if (operators[i] == '*') {
			operands[i] *= operands[i + 1];
			for (int j = i; j < cnt - 1; j++) {
				operators[j] = operators[j + 1];
				operands[j + 1] = operands[j + 2];
			}
			i--;
			cnt--;
		}
		else if (operators[i] == '/') {
			operands[i] /= operands[i + 1];
			for (int j = i; j < cnt - 1; j++) {
				operators[j] = operators[j + 1];
				operands[j + 1] = operands[j + 2];
			}
			i--;
			cnt--;
		}
	}
	//第二次
	for (int i = 0; i < cnt; i++) {
		if (operators[i] == '+') {
			operands[0] += operands[i + 1];
		}
		else if (operators[i] == '-') {
			operands[0] -= operands[i + 1];
		}
	}

	//将数字转换成string
	//判断正负
	if (operands[0] < 0) {
		negative = true;
		operands[0] *= -1;
	}
	else {
		negative = false;
	}

	string ret = to_string(operands[0]);
	//判断正负输出
	if (!negative) {
		return ret;
	}
	else {
		return "(-" + ret + ")";
	}
}

string calculator(string s)
{
	//计算过程中最多保留三位小数	计算结束后输出一位小数（四舍五入）

	//一个括号内最多有100个数字+内层括号	理论上能完成最大一万个最小一百个数的计算   足矣！

	if (s == "") {
		return "";
	}


	//检查表达式是否合法
	//括号匹配
	if (match_parentheses(s)) {
		return "括号不匹配";
	}

	//空格问题
	s = remove_space(s);
	if (" " == s) {
		return "在不合理位置出现空格";
	}

	//操作符是否有误
	string check = operator_usage(s);
	if (check != " ") {
		return check;
	}

	//计算 得出结果
	s = calculate(s);
	if (s[0] == '(') {
		s = s.substr(1, s.length() - 2);
	}

	double ans = atof(s.c_str());
	int temp = (int)floor(ans * 100);
	int ret;
	if (temp % 10 > 4) {
		ret = ceil(ans * 10);
	}
	else {
		ret = floor(ans * 10);
	}

	s = to_string((double)ret / 10);
	s = s.substr(0, s.length() - 5);

	return s;
}

string simplify(string s)
{
	//把要化简的部分放在vector里
	vector<vector<string>>vec;
	string num, price;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '*') {
			//如果是乘法 先找到乘号前的num 在vector中找有没有一样的
			for (int j = i; j >= 0; j--) {
				if (s[j] == '+' || s[j] == '-' || j == 0) {
					if (j == 0) num = s.substr(0, i);
					else num = s.substr(j + 1, i - j - 1);
					bool found = false;
					//在vector中找有无一样
					for (int v = 0; v < vec.size(); v++) {
						if (vec[v][0] == num) {
							//找到了一样的
							found = true;
							bool last = true;
							for (int k = i; k < s.length(); k++) {
								//不是最后一个数
								if (s[k] == '+' || s[k] == '-') {
									if (!is_num(s[j])) {
										price = s[j] + s.substr(i + 1, k - i - 1);
									}
									else {
										price = "+" + s.substr(i + 1, k - i - 1);
									}
									vec[v].push_back(price);
									last = false;
								}
							}
							//是最后一个数
							if (last) {
								if (!is_num(s[j])) {
									price = s[j] + s.substr(i + 1);
								}
								else {
									price = "+" + s.substr(i + 1);
								}
								vec[v].push_back(price);
							}
							break;
						}
					}
					if (!found) {
						vector<string>temp;
						temp.push_back(num);
						vec.push_back(temp);
						i--;//再来一次把数字放进去
					}
					break;
				}
			}
		}
	}

	//取出前面不用化简部分
	bool only_recharge = true;
	int last_operator = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '+' || s[i] == '-') {
			only_recharge = false;
			last_operator = i;
		}
		else if (s[i] == '*') {
			only_recharge = false;
			break;
		}
	}
	if (only_recharge) {
		return s;
	}
	else if (last_operator != 0) {
		s = s.substr(0, last_operator);
	}
	else {
		s = "";
	}

	for (int i = 0; i < vec.size(); i++) {
		string temp;
		for (int j = 1; j < vec[i].size(); j++) {
			if (j == 1 && vec[i][j][0] == '+') {
				temp = vec[i][j].substr(1);//去掉第一个+
			}
			else temp = temp + vec[i][j];
		}
		if (s == "") {
			s = vec[i][0] + "*" + "(" + temp + ")";
		}
		else {
			s = s + "+" + vec[i][0] + "*" + "(" + temp + ")";
		}
	}

	return s;
}
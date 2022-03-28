#include <iostream>
#include <math.h>
#include "calculator.h"
#include <string>
#include <vector>

using namespace std;

//�ж��Ƿ��ǼӼ��˳�����
bool is_signal(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '(') {
		return true;
	}
	return false;
}
//�ж��Ƿ��ǼӼ��˳�
bool is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/') {
		return true;
	}
	return false;
}
//�ж��Ƿ�������
bool is_num(char c)
{
	if (c > 47 && c < 58) {
		return true;
	}
	return false;
}
//�ж������Ƿ�ƥ��
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
//�Ƴ��ո� ����ո��������򷵻ص����ո� ��Ȼ����ȥ���ո���ʽ��
string remove_space(string s)
{
	int len = s.length();
	for (int i = 0; i < len; i++) {
		if (s[i] == ' ') {
			if (i != 0 && i != len - 1) {
				if (is_num(s[i - 1]) && is_num(s[i + 1])) {			//ǰ��������
					return " ";
				}
				else if (s[i - 1] == '.' || s[i + 1] == '.') {		//ǰ����С����
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
//������ʹ���Ƿ����� ���������ͷ������� ��Ȼ���ؿո�
string operator_usage(string s)
{
	//�Ƿ������������Ĳ�����
	//���ֺ�����֮���Ƿ��в�����
	//һ���������м���С����
	//'('ǰ')'���Ƿ�������
	//0֮����ֱ�ӳ�������

	int len = s.length();
	int dot_num = 0;
	for (int i = 0; i < len; i++) {
		//�������Ƿ�Ϸ�
		if (!is_signal(s[i]) && (s[i] < 48 || s[i] > 57) && s[i] != '.') {
			return "���ʽ�к��в��Ϸ�����";
		}

		//����Ƿ������������Ĳ�����
		//��ͷ�����Ǽӳ˳�	��β�����ǼӼ��˳�
		if (i == 0 || i == len - 1) {		//��ͷ��β
			if (is_operator(s[i]) && s[i] != '-') {
				return "����������";
			}
		}
		else {		//�м䲿��
			if (is_operator(s[i])) {
				//�м䲿�ּӼ��˳�ǰ�󶼲����ǼӼ��˳�
				if (is_operator(s[i - 1]) || is_operator(s[i + 1])) {
					return "����������";
				}
				//�ӳ˳�ǰ������'('���Ӽ��˳�������')'
				if ((s[i] != '-' && s[i - 1] == '(') || s[i + 1] == ')') {
					return "����������";
				}
				//'('ǰ')'��ֻ���������
				if ((s[i] == '(' && is_signal(s[i - 1])) || (s[i] == ')' && is_signal(s[i + 1]))) {
					return "����������";
				}
			}
		}

		//���С����
		if (s[i] == '.') {

			//���һ���������м���С����
			for (int j = i + 1; !is_signal(s[j]) && j < len; j++) {
				if (s[j] == '.') {
					return "С����ʹ�ô���";
				}
			}

			//���С������Χ�Ƿ�������
			if (i == 0 || i == len - 1) {
				return "С����ʹ�ô���";
			}
			else {
				if (!is_num(s[i - 1]) || !is_num(s[i + 1])) {
					return "С����ʹ�ô���";
				}
			}
		}

		//'('ǰ')'���Ƿ�������
		if ((s[i] == '(' && i != 0 && is_num(s[i - 1])) || (s[i] == ')' && i != len - 1 && is_num(s[i + 1]))) {
			return "����������";
		}

		//�ų�00��ʽ
		if (s[i] == '0' && (i==0||!is_num(s[i-1]))) {
			bool still = false;
			for (int j = i + 1; j < len; j++) {
				if (s[j] == '0') {
					if (j == len - 1)return "����00����һ���Ϸ�����";
					else {
						still = true;
						continue;
					}
				}
				else if ((j == len - 1 || is_signal(s[j])) && still) {
					return "����00����һ���Ϸ�����";
				}
				else {
					break;
				}
			}
		}

		//0֮����������
		if (s[i] == '0' && i < len - 1 && is_num(s[i + 1])) {
			if (i == 0 || (!is_num(s[i - 1]) && s[i - 1] != '.')) {
				return "������������0��ͷ";
			}
		}

		//������Ϊ��
		if (s[i] == '/') {
			if (i + 2 == len) {
				if (s[i + 1] == '0') return "��������Ϊ��";
			}
			else {
				if (s[i + 1] == '0' && is_signal(s[i + 2]) || s.substr(i + 1, 3) == "0.0") return "��������Ϊ��";
			}
		}

	}
	return " ";
}
//����
string calculate(string s)
{
	//����˼·���ݹ���
	//���õݹ�����������
	//��������洢���ֺͲ������������ŵݹ���
	//�����������������ֱ�ӷ������� ����Ǹ����򷵻�ֵ������

	int len = s.length();

	//���������������
	int dismatches = 0;				//��ƥ�����������
	int begin = -1, end = -1;		//���ŵĿ�ʼ�ͽ���
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
				//���������ֻ��һ����������	��������   ����ȥ����(���õݹ�)
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
					//����len��i��ֵ
					int delta = end - begin + 1 - substr.length();	//ʽ�ӳ��ȱ仯
					len -= delta;
					i -= delta;
				}
			}
		}
	}

	//��ɼ���
	//��ʱʽ����ֻ�����ֺͼӼ��˳�������ֻ�����ڸ�����Χ
	//����������Ǹ�������Ҫ��������
	//�ж�����ʽ����ǰ�����޸���
	len = s.length();
	if (s[0] == '-') {

		//���ź���������
		if (is_num(s[1])) {
			for (int j = 2; j < len; j++) {
				if (is_operator(s[j])) {
					s = "(" + s.substr(0, j) + ")" + s.substr(j);
					break;
				}
			}
		}
		//���ź���������:��ȥ��"-(-",���ں���ȥ��һ��")"
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
	//���������ֺ������ȡ���ŵ�vector��
	vector<double>operands(0);
	vector<char>operators;
	//double operands[100] = { 0 };
	//char operators[100];
	bool negative = false;				//�ǲ��Ǹ���
	int cnt = 0;						//���ֵ����� = ����������� + 1
	begin = -1;
	end = -1;							//begin == - 1 ������һ��������
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
	//��ʱ��cnt+1������	�������ó����
	//���α��� ��һ�μ������г˳� �ڶ��μ������мӼ�
	//��һ��
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
	//�ڶ���
	for (int i = 0; i < cnt; i++) {
		if (operators[i] == '+') {
			operands[0] += operands[i + 1];
		}
		else if (operators[i] == '-') {
			operands[0] -= operands[i + 1];
		}
	}

	//������ת����string
	//�ж�����
	if (operands[0] < 0) {
		negative = true;
		operands[0] *= -1;
	}
	else {
		negative = false;
	}

	string ret = to_string(operands[0]);
	//�ж��������
	if (!negative) {
		return ret;
	}
	else {
		return "(-" + ret + ")";
	}
}

string calculator(string s)
{
	//�����������ౣ����λС��	������������һλС�����������룩

	//һ�������������100������+�ڲ�����	��������������һ�����Сһ�ٸ����ļ���   ���ӣ�

	if (s == "") {
		return "";
	}


	//�����ʽ�Ƿ�Ϸ�
	//����ƥ��
	if (match_parentheses(s)) {
		return "���Ų�ƥ��";
	}

	//�ո�����
	s = remove_space(s);
	if (" " == s) {
		return "�ڲ�����λ�ó��ֿո�";
	}

	//�������Ƿ�����
	string check = operator_usage(s);
	if (check != " ") {
		return check;
	}

	//���� �ó����
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
	//��Ҫ����Ĳ��ַ���vector��
	vector<vector<string>>vec;
	string num, price;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '*') {
			//����ǳ˷� ���ҵ��˺�ǰ��num ��vector������û��һ����
			for (int j = i; j >= 0; j--) {
				if (s[j] == '+' || s[j] == '-' || j == 0) {
					if (j == 0) num = s.substr(0, i);
					else num = s.substr(j + 1, i - j - 1);
					bool found = false;
					//��vector��������һ��
					for (int v = 0; v < vec.size(); v++) {
						if (vec[v][0] == num) {
							//�ҵ���һ����
							found = true;
							bool last = true;
							for (int k = i; k < s.length(); k++) {
								//�������һ����
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
							//�����һ����
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
						i--;//����һ�ΰ����ַŽ�ȥ
					}
					break;
				}
			}
		}
	}

	//ȡ��ǰ�治�û��򲿷�
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
				temp = vec[i][j].substr(1);//ȥ����һ��+
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
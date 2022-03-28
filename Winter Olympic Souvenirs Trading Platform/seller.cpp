#include <iostream>
#include "seller.h"
#include "command.h"
#include "print.h"
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

extern bool is_num(char c);
extern bool chinese_length_check(string s, int n);
extern int find_comma(string s, int n);

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

	//�����Ʒ�����Ƿ�Ϸ�
	cout << "��������Ʒ���ƣ�";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	bool name_len_legal = chinese_length_check(name, 10);
	if (!name_len_legal) {
		colorful_print("��Ʒ���Ʋ��Ϸ������ȴ���10��", 4);
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < name.length(); i++) {
		if (name[i] < 0)i++;
		else if (name[i] < 65 || (name[i] > 90 && name[i] < 97) || name[i]>122) {
			colorful_print("��Ʒ���Ʋ��Ϸ����в��Ϸ��ַ���", 4);
			system("pause");
			system("cls");
			return;
		}
	}
	if (name[name.length() - 1] == ' ' || name[0] == ' ') {
		colorful_print("��Ʒ���Ʋ��Ϸ��������Կո�ͷ���β��", 4);
		system("pause");
		system("cls");
		return;
	}

	
	//��Ʒ�۸��Ƿ�Ϸ�
	cout << "��������Ʒ�۸�";
	getline(cin, money);
	if (money == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	if (money[0] == '0') {
		colorful_print("��Ʒ�۸񲻺Ϸ���������0��ͷ��", 4);
		system("pause");
		system("cls");
		return;
	}
	if (money[0] == '-') {
		colorful_print("��Ʒ�۸񲻺Ϸ��������Ǹ�����", 4);
		system("pause");
		system("cls");
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
				colorful_print("��Ʒ�۸񲻺Ϸ���С���㲻���ǵ�һλ��", 4);
				system("pause");
				system("cls");
				return;
			}
			else if (i + 1 == money.length()) {
				colorful_print("��Ʒ�۸񲻺Ϸ���С����������֣�", 4);
				system("pause");
				system("cls");
				return;
			}
			else if (i + 2 < money.length()) {
				colorful_print("��Ʒ�۸񲻺Ϸ�������һλС����", 4);
				system("pause");
				system("cls");
				return;
			}
		}
	}
	if (!legal) {
		colorful_print("��Ʒ�۸񲻺Ϸ����зǷ��ַ���", 4);
		system("pause");
		system("cls");
		return;
	}

	//��Ʒ�����Ƿ�Ϸ�
	cout << "��������Ʒ������";
	getline(cin, num);
	if (num == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	if (num[0] == '0') {
		colorful_print("��Ʒ�������Ϸ���������0��ͷ��", 4);
		system("pause");
		system("cls");
		return;
	}
	if (num[0] == '-') {
		colorful_print("��Ʒ�������Ϸ��������Ǹ�����", 4);
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < num.length(); i++) {
		if (num[i] < '0' || num[i]>'9') {
			colorful_print("��Ʒ�������Ϸ����зǷ��ַ���", 4);
			system("pause");
			system("cls");
			return;
		}
	}

	cout << "��������Ʒ������";
	getline(cin, account);
	if (account == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < account.length(); i++) {
		if (account[i] == ',') {
			colorful_print("��Ʒ�������Ϸ������зǷ��ַ���,����", 4);
			system("pause");
			system("cls");
			return;
		}
	}
	bool account_len_legal = chinese_length_check(account, 100);
	if (!account_len_legal) {
		colorful_print("��Ʒ�������Ϸ������ȴ���100��", 4);
		system("pause");
		system("cls");
		return;
	}

	//���Ϸ���
	cout << endl;

	string check;
	do {
		cout << "��ȷ�Ϸ�����Ʒ��Ϣ����" << endl;
		cout << "*************************" << endl;
		cout << "��Ʒ���ƣ�" << name << endl;
		cout << "��Ʒ�۸�" << money << endl;
		cout << "��Ʒ������" << num << endl;
		cout << "��Ʒ������" << account << endl;
		cout << "*************************" << endl;
		cout << endl;

		cout << "�Ƿ�ȷ�Ϸ�����(y/n)��";
		getline(cin, check);
		if (check == "") {
			colorful_print("Error�����벻��Ϊ�գ�", 4);
			system("pause");
			system("cls");
			return;
		}
		if (check.length() == 1 && check[0] == 'y') {
			command = command + "(" + name + "," + money + "," + num + "," + account + ")";
			solve_command(command, 's', u_id);

			return;
		}
		else if (check.length() == 1 && check[0] == 'n') {
			cout << endl;
			cout << "����������������ȡ��������������";
			system("pause");
			system("cls");
			return;
		}
		else {
			colorful_print("����Ƿ������������룡", 4);
			system("pause");
			system("cls");
			continue;
		}
		
	} while (true);
	
}

void Seller::s_remove_good()
{
	string command = "DELETE FROM commodity WHERE ID = ";
	string good_id;
	cout << "������Ҫ�¼ܵ���ƷID��";
	getline(cin, good_id);
	if (good_id == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	if (good_id.length() != 4 || good_id[0] != 'M' || !is_num(good_id[1]) || !is_num(good_id[2]) || !is_num(good_id[3])) {
		colorful_print("��ƷID����", 4);
		system("pause");
		system("cls");
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
		colorful_print("��Ʒ�����ڣ�", 4);
		system("pause");
		system("cls");
		return;
	}

	command = command + good_id;
	solve_command(command, 's');

}

void Seller::s_update_good()
{
	string command = "UPDATE commodity SET ";
	string good_id, money, account, name;

	cout << "�����뱻�޸ĵ���ƷID��";
	getline(cin, good_id);
	if (good_id == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	if (good_id.length() != 4 || good_id[0] != 'M' || !is_num(good_id[1]) || !is_num(good_id[2]) || !is_num(good_id[3])) {
		colorful_print("��ƷID����", 4);
		system("pause");
		system("cls");
		return;
	}

	//ȡ���û�id ��Ʒ��
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
		colorful_print("��Ʒ�����ڣ�", 4);
		system("pause");
		system("cls");
		return;
	}

	if (u_id != user_id) {
		colorful_print("�ⲻ�������Ʒ��", 4);
		system("pause");
		system("cls");
		return;
	}

	string chr;
	cout << "�������޸ĵ���Ʒ���ԣ�1.�۸� 2.������";
	getline(cin,chr);
	if (chr.length() != 1 || !is_num(chr[0])) {
		colorful_print("Error���Ƿ����룡", 4);
		system("pause");
		system("cls");
		return;
	}
	int ch = (chr[0] - '0');
	if (ch != 1 && ch != 2) {
		colorful_print("Error���Ƿ����룡", 4);
		system("pause");
		system("cls");
		return;
	}
	else if (ch == 1) {
		cout << "�������޸ĵ���Ʒ�۸�";
		getline(cin, money);
		if (money == "") {
			colorful_print("Error�����벻��Ϊ�գ�", 4);
			system("pause");
			system("cls");
			return;
		}
		if (money[0] == '0') {
			colorful_print("��Ʒ�۸񲻺Ϸ���������0��ͷ��", 4);
			system("pause");
			system("cls");
			return;
		}
		if (money[0] == '-') {
			colorful_print("��Ʒ�۸񲻺Ϸ��������Ǹ�����", 4);
			system("pause");
			system("cls");
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
					colorful_print("��Ʒ�۸񲻺Ϸ���С���㲻���ǵ�һλ��", 4);
					system("pause");
					system("cls");
					return;
				}
				else if (i + 1 == money.length()) {
					colorful_print("��Ʒ�۸񲻺Ϸ���С����������֣�", 4);
					system("pause");
					system("cls");
					return;
				}
				else if (i + 2 < money.length()) {
					colorful_print("��Ʒ�۸񲻺Ϸ�������һλС����", 4);
					system("pause");
					system("cls");
					return;
				}
			}
		}
		if (!legal) {
			colorful_print("��Ʒ�۸񲻺Ϸ����зǷ��ַ���", 4);
			system("pause");
			system("cls");
			return;
		}
	}
	else {
		cout << "�������޸ĵ���Ʒ������";
		getline(cin, account);
		if (account == "") {
			colorful_print("Error�����벻��Ϊ�գ�", 4);
			system("pause");
			system("cls");
			return;
		}
		for (int i = 0; i < account.length(); i++) {
			if (account[i] == ',') {
				colorful_print("��Ʒ�������Ϸ������зǷ��ַ���, ����", 4);
				system("pause");
				system("cls");
				return;
			}
		}
		bool account_len_legal = chinese_length_check(account, 20);
		if (!account_len_legal) {
			colorful_print("��Ʒ�������Ϸ������ȴ���20��", 4);
			system("pause");
			system("cls");
			return;
		}
	}

	//���Ϸ���
	cout << endl;
	string check;
	do {
		cout << "��ȷ���޸ĵ���Ʒ��Ϣ����" << endl;
		cout << "*************************" << endl;
		cout << "��ƷID��\t" << good_id << endl;
		cout << "��Ʒ���ƣ�\t" << name << endl;
		if (ch == 1) {
			cout << "��Ʒ�۸�\t" << money << endl;
		}
		else {
			cout << "��Ʒ������\t" << account << endl;
		}
		cout << "*************************" << endl;
		cout << endl;

		cout << "�Ƿ�ȷ���޸ģ�(y/n)��";
		getline(cin, check);
		if (check == "") {
			colorful_print("Error�����벻��Ϊ�գ�", 4);
			system("pause");
			system("cls");
			return;
		}

		if (check.length() == 1 && check[0] == 'y') {
			string command_app = " WHERE ID = " + good_id;
			if (ch == 1) {
				command = command + "�۸� = " + money + command_app;
			}
			else if (ch == 2) {
				command = command + "���� = " + account + command_app;
			}
			solve_command(command, 's');

			return;
		}
		else if (check.length() == 1 && check[0] == 'n') {
			cout << endl;
			cout << "�������������޸�ȡ��������������";
			Sleep(500);
			system("cls");
			return;
		}
		else {
			colorful_print("����Ƿ������������룡", 4);
			system("pause");
			system("cls");
			continue;
		}

	} while (true);
}

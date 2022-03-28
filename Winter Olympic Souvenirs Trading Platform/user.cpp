#include <iostream>
#include "user.h"
#include "seller.h"
#include "buyer.h"
#include "print.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include "calculator.h"
#include "notice.h"

using namespace std;

extern bool is_num(char c);
extern bool input_check(int n);
extern string choice;
extern string get_time();
extern string cut(string s, int n, char c);

//���ص�n����������λ��
int find_comma(string s,int n)
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

//�޸��ļ���Ϣ
void change_txt(string id, string txt, string inf, int n)	//ID �ļ��� �޸ĵ���Ϣ �ڼ������ź�
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

//�ַ������Ƿ�Ϸ�
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

void User::u_inf()
{
	system("cls");

	bool end_procedure = false;
	while (!end_procedure) {
		box_print("1.�鿴��Ϣ 2.�޸���Ϣ 3.��ֵ 4.�����û�������", '=');
		cout << "��ѡ�������";

		//�������׼ȷ��
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
			system("cls");
			cout << "���������������ڷ��������桪����������" << endl;
			Sleep(500);
			system("cls");
			end_procedure = true;
			break;
		}

	}
}

void User::u_show_inf()//�鿴��Ϣ���û��� ��ϵ��ʽ ��ַ ���
{
	fstream fuser("users.txt");
	if (!fuser.is_open()) {
		cout << "Open failed!";
		exit(-1);
	}
	else {
		string lines, name, phone, address, money, state, credibility;
		//�������Ҳ���
		while (getline(fuser, lines)) {
			if (u_id == lines.substr(0, 4)) {
				name = lines.substr(find_comma(lines, 1) + 1, find_comma(lines, 2) - find_comma(lines, 1) - 1);
				phone = lines.substr(find_comma(lines, 3) + 1, find_comma(lines, 4) - find_comma(lines, 3) - 1);
				address = lines.substr(find_comma(lines, 4) + 1, find_comma(lines, 5) - find_comma(lines, 4) - 1);
				credibility = lines.substr(find_comma(lines, 6) + 1, find_comma(lines, 7) - find_comma(lines, 6) - 1);
				state = lines.substr(find_comma(lines, 7) + 1);
			}
		}

		if (phone == "") phone = "��";
		if (address == "") address = "��";

		//�����Ҫ���¼���
		string expr;
		//��ֵ��¼
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

		//������Ʒ
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

		//������Ʒ
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

		//������
		system("cls");
		cout << "���������������ڲ�ѯ������������";
		Sleep(500);
		system("cls");

		cout << "******************************" << endl;
		cout << "�û�ID��\t" << u_id << endl;
		cout << "�û�����\t" << name << endl;
		cout << "��ϵ��ʽ��\t" << phone << endl;
		cout << "��ַ��\t\t" << address << endl;
		cout << "��\t\t" << money << endl;
		cout << "�����֣�\t" << credibility << endl;
		cout << "״̬��\t\t" << state << endl;
		cout << "******************************" << endl;

		system("pause");
		system("cls");
	}
}

void User::u_update()//�޸���Ϣ
{
	bool end_procedure = false;
	while (!end_procedure) {
		cout << "��ѡ���޸ĵ����ԣ�1.�û��� 2.���� 3.��ϵ��ʽ 4.��ַ 5.ȡ������";

		//�������׼ȷ��
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
			system("cls");
			cout << "�����������������˳�������������" << endl;
			Sleep(500);
			system("cls");
			end_procedure = true;
			break;
		}
	}
}

void User::u_update_name()
{
	string name;
	cout << "�������û�����������10��Ӣ����ĸ���֣���";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	//����û����Ƿ�Ϸ�
	int len = 0;
	for (int i = 0; i < name.length(); i++) {
		len++;
		if (len > 10) {
			colorful_print("�û������Ϸ������ȴ���10��", 4);
			system("pause");
			system("cls");
			return;
		}
		if (name[i] < 0)i++;
	}

	for (int i = 0; i < name.length(); i++) {
		if (name[i] < 0)i++;
		else if (name[i] < 65 || (name[i] > 90 && name[i] < 97) || name[i]>122) {
			colorful_print("�û������Ϸ����в��Ϸ��ַ���", 4);
			system("pause");
			system("cls");
			return;
		}
	}
	if (name[name.length() - 1] == ' ' || name[0] == ' ') {
		colorful_print("�û������Ϸ��������Կո�ͷ���β��", 4);
		system("pause");
		system("cls");
		return;
	}

	//�û����Ƿ��ظ�
	fstream name_check("users.txt");
	if (!name_check) {
		cout << "Open failed!";
		exit(-1);
	}
	else {
		string lines, names;
		getline(name_check, lines);//������һ��
		while (getline(name_check, lines)) {
			names = lines.substr(find_comma(lines, 1) + 1, find_comma(lines, 2) - find_comma(lines, 1) - 1);
			if (names == name) {
				if (u_id == lines.substr(0, 4)) {
					colorful_print("�û������Ϸ���������ԭ�û�����ͬ��", 4);
					system("pause");
					system("cls");
					return;
				}
				else {
					colorful_print("�û������Ϸ����ظ���", 4);
					system("pause");
					system("cls");
					return;
				}
			}
		}
	}

	//��û����
	change_txt(u_id, "users.txt", name, 1);

	cout << "�������������޸ĳɹ�������������";
	Sleep(500);
	system("cls");
}

void User::u_update_password()
{
	string o_password, n_password;
	cout << "���������ڵ����룺";
	getline(cin, o_password);
	if (o_password == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	fstream user("users.txt");
	string password, lines;
	getline(user, lines);
	while (getline(user, lines)) {
		if (u_id == lines.substr(0, 4)) {
			password = lines.substr(find_comma(lines, 2) + 1, find_comma(lines, 3) - find_comma(lines, 2) - 1);
			if (password != o_password) {
				colorful_print("Error���������", 4);
				system("pause");
				system("cls");
				return;
			}
			else {
				//������ȷ
				cout << "���������루������20��Сд��ĸ�����֣���";
				getline(cin, n_password);
				if (n_password == "") {
					colorful_print("Error�����벻��Ϊ�գ�", 4);
					system("pause");
					system("cls");
					return;
				}
				//��������Ƿ�Ϸ�
				if (n_password.length() > 20) {
					colorful_print("���벻�Ϸ������ȴ���20��", 4);
					system("pause");
					system("cls");
					return;
				}
				for (int i = 0; i < n_password.length(); i++) {
					if (n_password[i] < 48 || (n_password[i] > 57 && n_password[i] < 97) || n_password[i]>122) {
						colorful_print("���벻�Ϸ����в��Ϸ��ַ���", 4);
						system("pause");
						system("cls");
						return;
					}
				}

				//�ٴ���������
				string pas_check;
				cout << "���ٴ��������룺";
				getline(cin, pas_check);
				if (pas_check != n_password) {
					colorful_print("Error�����벻һ�£�", 4);
					system("pause");
					system("cls");
					return;
				}
			}

		}
	}

	change_txt(u_id, "users.txt", n_password, 2);

	cout << "�������������޸ĳɹ�������������";
	Sleep(500);
	system("cls");
}

void User::u_update_address()
{
	string address;
	cout << "�������ַ��������20���ַ�����";
	getline(cin, address);
	if (address == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}

	bool legal;
	legal =  chinese_length_check(address, 20);
	if (!legal) {
		colorful_print("��ַ���Ϸ������ȴ���20��", 4);
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < address.length(); i++) {
			if (address[i] == ' ') {
				colorful_print("��ַ���Ϸ��������пո�", 4);
				system("pause");
				system("cls");
				return;
			}
			if (address[i] == ',') {
				colorful_print("��ַ���Ϸ��������ж��ţ�", 4);
				system("pause");
				system("cls");
				return;
			}
			if (address[i] < 0)i++;
			else if (address[i] < 65 || (address[i] > 90 && address[i] < 97) || address[i]>122) {
				colorful_print("�û������Ϸ����в��Ϸ��ַ���", 4);
				system("pause");
				system("cls");
				return;
			}
		}

		change_txt(u_id, "users.txt", address, 4);

		cout << "�������������޸ĳɹ�������������";
		Sleep(500);
		system("cls");
	}
}

void User::u_update_phone()
{
	string phone;
	cout << "��������ϵ��ʽ��������20�����֣���";
	getline(cin, phone);
	if (phone == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}

	//�ַ��Ƿ�Ϸ�
	bool legal = true;
	for (int i = 0; i < phone.length(); i++) {
		if (phone[i] < '0' || phone[i]>'9') {
			legal = false;
		}
	}
	if (!legal) {
		colorful_print("��ϵ��ʽ���Ϸ����з����֣�", 4);
		system("pause");
		system("cls");
		return;
	}
	else if (phone.length() > 20) {
		colorful_print("��ϵ��ʽ���Ϸ������ȴ���20��", 4);
		system("pause");
		system("cls");
		return;
	}
	else {
		change_txt(u_id, "users.txt", phone, 3);

		cout << "�������������޸ĳɹ�������������";
		Sleep(500);
		system("cls");
	}
}

void User::u_recharge()//��ֵ
{
	string money;
	cout << "�������ֵ��������һλС������";
	getline(cin, money);
	if (money == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}

	//�Ƿ�Ϸ�
	bool legal = true, integ = true;
	for (int i = 0; i < money.length(); i++) {
		if ((money[i] < '0' || money[i]>'9') && money[i] != '.') {
			legal = false;
			break;
		}
		if (money[i] == '.') {
			integ = false;
			if (i == 0) {
				colorful_print("��ֵ���Ϸ���С���㲻���ǵ�һλ��", 4);
				system("pause");
				system("cls");
				return;
			}
			else if (i + 1 == money.length()) {
				colorful_print("��ֵ���Ϸ���С����������֣�", 4);
				system("pause");
				system("cls");
				return;
			}
			else if (i + 2 < money.length()) {
				colorful_print("��ֵ���Ϸ�������һλС����", 4);
				system("pause");
				system("cls");
				return;
			}
		}
	}
	if (!legal) {
		colorful_print("��ֵ���Ϸ����зǷ��ַ���", 4);
		system("pause");
		system("cls");
		return;
	}
	
	//���Ϸ�
	//���ɳ�ֵ��¼
	fstream recharge("recharge.txt", ios::app);
	if (!recharge.is_open()) {
		cout << "Open failed!" << endl;
	}
	else {
		recharge << u_id << "," << get_time() << "," << money << endl;
	}
	recharge.close();

	//�������
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

	cout << "��������������ֵ�ɹ�������������";
	Sleep(500);
	system("cls");
}

void User::u_buyer_mode()
{
	system("cls");

	Buyer buyer(u_id);
	bool end_procedure = false;
	while (!end_procedure) {
		box_print("1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�������� 7.�����û�������", '=');
		cout << "��ѡ�������";

		//�������׼ȷ��
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
			system("cls");
			cout << "���������������ڷ��������桪����������" << endl;
			Sleep(500);
			system("cls");
			end_procedure = true;
			break;
		}

	}

}

void User::u_seller_mode()
{
	system("cls");

	Seller seller(u_id);
	bool end_procedure = false;
	while (!end_procedure) {
		box_print("1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������", '=');
		cout << "��ѡ�������";

		//�������׼ȷ��
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
			system("cls");
			cout << "���������������ڷ��������桪����������" << endl;
			Sleep(500);
			system("cls");
			end_procedure = true;
			break;
		}

	}

}

void u_log_in()
{
	string name, password;
	cout << "�������û�����";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	cout << "���������룺";
	getline(cin, password);
	if (password == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
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
		//Ѱ���û���������
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
											colorful_print("�������", 4);
											system("pause");
											system("cls");
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
			colorful_print("Error���û������ڣ�", 4);
			system("pause");
			system("cls");
			return;
		}

		//�Ƿ���
		if (state == "banned") {
			colorful_print("���û��ѱ������", 4);
			system("pause");
			system("cls");
			return;
		}
		else {
			cout << "��������������½�ɹ�������������";
			Sleep(500);
			system("cls");
		}


		//��¼�ɹ���
		User user(id);
		bool end_procedure = false;
		while (!end_procedure) {
			box_print("1.������� 2.�������� 3.������Ϣ���� 4.�ҵ�֪ͨ 5.�˳���¼", '=');
			cout << "��ѡ�������";

			//�������׼ȷ��
			if (!input_check(5)) {
				continue;
			}

			switch ((int)(choice[0] - '0')) {
			case 1:
				system("cls");
				cout << "���������������ڼ��ء�����������";
				Sleep(500);
				system("cls");
				user.u_buyer_mode();
				break;
			case 2:
				system("cls");
				cout << "���������������ڼ��ء�����������"; 
				Sleep(500);
				system("cls");
				user.u_seller_mode();
				break;
			case 3:
				system("cls");
				cout << "���������������ڼ��ء�����������";
				Sleep(500);
				system("cls");
				user.u_inf();
				break;
			case 4:
				system("cls");
				cout << "���������������ڼ��ء�����������";
				Sleep(500);
				system("cls");
				user.u_notice();
				break;
			case 5:
				system("cls");
				cout << "�����������������˳���¼������������" << endl;
				Sleep(500);
				system("cls");
				end_procedure = true;
				break;
			}
		}
	}
}

void u_register()
{	
	string name, password;
	cout << "�������û�����������10��Ӣ����ĸ���֣���";
	getline(cin, name);
	if (name == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	//����û����Ƿ�Ϸ�
	int len = 0;
	for (int i = 0; i < name.length(); i++) {
		len++;
		if (len > 10) {
			colorful_print("�û������Ϸ������ȴ���10��", 4);
			system("pause");
			system("cls");
			return;
		}
		if (name[i] < 0)i++;
	}

	for (int i = 0; i < name.length(); i++) {
		if (name[i] < 0)i++;
		else if (name[i] < 65 || (name[i] > 90 && name[i] < 97) || name[i]>122) {
			colorful_print("�û������Ϸ����в��Ϸ��ַ���", 4);
			system("pause");
			system("cls");
			return;
		}
	}
	if (name[name.length() - 1] == ' ' || name[0] == ' ') {
		colorful_print("�û������Ϸ��������Կո�ͷ���β��", 4);
		system("pause");
		system("cls");
		return;
	}

	//�û����Ƿ��ظ�
	fstream name_check("users.txt");
	if (!name_check) {
		cout << "Open failed!";
		exit(-1);
	}
	else {
		string lines, names;
		int name_b, name_e;
		getline(name_check, lines);//������һ��
		while (getline(name_check, lines)) {
			for (int i = 0; i < lines.length(); i++) {
				if (lines[i] == ',') {
					name_b = i + 1;
					for (int j = i; j < lines.length(); j++) {
						if (lines[j] == ',') {
							name_e = j - 1;
							names = lines.substr(name_b, name_e - name_b + 1);
							if (names == name) {
								colorful_print("�û������Ϸ����ظ���", 4);
								system("pause");
								system("cls");
								return;
							}
						}
					}
					
				}
			}
		}
	}

	cout << "���������루������20��Сд��ĸ�����֣���";
	getline(cin, password);
	if (password == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	//��������Ƿ�Ϸ�
	if (password.length() > 20) {
		colorful_print("���벻�Ϸ������ȴ���20��", 4);
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < password.length(); i++) {
		if (password[i] < 48 || (password[i] > 57 && password[i] < 97) || password[i]>122) {
			colorful_print("���벻�Ϸ����в��Ϸ��ַ���", 4); 
			system("pause");
			system("cls");
			return;
		}
	}

	//�ٴ���������
	string pas_check;
	cout << "���ٴ��������룺";
	getline(cin, pas_check);
	if (pas_check != password) {
		colorful_print("Error�����벻һ�£�", 4);
		system("pause");
		system("cls");
		return;
	}

	//���Ϸ�
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
		//�û�ID
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

		//�û���������
		user << name << "," << password << ",";

		//����
		user << ",,0.0,��,active" << endl;
	}
	user.close();

	cout << "������������ע��ɹ�������������" << endl;
	Sleep(500);
	system("cls");
}

void User::u_notice()
{
	system("cls");

	bool end_procedure = false;
	while (!end_procedure) {
		system("cls");
		box_print("1.�鿴����Ϣ 2.�鿴��ʷ��Ϣ 3.�������� 4.����������", '=');
		cout << "��ѡ�������";

		//�������׼ȷ��
		if (!input_check(4)) {
			continue;
		}

		//֪ͨ���,����ʱ��,������ID,������ID,�Ƿ��Ѷ�,֪ͨ����
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
				if (cut(notice[i], 4, ',') == "��") {
					have_new = true;

					cout << endl;
					int length = max(notice[i].length() - find_comma(notice[i], 5) - 1, find_comma(notice[i], 2) + 1) + 10;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "����ʱ�䣺" << cut(notice[i], 1, ',') << endl;
					cout << "������ID��" << cut(notice[i], 2, ',') << endl;
					cout << "֪ͨ���ݣ�" << cut(notice[i], 5, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;

					change_txt(notice[i].substr(0, 4), "notice.txt", "��", 4);
				}
			}
			if (!have_new) {
				cout << endl;
				box_print("��û���µ���Ϣ��", '=');
			}
			system("pause");
			break; 
		}
		case 2:
		{
			bool have_new = false;
			for (int i = 0; i < notice.size(); i++) {
				if (cut(notice[i], 4, ',') == "��") {
					have_new = true;

					cout << endl;
					int length = max(notice[i].length() - find_comma(notice[i], 5) - 1, find_comma(notice[i], 2) + 1) + 10;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "����ʱ�䣺" << cut(notice[i], 1, ',') << endl;
					cout << "������ID��" << cut(notice[i], 2, ',') << endl;
					cout << "֪ͨ���ݣ�" << cut(notice[i], 5, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
				}
			}
			if (!have_new) {
				cout << endl;
				box_print("��û����ʷ��Ϣ��", '=');
			}
			system("pause");
			break;
		}
		case 3:
		{
			fstream comment("comments.txt");
			vector<string> comments;
			string lines;
			getline(comment, lines);
			while (getline(comment, lines)) {
				if (cut(lines, 6, ',') != "��Ч") {
					comments.push_back(lines);
				}
			}
			comment.close();

			if (comments.size() == 0) {
				cout << endl;
				box_print("��û����ʷ���ۣ�", '=');
				system("pause");
				break;
			}
			else {
				for (int i = 0; i < comments.size(); i++) {
					int length = cut(comments[i], 1, ',').length() + 10;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "����ID��\t" << comments[i].substr(0,4) << endl;
					cout << "����ʱ�䣺\t" << cut(comments[i], 1, ',') << endl;
					cout << "������ID��\t" << cut(comments[i], 2, ',') << endl;
					cout << "����ID��\t" << cut(comments[i], 4, ',') << endl;
					cout << "���֣�\t\t" << cut(comments[i], 5, ',') << endl;
					cout << "״̬��\t\t"<< cut(comments[i], 6, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
				}
			}

			//����ʷ����
			string id;
			cout << "��������Ҫ���ߵ�����ID:";
			getline(cin, id);
			if (id == "") {
				colorful_print("Error�����벻��Ϊ�գ�", 4);
				system("pause");
				system("cls");
				return;
			}
			if (id.length() != 4 || id[0] != 'C' || !is_num(id[1]) || !is_num(id[2]) || !is_num(id[3])) {
				colorful_print("����ID����", 4);
				system("pause");
				system("cls");
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
				colorful_print("����ID����", 4);
				system("pause");
				system("cls");
				return;
			}
			else {
				int i = 0;
				for (; i < comments.size(); i++) {
					if (comments[i].substr(0, 4) == id) {
						break;
					}
				}
				//�Ƿ���������
				if (cut(comments[i], 6, ',') == "������") {
					colorful_print("���������������У�", 4);
					system("pause");
					system("cls");
					return;
				}
				//�Ƿ��Ѿ�������
				fstream argues("argue.txt");
				string lines;
				while (getline(argues, lines)) {
					if (cut(lines, 3, ',') == id && cut(lines, 5, ',') == "�Ѳ���") {
						colorful_print("��Դ����۵������ѱ����أ�", 4);
						system("pause");
						system("cls");
						return;
					}
				}
				argues.close();

				do {
					int length = cut(comments[i], 1, ',').length() + 10;
					cout << "��Ҫ�����Ա���ߵ������ǣ�" << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;
					cout << "����ID��\t" << comments[i].substr(0, 4) << endl;
					cout << "����ʱ�䣺\t" << cut(comments[i], 1, ',') << endl;
					cout << "������ID��\t" << cut(comments[i], 2, ',') << endl;
					cout << "����ID��\t" << cut(comments[i], 4, ',') << endl;
					cout << "���֣�\t\t" << cut(comments[i], 5, ',') << endl;
					for (int j = 0; j < length; j++) cout << '=';
					cout << endl;

					//�ٴ�ȷ��
					cout << "�Ƿ�ȷ�����ߣ�(y/n)��";
					string check;
					getline(cin, check);
					if (check == "") {
						colorful_print("Error�����벻��Ϊ�գ�", 4);
						system("pause");
						system("cls");
						return;
					}
					if (check.length() == 1 && check[0] == 'y') {
						argue(id);
						return;
					}
					else if (check.length() == 1 && check[0] == 'n') {
						cout << endl;
						cout << "����������������ȡ��������������";
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

			break;//��Ӧswitch case �� braek
		}
		case 4:
			cout << endl;
			cout << "���������������ڷ��ء�����������" << endl;
			end_procedure = true;
			Sleep(500);
			system("cls");
			break;
		}

	}
}

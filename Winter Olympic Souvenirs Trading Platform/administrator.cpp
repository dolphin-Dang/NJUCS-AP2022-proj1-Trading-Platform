#include <iostream>
#include "administrator.h"
#include "print.h"
#include <Windows.h>
#include "command.h"
#include <fstream>
#include <string>
#include "notice.h"
#include <vector>

using namespace std;

extern int find_comma(string s, int n);
extern string choice;
extern bool input_check(int n);
extern bool is_num(char c);
extern string cut(string s, int n, char c);

void Administrator:: a_log_in()
{
	string name, password;

	cout << "���������Ա���ƣ�";
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

	if (name != a_name || password != a_password) {
		colorful_print("�û������������", 4);
		cout << "��������������½ʧ�ܣ������������˵�������������" << endl;
		Sleep(500);
		system("cls");
		return;
	}
	
	cout << "��������������½�ɹ�������������" << endl;
	Sleep(500);

	bool end_procedure = false;
	while (!end_procedure) {
		system("cls");
		box_print("1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.����û� 7.����֪ͨ 8.ע��", '=');
		cout << "��ѡ�������";

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
			cout << endl;
			cout << "����������������ע��������������" << endl;
			end_procedure = true;
			Sleep(500);
			system("cls");
			break;
		}
	}
}

void Administrator::a_search_goods()
{
	string command, good_name;
	cout << "��������Ʒ����";
	getline(cin, good_name);
	if (good_name == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	command = "SELECT * FROM commodity WHERE ���� CONTAINS " + good_name;
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
	cout << "�������û�ID��";
	getline(cin, user_id);
	if (user_id == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	if (user_id.length() != 4 || user_id[0] != 'U' || !is_num(user_id[1]) || !is_num(user_id[2]) || !is_num(user_id[3])) {
		colorful_print("�û�ID����", 4);
		system("pause");
		system("cls");
		return;
	}
	command = "DELETE FROM users WHERE ID = " + user_id;
	solve_command(command, 'a');
	
}

void Administrator::a_remove_good()
{
	string command, good_id;
	cout << "��������ƷID��";
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
		colorful_print("��Ʒ�����ڣ�", 4);
		system("pause");
		system("cls");
		return;
	}

	command = "DELETE FROM commodity WHERE ID = " + good_id;
	solve_command(command, 'a');

	send_notice("admin", good_id, s_id);
}

void Administrator::a_argue()
{
	system("cls");
	fstream argue("argue.txt");
	string lines;
	vector<string> argues;
	getline(argue, lines);
	while (getline(argue, lines)) {
		if (cut(lines, 5, ',') == "δ����") {
			argues.push_back(lines);
		}
	}
	argue.close();

	if (argues.size() == 0) {
		box_print("�����������ߣ�", '=');
		system("pause");
		return;
	}
	else {
		for (int i = 0; i < argues.size(); i++) {
			int length = max(cut(argues[i],1,',').length(), cut(argues[i], 4, ',').length()) + 16;
			for (int j = 0; j < length; j++) cout << '=';
			cout << endl;
			cout << "���߱�ţ�\t" << argues[i].substr(0, 4) << endl;
			cout << "����ʱ�䣺\t" << cut(argues[i], 1, ',') << endl;
			cout << "������ID��\t" << cut(argues[i], 2, ',') << endl;
			string reason = cut(argues[i], 4, ',');
			int k = 0;
			for (; k < reason.length(); k++) {
				if (reason[k] == ')') {
					break;
				}
			}
			cout << "�������ɣ�\t" << reason.substr(k + 1) << endl;
			cout << "���֣�\t\t" << reason.substr(1, k - 1) << endl;
			for (int j = 0; j < length; j++) cout << '=';
			cout << endl;
		}

		//������
		string id;
		cout << "�������㴦�������ID:";
		getline(cin, id);
		if (id == "") {
			colorful_print("Error�����벻��Ϊ�գ�", 4);
			system("pause");
			system("cls");
			return;
		}
		if (id.length() != 4 || id[0] != 'A' || !is_num(id[1]) || !is_num(id[2]) || !is_num(id[3])) {
			colorful_print("����ID����", 4);
			system("pause");
			system("cls");
			return;
		}

		bool have_argue = false;
		for (int i = 0; i < argues.size(); i++) {
			if (argues[i].substr(0, 4) == id) {
				have_argue = true;
			}
		}

		if (!have_argue) {
			colorful_print("����ID����", 4);
			system("pause");
			system("cls");
			return;
		}
		else {//id��ȷ
			int i = 0;
			for (; i < argues.size(); i++) {
				if (argues[i].substr(0, 4) == id) {
					break;
				}
			}

			cout << endl;
			box_print("��ѡ��Դ������ߵĲ�����1.ͬ�����ߣ��������� 2.�������ߣ�ά��ԭ��", '=');
			cout << "���������ѡ��";

			//�������׼ȷ��
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
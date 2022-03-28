#include <iostream>
#include "command.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include "print.h"

using namespace std;

extern int find_comma(string s, int n);
extern string get_time();
extern void change_txt(string id, string txt, string inf, int n);

string get_time_sec()
{
	string ret;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	ret = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);

	return ret;
}

//�г���n��char���string
string cut(string s, int n,char c)
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

void Select(string s, char mode, string id = "*")
{
	if (mode == 'a') {
		string txt = cut(s, 3, ' ');
		if (txt == "users") {
			fstream user("users.txt");
			string lines, firstline;
			bool found = false;
			cout << endl;
			cout << "*************************************************************************************" << endl;
			getline(user, firstline);
			while (getline(user, lines)) {
				if (!found) {
					found = true;
					cout << cut(firstline, 0, ',') << '\t' << cut(firstline, 1, ',') << '\t' << setw(20) << cut(firstline, 3, ',') \
						<< '\t' << setw(20) << cut(firstline, 4, ',') << '\t' << setw(20) << cut(firstline, 5, ',') << endl;
				}
				cout << cut(lines, 0, ',') << '\t' << cut(lines, 1, ',') << '\t';
				if (cut(lines, 3, ',') == "") cout << setw(20) << "��" << '\t';
				else cout<< setw(20) << cut(lines, 3, ',') << '\t';
				if (cut(lines, 4, ',') == "")cout << setw(20) << "��" << '\t';
				else cout << setw(20) << cut(lines, 4, ',') << '\t';
				cout << setw(20) << cut(lines, 5, ',') << endl;
			}
			if (!found) {
				cout << "δ�ҵ��κ��û���Ϣ��" << endl;
			}
			cout << "*************************************************************************************" << endl;
			cout << endl;
			user.close();
		}
		else if (txt == "orders") {
			fstream order("orders.txt");
			string lines, firstline;
			bool found = false;
			cout << endl;
			cout << "********************************************************************************" << endl;
			getline(order, firstline);
			while (getline(order, lines)) {
				if (!found) {
					found = true;
					cout << cut(firstline, 0, ',') << '\t' << cut(firstline, 1, ',') << '\t' << \
						cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' << setw(15) << \
						cut(firstline, 4, ',') << '\t' << cut(firstline, 5, ',') << '\t' << cut(firstline, 6, ',') << endl;
				}
				cout << cut(lines, 0, ',') << '\t' << cut(lines, 1, ',') << '\t' << cut(lines, 2, ',') \
					<< '\t' << '\t' << cut(lines, 3, ',') << '\t' << setw(15) << cut(lines, 4, ',') << '\t' << cut(lines, 5, ',') \
					<< '\t' << cut(lines, 6, ',') << endl;
			}
			if (!found) {
				cout << "δ�ҵ��κζ�����Ϣ��" << endl;
			}
			cout << "********************************************************************************" << endl;
			cout << endl;
			order.close();
		}
		else if (txt == "commodity") {
			string g_name = cut(s, 7, ' ');
			if (g_name == "404") {
				fstream good("commodity.txt");
				string lines, firstline;
				bool found = false;
				cout << endl;
				cout << "********************************************************************************" << endl;
				getline(good, firstline);
				while (getline(good, lines)) {
					if (!found) {
						found = true;
						cout << cut(firstline, 0, ',') << '\t' << setw(10) << cut(firstline, 1, ',') << '\t' \
							<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' \
							<< cut(firstline, 5, ',') << '\t' << cut(firstline, 6, ',') << '\t' << cut(firstline, 7, ',') << endl;
					}
					cout << cut(lines, 0, ',') << '\t' << setw(10) << cut(lines, 1, ',') << '\t' \
						<< cut(lines, 2, ',') << '\t' << cut(lines, 3, ',') << '\t' \
						<< cut(lines, 5, ',') << '\t' << cut(lines, 6, ',') << '\t' << cut(lines, 7, ',') << endl;
				}
				if (!found) {
					cout << "δ�ҵ��κ���Ʒ��Ϣ��" << endl;
				}
				cout << "********************************************************************************" << endl;
				cout << endl;
				good.close();
			}
			else {
				fstream good("commodity.txt");
				string lines, firstline;
				bool found = false;
				cout << endl;
				cout << "********************************************************************************" << endl;
				getline(good, firstline);
				while (getline(good, lines)) {
					if (cut(lines, 1, ',').find(g_name) != string::npos) {
						if (!found) {
							found = true;
							cout << cut(firstline, 0, ',') << '\t' << setw(10) << cut(firstline, 1, ',') << '\t' \
								<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' \
								<< cut(firstline, 5, ',') << '\t' << cut(firstline, 6, ',') << '\t' << cut(firstline, 7, ',') << endl;
						}
						cout << cut(lines, 0, ',') << '\t' << setw(10) << cut(lines, 1, ',') << '\t' \
							<< cut(lines, 2, ',') << '\t' << cut(lines, 3, ',') << '\t' \
							<< cut(lines, 5, ',') << '\t' << cut(lines, 6, ',') << '\t' << cut(lines, 7, ',') << endl;
					}
				}
				if (!found) {
					cout << "δ�ҵ���ص���Ʒ���볢������������ʽ���������������档����������" << endl;
				}
				cout << "********************************************************************************" << endl;
				cout << endl;
				good.close();
			}
		}
	}
	else if (mode == 'b') {
		string txt = cut(s, 3, ' ');
		if (txt == "order") {
			fstream good("orders.txt");
			string lines, firstline;
			bool found = false;
			getline(good, firstline);
			cout << endl;
			cout << "***************************************************************************" << endl;
			while (getline(good, lines)) {
				if (cut(lines, 6, ',') == id) {
					if (!found) {
						found = true;
						cout << cut(firstline, 0, ',') << '\t' << cut(firstline, 1, ',') << '\t' \
							<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' << setw(10) \
							<< cut(firstline, 4, ',') << '\t' << cut(firstline, 5, ',') << endl;
					}
					cout << cut(lines, 0, ',') << '\t' << cut(lines, 1, ',') << '\t' \
						<< cut(lines, 2, ',') << '\t' << '\t' << cut(lines, 3, ',') << '\t' << setw(10) \
						<< cut(lines, 4, ',') << '\t' << cut(lines, 5, ',') << endl;
				}
			}
			if (!found) {
				cout << "����û���κζ�����" << endl;
			}
			cout << "***************************************************************************" << endl;
			cout << endl;
			good.close();
		}
		else if (txt == "commodity") {
			txt = cut(s, 5, ' ');
			if (txt == "404") {
				fstream good("commodity.txt");
				string lines, firstline;
				bool found = false;
				cout << endl;
				cout << "********************************************************************************" << endl;
				getline(good, firstline);
				while (getline(good, lines)) {
					if (cut(lines, 7, ',') == "������") {
						if (!found) {
							found = true;
							cout << cut(firstline, 0, ',') << '\t' << setw(10) << cut(firstline, 1, ',') << '\t' \
								<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' \
								<< cut(firstline, 5, ',') << '\t' << cut(firstline, 6, ',') << '\t' << cut(firstline, 7, ',') << endl;
						}
						cout << cut(lines, 0, ',') << '\t' << setw(10) << cut(lines, 1, ',') << '\t' \
							<< cut(lines, 2, ',') << '\t' << cut(lines, 3, ',') << '\t' \
							<< cut(lines, 5, ',') << '\t' << cut(lines, 6, ',') << '\t' << cut(lines, 7, ',') << endl;
					}
				}
				if (!found) {
					cout << "δ�ҵ��κ����۵���Ʒ��Ϣ��" << endl;
				}
				cout << "********************************************************************************" << endl;
				cout << endl;
				good.close();
			}
			else if (txt == "ID") {
				string g_id = cut(s, 7, ' ');
				fstream good("commodity.txt");
				string lines, firstline;
				bool found = false;
				cout << endl;
				cout << "********************************************************************************" << endl;
				getline(good, firstline);
				while (getline(good, lines)) {
					if (lines.substr(0,4)==g_id) {
						if (cut(lines, 7, ',') == "������") {
							found = true;
							cout << cut(firstline, 0, ',') << '\t' << setw(10) << cut(firstline, 1, ',') << '\t' \
								<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' \
								<< cut(firstline, 5, ',') << '\t' << cut(firstline, 6, ',') << '\t' << cut(firstline, 7, ',') << endl;
							cout << cut(lines, 0, ',') << '\t' << setw(10) << cut(lines, 1, ',') << '\t' \
								<< cut(lines, 2, ',') << '\t' << cut(lines, 3, ',') << '\t' \
								<< cut(lines, 5, ',') << '\t' << cut(lines, 6, ',') << '\t' << cut(lines, 7, ',') << endl;
						}
						else if (cut(lines, 7, ',') == "���¼�") {
							cout << "����Ʒ���¼�!" << endl;
						}
						else if (cut(lines, 7, ',') == "������") {
							cout << "����Ʒ������!" << endl;
						}
						break;
					}
				}
				if (!found) {
					cout << "��ƷID������!" << endl;
				}
				cout << "********************************************************************************" << endl;
				cout << endl;
				good.close();
			}
			else if (txt == "����") {
				string g_name = cut(s, 7, ' ');
				fstream good("commodity.txt");
				string lines, firstline;
				bool found = false;
				cout << endl;
				cout << "********************************************************************************" << endl;
				getline(good, firstline);
				while (getline(good, lines)) {
					if (cut(lines, 1, ',').find(g_name) != string::npos) {
						if (cut(lines, 7, ',') == "������") {
							if (!found) {
								found = true;
								cout << cut(firstline, 0, ',') << '\t' << setw(10) << cut(firstline, 1, ',') << '\t' \
									<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' \
									<< cut(firstline, 5, ',') << '\t' << cut(firstline, 6, ',') << '\t' << cut(firstline, 7, ',') << endl;
							}
							cout << cut(lines, 0, ',') << '\t' << setw(10) << cut(lines, 1, ',') << '\t' \
								<< cut(lines, 2, ',') << '\t' << cut(lines, 3, ',') << '\t' \
								<< cut(lines, 5, ',') << '\t' << cut(lines, 6, ',') << '\t' << cut(lines, 7, ',') << endl;
						}
					}
				}
				if (!found) {
					cout << "δ�ҵ���ص���Ʒ���볢������������ʽ���������������档����������" << endl;
				}
				cout << "********************************************************************************" << endl;
				cout << endl;
				good.close();
			}
		}
	}
	else if (mode == 's') {
		string txt = cut(s, 3, ' ');
		if (txt == "commodity") {
			fstream good("commodity.txt");
			string lines, firstline;
			bool found = false;
			getline(good, firstline);
			cout << endl;
			cout << "***************************************************************************" << endl;
			while (getline(good, lines)) {
				if (cut(lines, 5, ',') == id) {
					if (!found) {
						found = true;
						cout << cut(firstline, 0, ',') << '\t' << setw(20) << cut(firstline, 1, ',') << '\t' \
							<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' << setw(10) \
							<< cut(firstline, 6, ',') << '\t' << cut(firstline, 7, ',') << endl;
					}
					cout << cut(lines, 0, ',') << '\t' << setw(20) << cut(lines, 1, ',') << '\t' \
						<< cut(lines, 2, ',') << '\t' << cut(lines, 3, ',') << '\t' << setw(10) \
						<< cut(lines, 6, ',') << '\t' << cut(lines, 7, ',') << endl;
				}
			}
			if (!found) {
				cout << "����û�з����κ���Ʒ��" << endl;
			}
			cout << "***************************************************************************" << endl;
			cout << endl;
			good.close();
		}
		else if (txt == "order") {
			fstream good("orders.txt");
			string lines, firstline;
			bool found = false;
			getline(good, firstline);
			cout << endl;
			cout << "***************************************************************************" << endl;
			while (getline(good, lines)) {
				if (cut(lines,5,',')==id) {
					if (!found) {
						found = true;
						cout << cut(firstline, 0, ',') << '\t' << cut(firstline, 1, ',') << '\t' \
							<< cut(firstline, 2, ',') << '\t' << cut(firstline, 3, ',') << '\t' << setw(10) \
							<< cut(firstline, 4, ',') << '\t' << cut(firstline, 6, ',') << endl;
					}
					cout << cut(lines, 0, ',') << '\t' << cut(lines, 1, ',') << '\t' \
						<< '\t' << cut(lines, 2, ',') << '\t' << cut(lines, 3, ',') << '\t' <<setw(10) \
						<< cut(lines, 4, ',') << '\t' << cut(lines, 6, ',') << endl;
				}
			}
			if (!found) {
				cout << "����û���κζ�����" << endl;
			}
			cout << "***************************************************************************" << endl;
			cout << endl;
			good.close();
		}
	}
}

void Update(string s, char mode)
{
	int comma_num = 0, space_num = 0;
	string good_id = s.substr(s.length() - 4);
	string inf;
	int five_space, six_space;//��Ϣ�ڵ�������ո�֮��
	
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			space_num++;
			if (space_num == 5)five_space = i;
			if (space_num == 6) {
				six_space = i;
				break;
			}
		}
	}
	inf = s.substr(five_space + 1, six_space - five_space - 1);

	if (s.substr(21, 4) == "�۸�") {
		comma_num = 2;
	}
	else if (s.substr(21, 4) == "����") {
		comma_num = 4;
	}

	if (comma_num) {
		change_txt(good_id, "commodity.txt", inf, comma_num);
	}

	cout << endl;
	cout << "�������������޸ĳɹ�������������" << endl;

}

void Insert(string s, char mode, string id = "*")
{
	if (mode == 's') {
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(') {
				s = s.substr(i + 1, s.length() - i - 2);
				break;
			}
		}

		string last_id, lines;

		fstream goods("commodity.txt");
		getline(goods, lines);
		while (getline(goods, lines)) {
			last_id = lines.substr(0, 4);
		}
		goods.close();

		fstream good;
		good.open("commodity.txt", ios::app);
		if (!good.is_open()) {
			cout << "Open failed!";
		}
		else {
			//�û�ID
			if (last_id == "") {
				last_id = "M001";
			}
			else {
				last_id[0] = '1';
				int g_num = atoi(last_id.c_str());
				g_num++;
				last_id = to_string(g_num);
				last_id[0] = 'M';
			}

			//"��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬"

			good << last_id << ',';

			//���� �۸� ���� ����
			good << s << ',' << id << "," << get_time() << "," << "������" << endl;

		}
		good.close();

		cout << endl;
		cout << "�����������������ɹ�������������" << endl;

	}
	else if (mode == 'b') {
		//���Ӷ�����Ϣ
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(') {
				s = s.substr(i + 1, s.length() - i - 2);
				break;
			}
		}
		fstream order("orders.txt", ios::app);
		if (!order.is_open()) {
			cout << "Open failed!" << endl;
			exit(-1);
		}
		else {
			order << s << ",��" << endl;
		}
		order.close();

		//�޸���Ʒ��Ϣ
		s = s.substr(5);
		fstream good("commodity.txt");
		string lines, good_num, num, state;
		num = s.substr(find_comma(s, 2) + 1, find_comma(s, 3) - find_comma(s, 2) - 1);

		while (getline(good, lines)) {
			if (lines.substr(0, 4) == s.substr(0, 4)) {
				good_num = lines.substr(find_comma(lines, 3) + 1, find_comma(lines, 4) - find_comma(lines, 3) - 1);
				state = lines.substr(find_comma(lines, 7) + 1);
				break;
			}
		}
		good.close();

		int ig_num = atoi(good_num.c_str()) - atoi(num.c_str());
		if (!ig_num) {
			state = "������";
			change_txt(s.substr(0, 4), "commodity.txt", state, 7);
			good_num = "0";
		}
		else {
			good_num = to_string(ig_num);
		}
		change_txt(s.substr(0, 4), "commodity.txt", good_num, 3);

		//�޸���Һ����ҵ����
		string s_id = s.substr(s.length() - 9, 4);
		string b_id = s.substr(s.length() - 4);
		string price = s.substr(find_comma(s, 1) + 1, find_comma(s, 2) - find_comma(s, 1) - 1);
		string money = to_string(atoi(num.c_str()) * atof(price.c_str()));
		string s_balance, b_balance;
		fstream user("users.txt");
		if (!user.is_open()) {
			cout << "Open failed!" << endl;
			exit(-1);
		}
		else {
			string lines;
			getline(user, lines);
			while (getline(user, lines)) {
				if (lines.substr(0.4) == s_id) {
					s_balance = lines.substr(find_comma(lines, 5) + 1, find_comma(lines, 6) - find_comma(lines, 5) - 1);
				}
				else if (lines.substr(0, 4) == b_id) {
					b_balance = lines.substr(find_comma(lines, 5) + 1, find_comma(lines, 6) - find_comma(lines, 5) - 1);
				}
			}
		}
		user.close();

		s_balance = to_string(atof(s_balance.c_str()) + atof(money.c_str()));
		b_balance = to_string(atof(b_balance.c_str()) - atof(money.c_str()));
		b_balance = b_balance.substr(0, b_balance.length() - 5);
		s_balance = s_balance.substr(0, s_balance.length() - 5);

		change_txt(s_id, "users.txt", s_balance, 5);
		change_txt(b_id, "users.txt", b_balance, 5);

		cout << "����������������ɹ�������������" << endl;
	}
}

void Delete(string s, char mode)
{
	if (mode == 's') {
		string good_id = s.substr(s.length() - 4);
		change_txt(good_id, "commodity.txt", "���¼�", 7);

		cout << "�������������¼ܳɹ�������������" << endl;

	}
	else if (mode == 'a') {
		string id = s.substr(s.length() - 4);
		if (id[0] == 'U') {
			change_txt(id, "users.txt", "banned", 7);
			cout << "����������������ɹ�������������" << endl;

		}
		else if (id[0] == 'M') {
			change_txt(id, "commodity.txt", "���¼�", 7);
			cout << "�������������¼ܳɹ�������������" << endl;

		}
	}
}

void solve_command(string s, char mode, string id)
{
	//SQL������txt
	fstream commands("commands.txt", ios::app);
	commands << get_time() << " " << get_time_sec() << "," << s << endl;
	commands.close();

	//�г�����
	string command;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			command = s.substr(0, i);
			break;
		}
	}


	if (command == "SELECT") {
		Select(s, mode, id);
	}
	else if (command == "UPDATE") {
		Update(s, mode);
	}
	else if (command == "INSERT") {
		Insert(s, mode, id);
	}
	else if (command == "DELETE") {
		Delete(s, mode);
	}

	system("pause");
	system("cls");
}

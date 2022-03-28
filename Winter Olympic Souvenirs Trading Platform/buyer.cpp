#include <iostream>
#include "buyer.h"
#include "command.h"
#include "print.h"
#include <Windows.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include "calculator.h"
#include "notice.h"

using namespace std;

extern void change_txt(string id, string txt, string inf, int n);
extern bool is_num(char c);
extern int find_comma(string s, int n);
extern string cut(string s, int n, char c);
extern string get_time_sec();

//����������
string cal_cred(string id)
{
	string expr, ans;
	string lines;
	int cnt = 0;
	fstream helper("comments.txt");
	getline(helper, lines);
	while (getline(helper, lines)) {
		if (id == cut(lines, 3, ',') && cut(lines, 6, ',') != "��Ч") {
			cnt++;
			expr += cut(lines, 5, ',') + "+";
		}
	}

	if (cnt == 0) {
		ans = "��";
	}
	else {
		helper.close();
		expr = "(" + expr.substr(0, expr.length() - 1) + ")/" + to_string(cnt);
		ans = calculator(expr);
	}
	return ans;
}

//��ö�����������Ϣ
string get_time()
{
	string ret;
	// ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
	time_t now = time(0);
	tm* ltm = localtime(&now);
	ret = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);

	return ret;
}

void Buyer::b_all_goods()
{
	string command = "SELECT * FROM commodity";
	solve_command(command, 'b');
}

void Buyer::b_search_good()
{
	string command = "SELECT * FROM commodity WHERE ���� CONTAINS ";
	string g_name;
	cout << "��������Ʒ����";
	getline(cin, g_name);
	if (g_name == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	command = command + g_name;
	solve_command(command, 'b');
}

void Buyer::b_his_orders()
{
	string command = "SELECT * FROM order";
	solve_command(command, 'b', u_id);
}

void Buyer::b_good_detail()
{
	string command = "SELECT * FROM commodity WHERE ID = ";
	string good_id;
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
	solve_command(command, 'b');
}

void Buyer::b_buy()//����ID ��ƷID ���� ���� ʱ�� ����ID ���ID //�����
{
	string command = "INSERT INTO order VALUES ";
	string good_id, num;

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
	string lines, price, seller_id, good_num;
	bool good_found = false;
	getline(goods, lines);
	while (getline(goods, lines)) {
		if (good_id == lines.substr(0, 4)) {
			price = lines.substr(find_comma(lines, 2) + 1, find_comma(lines, 3) - find_comma(lines, 2) - 1);
			seller_id = lines.substr(find_comma(lines, 5) + 1, find_comma(lines, 6) - find_comma(lines, 5) - 1);
			good_num= lines.substr(find_comma(lines, 3) + 1, find_comma(lines, 4) - find_comma(lines, 3) - 1);
			good_found = true;
			break;
		}
	}

	goods.close();
	
	if (u_id == seller_id) {
		colorful_print("Error�����ܹ����Լ�����Ʒ��", 4);
		system("pause");
		system("cls");
		return;
	}

	if (!good_found) {
		colorful_print("Error����Ʒ�����ڣ�", 4);
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
	if (atoi(num.c_str()) > atoi(good_num.c_str())) {
		colorful_print("��Ʒ�������Ϸ�����治�㣡", 4);
		system("pause");
		system("cls");
		return;
	}

	//����Ƿ������
	fstream check("users.txt");
	if (!check.is_open()) {
		cout << "Open failed!" << endl;
	}
	else {
		string lines, money;
		getline(check, lines);
		while (getline(check, lines)) {
			if (lines.substr(0, 4) == u_id) {
				money = lines.substr(find_comma(lines, 5) + 1, find_comma(lines, 6) - find_comma(lines, 5) - 1);
				if (atof(money.c_str()) < atoi(num.c_str()) * atof(price.c_str())) {
					colorful_print("���㣡", 4);
					system("pause");
					system("cls");
					return;
				}
				break;
			}
		}
	}
	check.close();

	//����̼���������
	fstream seller("users.txt");
	string cred;
	while (getline(seller, lines)) {
		if (seller_id == lines.substr(0, 4)) {
			cred = cut(lines, 6, ',');
			break;
		}
	}
	
	if (cred == "��" || atof(cred.c_str()) < 80) {
		if (cred == "��") {
			cout << "���̼��������ּ�¼�����̼ң����Ƿ��������(y/n):";
		}
		else {
			cout << "���̼������ֽϵ�(" << cred << "��)���Ƿ��������(y/n):";
		}
		string check;
		getline(cin, check);
		if (check == "") {
			colorful_print("Error�����벻��Ϊ�գ�", 4);
			system("pause");
			system("cls");
			return;
		}
		if (check.length() == 1 && check[0] == 'y') {
		}
		else if (check.length() == 1 && check[0] == 'n') {
			cout << endl;
			cout << "������������ȡ�����򡪡���������";
			Sleep(500);
			system("cls");
			return;
		}
		else {
			colorful_print("����Ƿ���", 4);
			system("pause");
			system("cls");
			return;
		}
	}

	//��������
	string last_id;//����ID
	fstream orders("orders.txt");
	if (!orders.is_open()) {
		cout << "Open failed!";
	}
	else {
		string lines;
		getline(orders, lines);
		while (getline(orders, lines)) {
			last_id = lines.substr(0, 4);
		}
	}
	orders.close();

	fstream order;
	order.open("orders.txt", ios::app);
	if (!order.is_open()) {
		cout << "Open failed!";
	}
	else {
		//�û�ID
		if (last_id == "") {
			last_id = "T001";
		}
		else {
			last_id[0] = '1';
			int o_num = atoi(last_id.c_str());
			o_num++;
			last_id = to_string(o_num);
			last_id[0] = 'T';
		}
	}
	order.close();

	command = command + "(" + last_id + "," + good_id + "," + price + "," + num + "," + get_time() + "," + seller_id + "," + u_id + ")";
	solve_command(command, 'b');

	send_notice(u_id, good_id, seller_id);
}

void Buyer::b_judge()
{
	cout << "��������δ���۵���ʷ������" << endl;
	fstream good("orders.txt");
	string lines, firstline;
	bool found = false;
	vector<string> orders;
	getline(good, firstline);
	cout << endl;
	cout << "***************************************************************************" << endl;
	while (getline(good, lines)) {
		if (cut(lines, 6, ',') == u_id && cut(lines, 7, ',') == "��") {
			orders.push_back(lines);
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
		cout << "����û��δ���۵��κζ�����" << endl;
	}
	cout << "***************************************************************************" << endl;
	cout << endl;
	good.close();

	if (!found) {
		system("pause");
		system("cls");
		return;
	}

	cout << "�����붩��ID��";
	string o_id;
	getline(cin, o_id);
	if (o_id == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return;
	}
	if (o_id.length() != 4 || o_id[0] != 'T' || !is_num(o_id[1]) || !is_num(o_id[2]) || !is_num(o_id[3])) {
		colorful_print("����ID����", 4);
		system("pause");
		system("cls");
		return;
	}
	int i = 0;
	for (; i < orders.size(); i++) {
		if (o_id == cut(orders[i], 0, ',')) {
			break;
		}
	}

	if (i == orders.size()) {
		colorful_print("Error���ⲻ����Ķ�����", 4);
		system("pause");
		system("cls");
		return;
	}
	else {
		cout << "��Դ˴������������ۣ�����100��ֻ������������";
		string comment;
		getline(cin, comment);
		if (comment == "") {
			colorful_print("Error�����벻��Ϊ�գ�", 4);
			system("pause");
			system("cls");
			return;
		}
		if (comment.length() > 3) {
			colorful_print("Error�����벻�Ϸ���", 4);
			system("pause");
			system("cls");
			return;
		}
		if (comment.length() > 2) {
			if (comment != "100") {
				colorful_print("Error�����벻�Ϸ���", 4);
				system("pause");
				system("cls");
				return;
			}
		}
		for (int i = 0; i < comment.length(); i++) {
			if (!is_num(comment[i])) {
				colorful_print("Error�����벻�Ϸ���", 4);
				system("pause");
				system("cls");
				return;
			}
		}

		//���ɱ��
		string last_id;
		fstream comments("comments.txt");
		if (!comments.is_open()) {
			cout << "Open failed!";
		}
		else {
			string lines;
			getline(comments, lines);
			while (getline(comments, lines)) {
				last_id = lines.substr(0, 4);
			}
		}
		comments.close();

		fstream comments2;
		comments2.open("comments.txt", ios::app);
		if (!comments2.is_open()) {
			cout << "Open failed!";
		}
		else {
			//�û�ID
			if (last_id == "") {
				last_id = "C001";
			}
			else {
				last_id[0] = '1';
				int u_num = atoi(last_id.c_str());
				u_num++;
				last_id = to_string(u_num);
				last_id[0] = 'C';
			}

			comments2 << last_id << ',';
		}
		comments2.close();

		//����Ϸ�
		string s_id = cut(orders[i], 5, ',');
		fstream comments3("comments.txt", ios::app);
		comments3 << get_time() << " " << get_time_sec() << "," << cut(orders[i], 6, ',') \
			<< "," << s_id << "," << o_id << "," << comment << ",��Ч" << endl;
		comments3.close();

		//���㲢�޸�������
		string ans;
		ans = cal_cred(s_id);

		change_txt(s_id, "users.txt", ans, 6);
		change_txt(o_id, "orders.txt", "��", 7);

		send_notice(u_id, o_id, s_id);

		cout << "���������������۳ɹ�������������";
		Sleep(500);
		system("cls");
		return;
	}
}

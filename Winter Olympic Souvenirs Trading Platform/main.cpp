#include <iostream>
#include "goods and orders.h"
#include "print.h"
#include "command.h"
#include "administrator.h"
#include "buyer.h"
#include "seller.h"
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

string choice;
extern int u_num;

//ѡ���¼��ע���
void begin_window(void)
{
	box_print("1.����Ա��¼ 2.�û���¼ 3.�û�ע�� 4.�˳�����",'=');

	cout << endl;
	cout << "��ѡ�������";
}

//�������Ϸ�����ͷ���0	n��������ѡ��
bool input_check(int n) {
	getline(cin, choice);
	if (choice == "") {
		colorful_print("Error�����벻��Ϊ�գ�", 4);
		system("pause");
		system("cls");
		return false;
	}
	if (choice.length() > 1 || choice.length() == 0) {
		colorful_print("ERROR:��������ȷ��ѡ�\n", 4);
		system("pause");
		system("cls");
		return false;
	}
	if (choice[0] < '1' || choice[0] > '0' + n) {
		colorful_print("ERROR:��������ȷ��ѡ�\n", 4);
		system("pause");
		system("cls");
		return false;
	}
	else {
		return true;
	}
}

void file_check(void)
{
	fstream test1("users.txt");
	if (!test1) {
		ofstream test11("users.txt");
		test11 << "�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,������,�û�״̬" << endl;
		test11.close();
	}
	test1.close();

	fstream test2("orders.txt");
	if (!test2) {
		ofstream test21("orders.txt");
		test21 << "����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID,�Ƿ�����" << endl;
		test21.close();
	}
	test2.close();

	fstream test3("commodity.txt");
	if (!test3) {
		ofstream test31("commodity.txt");
		test31 << "��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬" << endl;
		test31.close();
	}
	test3.close();

	fstream test4("recharge.txt");
	if (!test4) {
		ofstream test41("recharge.txt");
		test41 << "�û�ID,��ֵʱ��,��ֵ���" << endl;
		test41.close();
	}
	test4.close();

	fstream test5("commands.txt");
	if (!test5) {
		ofstream test51("commands.txt");
		test51 << "��������ʱ��,SQL����" << endl;
		test51.close();
	}
	test5.close();

	fstream test6("comments.txt");
	if (!test6) {
		ofstream test61("comments.txt");
		test61 << "���۱��,����ʱ��,���ID,����ID,����ID,����,�Ƿ���Ч" << endl;//��Ч ��Ч ������
		test61.close();
	}
	test6.close();

	fstream test7("notice.txt");
	if (!test7) {
		ofstream test71("notice.txt");
		test71 << "֪ͨ���,����ʱ��,������ID,������ID,�Ƿ��Ѷ�,֪ͨ����" << endl;
		test71.close();
	}
	test7.close();

	fstream test8("argue.txt");
	if (!test8) {
		ofstream test81("argue.txt");
		test81 << "���߱��,����ʱ��,������ID,���۱��,��������,����״̬" << endl;//δ���� �Ѳ��� ��ͬ��
		test81.close();
	}
	test8.close();
}

int main()
{
	//����Ƿ������Դ�ļ� �����ھʹ���
	file_check();

	colorful_print(print_line("*", 38), 6);
	colorful_print("*****��ӭ�������»����Ʒ����ƽ̨*****", 6);
	colorful_print(print_line("*", 38), 6);
	cout << endl;
	Sleep(500);

	Administrator admin;

	bool end_procedure = false;
	while (!end_procedure) {
		begin_window();

		//�������׼ȷ��
		if (!input_check(4)) {
			continue;
		}
		
		switch ((int)(choice[0] - '0')) {
		case 1://����Ա��¼
			admin.a_log_in();
			break;
		case 2://�û���¼
			u_log_in();
			break;
		case 3://�û�ע��
			u_register();
			break;
		case 4://�˳�����
			system("cls");
			cout << "�����������������˳����򡪡���������" << endl;
			Sleep(500);
			system("cls");
			colorful_print(print_line("*", 36), 6);
			colorful_print("*****���ѳɹ��˳�����ӭ�´�����*****", 6);
			colorful_print(print_line("*", 36), 6);
			end_procedure = true;
			break;
		}
	}
	return 0;
}
#include <iostream>
#include "goods and orders.h"
#include "print.h"
#include "command.h"
#include "administrator.h"
#include "buyer.h"
#include "seller.h"
#include <fstream>
#include <string>
#include "helpers.h"
#include "user.h"

using namespace std;

string choice;

//选择登录、注册等
void begin_window(void)
{
	box_print("1.管理员登录 2.用户登录 3.用户注册 4.退出程序",'=');

	cout << endl;
	cout << "请选择操作：";
}

//遇到不合法输入就返回0	n代表最大的选项

void file_check(void)
{
	fstream test1("users.txt");
	if (!test1) {
		ofstream test11("users.txt");
		test11 << "用户ID,用户名,密码,联系方式,地址,钱包余额,信誉分,用户状态" << endl;
		test11.close();
	}
	test1.close();

	fstream test2("orders.txt");
	if (!test2) {
		ofstream test21("orders.txt");
		test21 << "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID,是否评价" << endl;
		test21.close();
	}
	test2.close();

	fstream test3("commodity.txt");
	if (!test3) {
		ofstream test31("commodity.txt");
		test31 << "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态" << endl;
		test31.close();
	}
	test3.close();

	fstream test4("recharge.txt");
	if (!test4) {
		ofstream test41("recharge.txt");
		test41 << "用户ID,充值时间,充值金额" << endl;
		test41.close();
	}
	test4.close();

	fstream test5("commands.txt");
	if (!test5) {
		ofstream test51("commands.txt");
		test51 << "命令生成时间,SQL命令" << endl;
		test51.close();
	}
	test5.close();

	fstream test6("comments.txt");
	if (!test6) {
		ofstream test61("comments.txt");
		test61 << "评价编号,评价时间,买家ID,卖家ID,订单ID,评分,是否有效" << endl;//有效 无效 申诉中
		test61.close();
	}
	test6.close();

	fstream test7("notice.txt");
	if (!test7) {
		ofstream test71("notice.txt");
		test71 << "通知编号,发送时间,发送者ID,接收者ID,是否已读,通知内容" << endl;
		test71.close();
	}
	test7.close();

	fstream test8("argue.txt");
	if (!test8) {
		ofstream test81("argue.txt");
		test81 << "申诉编号,申诉时间,申诉者ID,评价编号,申诉理由,处理状态" << endl;//未处理 已驳回 已同意
		test81.close();
	}
	test8.close();
}

int main()
{
	//检查是否存在资源文件 不存在就创建
	file_check();

	colorful_print(print_line("*", 38), 6);
	colorful_print("*****欢迎来到冬奥会纪念品交易平台*****", 6);
	colorful_print(print_line("*", 38), 6);
	cout << endl;

	Administrator admin;

	bool end_procedure = false;
	while (!end_procedure) {
		begin_window();

		//检查输入准确性
		if (!input_check(4)) {
			continue;
		}
		
		switch ((int)(choice[0] - '0')) {
		case 1://管理员登录
			admin.a_log_in();
			break;
		case 2://用户登录
			u_log_in();
			break;
		case 3://用户注册
			u_register();
			break;
		case 4://退出程序
			////system("cls");
			colorful_print(print_line("*", 36), 6);
			colorful_print("*****您已成功退出，欢迎下次再来*****", 6);
			colorful_print(print_line("*", 36), 6);
			end_procedure = true;
			break;
		}
	}
	return 0;
}
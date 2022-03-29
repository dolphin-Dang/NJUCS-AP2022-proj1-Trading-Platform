#include <iostream>
#include "print.h"
#include <iomanip>

using namespace std;

void colorful_print(string s, int color, int end)	//如果end==1就换行，默认换行
{
	/*HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
	cout << s;
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);*/

	if (color == 6) {
		printf(YELLOW "%s" NONE, s.c_str());
	}
	else if (color == 4) {
		printf(RED "%s" NONE, s.c_str());
	}

	if (end == 1) {
		cout << endl;
	}
}

string print_line(string c,int n)
{
	string s = c;
	for (int i = 1; i < n; i++) {
		s += c;
	}
	return s;
}

void box_print(string s, char c)	//s为打印内容，c为box的格式
{
	cout << setfill(c) << setw(s.length()) << c << endl;
	cout << s << endl;
	cout << setfill(c) << setw(s.length()) << c << endl;
	cout << setfill(' ');
}

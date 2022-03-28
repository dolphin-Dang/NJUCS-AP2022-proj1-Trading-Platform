#include <iostream>
#include <Windows.h>
#include "print.h"
#include <iomanip>

using namespace std;

void colorful_print(string s, int color, int end)	//���end==1�ͻ��У�Ĭ�ϻ���
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
	cout << s;
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);

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

void box_print(string s, char c)	//sΪ��ӡ���ݣ�cΪbox�ĸ�ʽ
{
	cout << setfill(c) << setw(s.length()) << c << endl;
	cout << s << endl;
	cout << setfill(c) << setw(s.length()) << c << endl;
	cout << setfill(' ');
}

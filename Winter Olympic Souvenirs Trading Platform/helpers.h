#pragma once
using namespace std;

bool input_check(int n);

bool is_signal(char c);

bool is_operator(char c);

bool is_num(char c);

string get_time_sec();

string cut(string s, int n, char c);

int find_comma(string s, int n);

void change_txt(string id, string txt, string inf, int n);

bool chinese_length_check(string s, int n);

string get_time();

string cal_cred(string id);

void pause();

